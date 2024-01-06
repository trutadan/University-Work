import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import 'package:logger/logger.dart';

import 'exercise_model.dart';

class ExerciseDatabase {
  final String tableName;
  static Database? _database;

  static final Logger _logger = Logger();

  ExerciseDatabase({required this.tableName});

  Future<Database> get database async {
    if (_database != null) {
      _logger.d('Returning existing database instance');
      return _database!;
    }

    _logger.d('Initializing database');
    _database = await _initDatabase();
    return _database!;
  }

  Future<Database> _initDatabase() async {
    final path = join(await getDatabasesPath(), '$tableName.db');
    _logger.d('Database path: $path');

    try {
      _logger.d('Opening database');
      return await openDatabase(
        path,
        version: 1,
        onCreate: (db, version) async {
          _logger.d('Creating table $tableName');
          await db.execute('''
            CREATE TABLE $tableName(
              id INTEGER PRIMARY KEY,
              name TEXT,
              description TEXT,
              category TEXT,
              primaryMuscle TEXT,
              secondaryMuscles TEXT,
              equipment TEXT,
              image TEXT,
              synchronized BOOLEAN              
            )
          ''');
        },
      );
    } catch (e) {
      _logger.e('Error opening database: $e');
      rethrow;
    }
  }

  Future<List<Exercise>> getAllExercises() async {
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.query(tableName);

    return List.generate(maps.length, (index) {
      return Exercise.fromMap(maps[index]);
    });
  }

  Future<Exercise?> getExerciseById(int id) async {
    final db = await database;

    final List<Map<String, dynamic>> maps = await db.query(
      tableName,
      where: 'id = ?',
      whereArgs: [id],
    );

    return maps.isNotEmpty ? Exercise.fromMap(maps[0]) : null;
  }

  Future<int> getNextId() async {
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.query(tableName, orderBy: 'id DESC', limit: 1);
    return maps.isNotEmpty ? maps[0]['id'] + 1 : 1;
  }

  Future<int> insertExercise(Exercise exercise) async {
    final db = await database;

    _logger.d('Inserting exercise into the database: $exercise');
    return await db.insert(tableName, exercise.toMapWithIdAndSynchronized(), conflictAlgorithm: ConflictAlgorithm.replace);
  }

  Future<void> insertAllExercisesSynchronized(List<Exercise> exercises) async {
    final db = await database;

    final batch = db.batch();

    for (var exercise in exercises) {
      exercise.synchronized = true;
      batch.insert(tableName, exercise.toMapWithIdAndSynchronized());
    }

    await batch.commit();
  }

  Future<void> updateExercise(Exercise exercise) async {
    final db = await database;

    await db.update(
      tableName,
      exercise.toMapWithIdAndSynchronized(),
      where: 'id = ?',
      whereArgs: [exercise.id],
    );
  }

  Future<void> deleteExercise(int id) async {
    final db = await database;

    await db.delete(
      tableName,
      where: 'id = ?',
      whereArgs: [id],
    );
  }

  Future<void> deleteAllExercises() async {
    final db = await database;

    await db.delete(tableName);
  }

  Future<List<Exercise>> getAllUnsyncExercises() async {
    final db = await database;
    final unsyncExercises = await db.query(
      tableName,
      where: 'synchronized = ?',
      whereArgs: [false],
    );

    return unsyncExercises.map((map) => Exercise.fromMap(map)).toList();
  }

  Future<void> close() async {
    try {
      final db = await database;
      _logger.d('Closing database');
      await db.close();
    } catch (e) {
      _logger.e('Error closing database: $e');
    }
  }
}
