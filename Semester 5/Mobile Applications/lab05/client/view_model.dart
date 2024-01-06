import 'package:flutter/material.dart';
import 'package:lab04/server_repository.dart';
import 'package:logger/logger.dart';

import 'exercise_model.dart';

class ExerciseViewModel extends ChangeNotifier {
  final ExerciseServerRepository _repository;
  final Logger _logger = Logger();
  List<Exercise> _exercises = [];

  ExerciseViewModel(this._repository){
    loadExercises();
  }

  List<Exercise> get exercises => _exercises;

  Future<void> loadExercises() async {
    try {
      _logger.d("Loading exercises in view model...");
      _exercises = await _repository.getExercises();

      _logger.d("Exercises: $_exercises");

      notifyListeners();
      _logger.d("Exercises loaded successfully: ${_exercises.length} exercises");
    } catch (e) {
      _logger.e("Error loading exercises in view model: $e");
    }
  }

  Future<void> addExercise(Exercise exercise) async {
    try {
      _logger.d("Adding exercise in view model...");
      int id = await _repository.insertExercise(exercise);
      exercise.id = id;
      await loadExercises();
      _logger.d("Exercise added successfully: $exercise");
    } catch (e) {
      _logger.e("Error adding exercise in view model: $e");
    }
  }

  Future<void> updateExercise(Exercise exercise) async {
    try {
      _logger.d("Updating exercise in view model...");
      await _repository.updateExercise(exercise);
      await loadExercises();
      _logger.d("Exercise updated successfully: $exercise");
    } catch (e) {
      _logger.e("Error updating exercise in view model: $e");
    }
  }

  Future<void> deleteExercise(int id) async {
    try {
      _logger.d("Deleting exercise in view model... $id");
      await _repository.deleteExercise(id);
      await loadExercises();
      _logger.d("Exercise deleted successfully with ID: $id");
    } catch (e) {
      _logger.e("Error deleting exercise in view model: $e");
    }
  }

  Future<Exercise?> getExerciseById(int id) async {
    try {
      _logger.d("Getting exercise by id in view model... $id");
      return await _repository.getExerciseById(id);
    } catch (e) {
      _logger.e("Error getting exercise by id in view model: $e");
    }

    return null;
  }
}
