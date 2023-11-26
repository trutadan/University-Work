import 'package:flutter/material.dart';
import 'package:logger/logger.dart';

import 'exercise_model.dart';
import 'exercise_repository.dart';

class ExerciseViewModel extends ChangeNotifier {
  final ExerciseRepository _repository = ExerciseRepository();
  final Logger _logger = Logger();
  List<Exercise> _exercises = [];

  List<Exercise> get exercises => _exercises;

  ExerciseViewModel() {
    loadExercises();
  }

  Future<void> loadExercises() async {
    try {
      _logger.d("Loading exercises in view model...");
      _exercises = await _repository.getExercises();
      notifyListeners();
      _logger.d("Exercises loaded successfully: ${_exercises.length} exercises");
    } catch (e) {
      _logger.e("Error loading exercises in view model: $e");
      rethrow;
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
      rethrow;
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
      rethrow;
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
      rethrow;
    }
  }

  Future<Exercise?> getExerciseById(int id) async {
    try {
      _logger.d("Getting exercise by id in view model... $id");
      return await _repository.getExerciseById(id);
    } catch (e) {
      _logger.e("Error getting exercise by id in view model: $e");
      rethrow;
    }
  }
}
