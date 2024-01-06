import 'dart:async';
import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:lab04/service.dart';
import 'package:logger/logger.dart';
import 'package:http/http.dart' as http;

import 'consts.dart';
import 'database_handler.dart';
import 'exercise_model.dart';

class ExerciseServerRepository {
  final ExerciseDatabase _exerciseDatabase;

  static final Logger _logger = Logger();

  ExerciseServerRepository({required ExerciseDatabase database}) :
                                      _exerciseDatabase = database;

  Future<void> listenToServer(String data) async {
    var decodedData = json.decode(data);

    if (decodedData.containsKey('message')) {
      decodedData = decodedData['message'];
    } else {
      _logger.i('Format data we do not care about: $data');
      return;
    }

    if (decodedData is Map<String, dynamic>) {
      final messageType = decodedData['type'];
      final payload = decodedData['payload'];

      _logger.d('Received message from the server: $data');
      switch (messageType) {
        case 'create':
          await _handleCreateMessage(payload);
          break;
        case 'update':
          await _handleUpdateMessage(payload);
          break;
        case 'delete':
          await _handleDeleteMessage(payload);
          break;
        default:
          _logger.e('Unhandled message type: $messageType');
      }
    }
  }

  Future<int> insertExerciseLocally(Exercise exercise) async {
    try {
      _logger.d('Inserting exercise into the database: $exercise');
      return await _exerciseDatabase.insertExercise(exercise);
    } catch (e) {
      _logger.e('Error inserting exercise into the database: $e');
      rethrow;
    }
  }

  Future<void> deleteExerciseLocally(int id) async {
    try {
      _logger.d('Deleting exercise with ID $id from the database');
      await _exerciseDatabase.deleteExercise(id);
    } catch (e) {
      _logger.e('Error deleting exercise with ID $id from the database: $e');
      rethrow;
    }
  }

  Future<void> updateExerciseLocally(Exercise exercise) async {
    try {
      _logger.d('Updating exercise in the database: $exercise');
      await _exerciseDatabase.updateExercise(exercise);
    } catch (e) {
      _logger.e('Error updating exercise in the database: $e');
      rethrow;
    }
  }

  Future<Exercise?> getExerciseById(int id) async {
    try {
      _logger.d('Fetching exercise with ID $id from the database');
      return await _exerciseDatabase.getExerciseById(id);
    } catch (e) {
      _logger.e('Error fetching exercise with ID $id: $e');
      rethrow;
    }
  }

  Future<void> _handleCreateMessage(Map<String, dynamic> payload) async {
    final exercise = Exercise.fromJson(payload);

    Exercise exerciseFromDatabase = (await getExerciseById(exercise.id))!;
    if (exerciseFromDatabase == exercise) {
      _logger.d('Exercise with ID ${exercise.id} already exists locally');
      return;
    }

    _logger.d('Inserting exercise $exercise locally');
    exercise.synchronized = true;
    await insertExerciseLocally(exercise);
  }

  Future<void> _handleDeleteMessage(Map<String, dynamic> payload) async {
    final id = int.tryParse(payload['id']);
    if (id != null) {
      if (await getExerciseById(id) == null) {
        _logger.d('Exercise with ID $id already deleted locally');
        return;
      }

      _logger.d('Deleting exercise with ID $id locally');
      await deleteExerciseLocally(id);
    } else {
      _logger.e('Invalid delete message payload: $payload');
    }
  }

  Future<void> _handleUpdateMessage(Map<String, dynamic> payload) async {
    final exercise = Exercise.fromJson(payload);

    Exercise exerciseFromDatabase = (await getExerciseById(exercise.id))!;
    if (exerciseFromDatabase == exercise) {
      _logger.d('Exercise with ID ${exercise.id} already exists locally');
      return;
    }

    _logger.d('Updating exercise with ID ${exercise.id} locally');
    exercise.synchronized = true;
    await updateExerciseLocally(exercise);
  }

  Future<void> synchronizeDatabases() async {
    try {
      _logger.d('Synchronizing databases');

      List<Exercise> unsynchronizedExercises = await _getUnsyncExercises();

      await _syncWithServer(unsynchronizedExercises);

      _logger.d('Synchronizing completed');
    } catch (e) {
      _logger.e('Error synchronizing databases: $e');
      rethrow;
    }
  }

  Future<List<Exercise>> _getUnsyncExercises() async {
    _logger.d('Fetching unsynchronized exercises from the local database');
    return await _exerciseDatabase.getAllUnsyncExercises();
  }

  Future<void> _syncWithServer(List<Exercise> unsynchronizedExercises) async {
    try {
      List<Exercise> serverExercises = await _fetchExercisesFromServer();

      await _deleteLocalExercises();

      await _insertServerExercises(serverExercises);

      await _sendUnsynchronizedExercisesToServer(unsynchronizedExercises);
    } catch (e) {
      _logger.e('Error syncing with the server: $e');
      rethrow;
    }
  }

  Future<List<Exercise>> _fetchExercisesFromServer() async {
    _logger.d('Sending request to the server to get all exercises');
    var response = await http.get(
      Uri.parse('$SERVER_URL/exercises'),
    ).timeout(const Duration(seconds: 3));

    if (response.statusCode != 200) {
      _logger.e('Error fetching exercises: ${response.body}');
      throw Exception('Error fetching exercises from the server');
    }
    List<dynamic> serverExercisesJson = jsonDecode(response.body);
    List<Exercise> serverExercises = serverExercisesJson
        .map((exerciseJson) => Exercise.fromJson(exerciseJson))
        .toList();

    return serverExercises;
  }

  Future<void> _deleteLocalExercises() async {
    _logger.d('Deleting all exercises from the local database');
    await _exerciseDatabase.deleteAllExercises();
  }

  Future<void> _insertServerExercises(List<Exercise> serverExercises) async {
    _logger.d('Inserting all exercises from the server into the local database');
    await _exerciseDatabase.insertAllExercisesSynchronized(serverExercises);
  }

  Future<void> _sendUnsynchronizedExercisesToServer(List<Exercise> unsynchronizedExercises) async {
    if (unsynchronizedExercises.isEmpty) {
      _logger.d('No unsynchronized exercises found locally');
      return;
    }

    for (Exercise exercise in unsynchronizedExercises) {
      _logger.d('Sending unsynchronized exercise to the server: $exercise');
      var response = await http.post(
        Uri.parse('$SERVER_URL/exercises'),
        headers: {'Content-Type': 'application/json'},
        body: jsonEncode(exercise.toJson()),
      ).timeout(const Duration(seconds: 3));

      if (response.statusCode != 201) {
        _logger.e('Error inserting exercise: ${response.body}');

        exercise.synchronized = false;
        exercise.id = await _exerciseDatabase.getNextId();

        await insertExerciseLocally(exercise);
      } else {
        _logger.d('Exercise sent to the server');

        Exercise addedExercise = Exercise.fromJson(jsonDecode(response.body));
        addedExercise.synchronized = true;
        await insertExerciseLocally(addedExercise);
        _logger.d('Exercise added locally');
      }
    }
  }

  Future<List<Exercise>> getExercises() async {
    try {
      await ExerciseService().onlineStatusManager.checkOnline();

      _logger.d('Fetching all exercises from the database');
      return await _exerciseDatabase.getAllExercises();
    } catch (e) {
      _logger.e('Error fetching exercises: $e');
      rethrow;
    }
  }

  Future<int> insertExercise(Exercise exercise) async {
    try {
      await ExerciseService().onlineStatusManager.checkOnline();

      if (ExerciseService().onlineStatusManager.isOnline) {
        _logger.d('Sending inserted exercise to the server');

        var response = await http.post(
          Uri.parse('$SERVER_URL/exercises'),
          headers: {'Content-Type': 'application/json'},
          body: jsonEncode(exercise.toJson())
        ).timeout(const Duration(seconds: 3));

        _logger.d('Server response: ${response.body}');
        if (response.statusCode != 201) {
          _logger.e('Error inserting exercise: ${response.body}');
          ExerciseService().notificationService.showToast('Connection is down, but the exercise is added locally', backgroundColor: Colors.yellow);

          exercise.synchronized = false;
          exercise.id = await _exerciseDatabase.getNextId();

          return await insertExerciseLocally(exercise);
        } else {
          _logger.d('Exercise sent to the server');

          ExerciseService().notificationService.showToast('Exercise successfully added');
          Exercise addedExercise = Exercise.fromJson(jsonDecode(response.body));
          await insertExerciseLocally(addedExercise);
          _logger.d('Exercise added locally');

          return jsonDecode(response.body)['id'];
        }
      } else {
        _logger.e('Can not send exercise to server while offline');
        ExerciseService().notificationService.showToast('Connection is down, but the exercise is added locally', backgroundColor: Colors.yellow);

        exercise.synchronized = false;
        exercise.id = await _exerciseDatabase.getNextId();

        _logger.d('Inserting exercise unsynchronized into the database: $exercise');
        return await insertExerciseLocally(exercise);
      }
    } catch (e) {
      _logger.e('Error inserting exercise: $e');
      rethrow;
    }
  }

  Future<void> deleteExercise(int id) async {
    try {
      await ExerciseService().onlineStatusManager.checkOnline();

      if (ExerciseService().onlineStatusManager.isOnline) {
        _logger.d('Sending deleted exercise to the server');
        var response = await http.delete(
          Uri.parse('$SERVER_URL/exercises/$id'),
        ).timeout(const Duration(seconds: 3));

        if (response.statusCode != 200) {
          _logger.e('Error deleting exercise: ${response.body}');
          Exercise? exercise = await getExerciseById(id);
          if (exercise?.synchronized == false) {
            _logger.d('If the exercise is unsynchronized, delete it locally');
            ExerciseService().notificationService.showToast('Connection is down, but you deleted the exercise locally', backgroundColor: Colors.yellow);

            await deleteExerciseLocally(id);
          } else {
            _logger.e('If the exercise is synchronized, you can not update it while offline');
            ExerciseService().notificationService.showToast('Connection is down, you can not delete this exercise', backgroundColor: Colors.red);
          }
        } else {
          _logger.d('Id of the exercise to be deleted sent to the server');
          ExerciseService().notificationService.showToast('Exercise successfully deleted');
          await deleteExerciseLocally(id);
          _logger.d('Exercise deleted locally');
        }
      } else {
        _logger.e('Can not send id of the exercise to be deleted to server while offline');
        Exercise? exercise = await getExerciseById(id);
        if (exercise?.synchronized == false) {
          _logger.d('If the exercise is unsynchronized, delete it locally');
          ExerciseService().notificationService.showToast('Connection is down, but you deleted the exercise locally', backgroundColor: Colors.yellow);
          await deleteExerciseLocally(id);
        } else {
          ExerciseService().notificationService.showToast('Connection is down, you can not delete this exercise', backgroundColor: Colors.red);
        }
      }
    } catch (e) {
      _logger.e('Error deleting exercise: $e');
      rethrow;
    }
  }

  Future<void> updateExercise(Exercise exercise) async {
    try {
      await ExerciseService().onlineStatusManager.checkOnline();

      Exercise? exerciseToBeUpdated = await getExerciseById(exercise.id);

      if (ExerciseService().onlineStatusManager.isOnline) {
        _logger.d('Sending exercise to be updated to the server');
        var response = await http.put(
            Uri.parse('$SERVER_URL/exercises/${exercise.id}'),
            headers: {'Content-Type': 'application/json'},
            body: jsonEncode(exercise.toJson())
        ).timeout(const Duration(seconds: 3));

        if (response.statusCode != 200) {
          _logger.e('Error updating exercise: ${response.body}');
          if (exerciseToBeUpdated?.synchronized == false) {
            _logger.d('If the exercise is unsynchronized, update it locally');
            ExerciseService().notificationService.showToast('Connection is down, but you updated this exercise locally', backgroundColor: Colors.yellow);

            exercise.synchronized = false;
            await updateExerciseLocally(exercise);
          } else {
            _logger.e('If the exercise is synchronized, you can not update it while offline');
            ExerciseService().notificationService.showToast('Connection is down, you can not update this exercise', backgroundColor: Colors.red);
          }
        } else {
          _logger.d('Exercise to be updated sent to the server');
          ExerciseService().notificationService.showToast('Exercise successfully updated');

          Exercise updatedExercise = Exercise.fromJson(jsonDecode(response.body));
          await updateExerciseLocally(updatedExercise);
          _logger.d('Exercise updated locally');
        }
      } else {
        _logger.e('Can not send exercise to be updated to server while offline');
        if (exerciseToBeUpdated?.synchronized == false) {
          _logger.d('If the exercise is unsynchronized, update it locally');
          ExerciseService().notificationService.showToast('Connection is down, but you updated this exercise locally', backgroundColor: Colors.yellow);
          exercise.synchronized = false;
          await updateExerciseLocally(exercise);
        } else {
          ExerciseService().notificationService.showToast('Connection is down, you can not update this exercise', backgroundColor: Colors.red);
        }
      }
    } catch (e) {
      _logger.e('Error updating exercise: $e');
      rethrow;
    }
  }
}