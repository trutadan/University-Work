import 'package:sqflite/sqflite.dart';

import 'exercise_database.dart';
import 'exercise_model.dart';

class ExerciseDatabaseActions {
  static Future<List<Exercise>> getAllExercises(Database db) async {
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
  }

  static Future<Exercise?> getExerciseById(Database db, int id) async {
    final List<Map<String, dynamic>> maps = await db.query(
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
  }

  static Future<int> insertExercise(Database db, Exercise exercise) async {
    return await db.insert(ExerciseDatabase.tableName, exercise.toMap(),
        conflictAlgorithm: ConflictAlgorithm.replace);
  }

  static Future<void> updateExercise(Database db, Exercise exercise) async {
    await db.update(
      ExerciseDatabase.tableName,
      exercise.toMap(),
      where: 'id = ?',
      whereArgs: [exercise.id],
    );
  }

  static Future<void> deleteExercise(Database db, int id) async {
    await db.delete(
      ExerciseDatabase.tableName,
      where: 'id = ?',
      whereArgs: [id],
    );
  }
}