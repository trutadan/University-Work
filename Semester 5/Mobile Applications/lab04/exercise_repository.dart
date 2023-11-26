import 'package:logger/logger.dart';
import 'package:sqflite/sqflite.dart';
import 'exercise_database.dart';
import 'exercise_model.dart';

class ExerciseRepository {
  final ExerciseDatabase _exerciseDatabase = ExerciseDatabase();
  static final Logger _logger = Logger();

  Future<List<Exercise>> getExercises() async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Fetching all exercises from the database');
      final List<Map<String, dynamic>> maps = await db.query(ExerciseDatabase.tableName);

      return List.generate(maps.length, (index) {
        return Exercise(
          id: maps[index]['id'],
          name: maps[index]['name'],
          description: maps[index]['description'],
          category: maps[index]['category'],
          primaryMuscle: maps[index]['primaryMuscle'],
          secondaryMuscles: maps[index]['secondaryMuscles'].split(','),
          equipment: maps[index]['equipment'].split(','),
          image: maps[index]['image'],
        );
      });
    } catch (e) {
      _logger.e('Error fetching exercises: $e');
      rethrow;
    }
  }

  Future<Exercise?> getExerciseById(int id) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Fetching exercise with ID $id from the database');
      List<Map<String, dynamic>> maps = await db.query(
        ExerciseDatabase.tableName,
        where: 'id = ?',
        whereArgs: [id],
      );

      if (maps.isNotEmpty) {
        return Exercise(
          id: maps[0]['id'],
          name: maps[0]['name'],
          description: maps[0]['description'],
          category: maps[0]['category'],
          primaryMuscle: maps[0]['primaryMuscle'],
          secondaryMuscles: maps[0]['secondaryMuscles'].split(','),
          equipment: maps[0]['equipment'].split(','),
          image: maps[0]['image'],
        );
      } else {
        return null;
      }
    } catch (e) {
      _logger.e('Error fetching exercise with ID $id: $e');
      rethrow;
    }
  }

  Future<int> insertExercise(Exercise exercise) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Inserting exercise into the database: $exercise');
      int id = await db.insert(ExerciseDatabase.tableName, exercise.toMap(),
          conflictAlgorithm: ConflictAlgorithm.replace);
      _logger.d('Inserted exercise with ID $id');
      return id;
    } catch (e) {
      _logger.e('Error inserting exercise into the database: $e');
      rethrow;
    }
  }

  Future<void> updateExercise(Exercise exercise) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Updating exercise in the database: $exercise');
      await db.update(
        ExerciseDatabase.tableName,
        exercise.toMap(),
        where: 'id = ?',
        whereArgs: [exercise.id],
      );
      _logger.d('Updated exercise with ID ${exercise.id}');
    } catch (e) {
      _logger.e('Error updating exercise in the database: $e');
      rethrow;
    }
  }

  Future<void> deleteExercise(int id) async {
    try {
      final db = await _exerciseDatabase.database;
      _logger.d('Deleting exercise with ID $id from the database');
      await db.delete(
        ExerciseDatabase.tableName,
        where: 'id = ?',
        whereArgs: [id],
      );
      _logger.d('Deleted exercise with ID $id');
    } catch (e) {
      _logger.e('Error deleting exercise with ID $id from the database: $e');
      rethrow;
    }
  }
}
