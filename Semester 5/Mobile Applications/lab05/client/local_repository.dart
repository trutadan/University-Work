import 'package:logger/logger.dart';

import 'database_handler.dart';
import 'exercise_model.dart';

class ExerciseRepository {
  final ExerciseDatabase _exerciseDatabase;

  static final Logger _logger = Logger();

  ExerciseRepository({required ExerciseDatabase database}) : _exerciseDatabase = database;

  Future<List<Exercise>> getExercises() async {
    try {
      _logger.d('Fetching all exercises from the database');
      return await _exerciseDatabase.getAllExercises();
    } catch (e) {
      _logger.e('Error fetching exercises: $e');
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

  Future<int> insertExercise(Exercise exercise) async {
    try {
      _logger.d('Inserting exercise into the database: $exercise');
      return await _exerciseDatabase.insertExercise(exercise);
    } catch (e) {
      _logger.e('Error inserting exercise into the database: $e');
      rethrow;
    }
  }

  Future<void> updateExercise(Exercise exercise) async {
    try {
      _logger.d('Updating exercise in the database: $exercise');
      await _exerciseDatabase.updateExercise(exercise);
    } catch (e) {
      _logger.e('Error updating exercise in the database: $e');
      rethrow;
    }
  }

  Future<void> deleteExercise(int id) async {
    try {
      _logger.d('Deleting exercise with ID $id from the database');
      await _exerciseDatabase.deleteExercise(id);
    } catch (e) {
      _logger.e('Error deleting exercise with ID $id from the database: $e');
      rethrow;
    }
  }
}