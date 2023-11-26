import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import 'package:logger/logger.dart';

class ExerciseDatabase {
  static const String tableName = 'exercises';
  static final Logger _logger = Logger();

  static Database? _database;

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
    final path = join(await getDatabasesPath(), 'exercises.db');
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
              image TEXT
            )
          ''');
        },
      );
    } catch (e) {
      _logger.e('Error opening database: $e');
      rethrow;
    }
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
