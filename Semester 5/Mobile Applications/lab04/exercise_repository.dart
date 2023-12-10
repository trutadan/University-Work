import 'package:logger/logger.dart';

import 'exercise_database.dart';
import 'exercise_database_actions.dart';
import 'exercise_model.dart';

class ExerciseRepository {
  final ExerciseDatabase _exerciseDatabase;
  static final Logger _logger = Logger();

  ExerciseRepository({required ExerciseDatabase database}) : _exerciseDatabase = database;

  Future<List<Exercise>> getExercises() async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Fetching all exercises from the database');
      return ExerciseDatabaseActions.getAllExercises(db);
    } catch (e) {
      _logger.e('Error fetching exercises: $e');
      rethrow;
    }
  }

  Future<Exercise?> getExerciseById(int id) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Fetching exercise with ID $id from the database');
      return ExerciseDatabaseActions.getExerciseById(db, id);
    } catch (e) {
      _logger.e('Error fetching exercise with ID $id: $e');
      rethrow;
    }
  }

  Future<int> insertExercise(Exercise exercise) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Inserting exercise into the database: $exercise');
      return await ExerciseDatabaseActions.insertExercise(db, exercise);
    } catch (e) {
      _logger.e('Error inserting exercise into the database: $e');
      rethrow;
    }
  }

  Future<void> updateExercise(Exercise exercise) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Updating exercise in the database: $exercise');
      await ExerciseDatabaseActions.updateExercise(db, exercise);
    } catch (e) {
      _logger.e('Error updating exercise in the database: $e');
      rethrow;
    }
  }

  Future<void> deleteExercise(int id) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Deleting exercise with ID $id from the database');
      await ExerciseDatabaseActions.deleteExercise(db, id);
    } catch (e) {
      _logger.e('Error deleting exercise with ID $id from the database: $e');
      rethrow;
    }
  }
}