import 'package:flutter/cupertino.dart';

import 'exercise_model.dart';

class ExerciseViewModel extends ChangeNotifier {
  final List<Exercise> _exercises = [
    Exercise(
      id: 1,
      name: "Bench Press",
      description: "A compound exercise for building upper body strength.",
      category: "Strength",
      primaryMuscle: "Pectoralis Major",
      secondaryMuscles: ["Anterior Deltoids", "Triceps"],
      equipment: ["Barbell", "Bench"],
      image: "",
    ),
    Exercise(
      id: 2,
      name: "Squats",
      description: "A fundamental lower body exercise for building leg strength.",
      category: "Strength",
      primaryMuscle: "Quadriceps",
      secondaryMuscles: ["Glutes", "Hamstrings"],
      equipment: ["Barbell", "Squat Rack"],
      image: "",
    ),
    Exercise(
      id: 3,
      name: "Running",
      description: "An effective cardiovascular exercise for improving endurance.",
      category: "Cardio",
      primaryMuscle: "Cardiovascular System",
      secondaryMuscles: [],
      equipment: ["Running Shoes"],
      image: "",
    ),
    Exercise(
      id: 4,
      name: "Deadlift",
      description: "A compound exercise for developing overall strength and power.",
      category: "Strength",
      primaryMuscle: "Erector Spinae",
      secondaryMuscles: ["Glutes", "Hamstrings", "Quadriceps"],
      equipment: ["Barbell"],
      image: "",
    ),
    Exercise(
      id: 5,
      name: "Push-Ups",
      description: "A bodyweight exercise for building chest and tricep strength.",
      category: "Strength",
      primaryMuscle: "Pectoralis Major",
      secondaryMuscles: ["Triceps", "Deltoids", "Serratus Anterior"],
      equipment: [],
      image: "",
    ),
    Exercise(
      id: 6,
      name: "Yoga",
      description: "A practice for improving flexibility, balance, and relaxation.",
      category: "Flexibility",
      primaryMuscle: "",
      secondaryMuscles: [],
      equipment: [],
      image: "",
    ),
    Exercise(
      id: 7,
      name: "Cycling",
      description: "A great cardiovascular exercise that's easy on the joints.",
      category: "Cardio",
      primaryMuscle: "Quadriceps",
      secondaryMuscles: ["Hamstrings", "Calves", "Glutes"],
      equipment: ["Bicycle"],
      image: "",
    ),
    Exercise(
      id: 8,
      name: "Dumbbell Rows",
      description: "An exercise for developing upper back and arm strength.",
      category: "Strength",
      primaryMuscle: "Latissimus Dorsi",
      secondaryMuscles: ["Rhomboids", "Traps", "Biceps"],
      equipment: ["Dumbbell", "Bench"],
      image: "",
    ),
    Exercise(
      id: 9,
      name: "Jumping Jacks",
      description: "A simple and effective cardio exercise for all fitness levels.",
      category: "Cardio",
      primaryMuscle: "",
      secondaryMuscles: [],
      equipment: [],
      image: "",
    ),
    Exercise(
      id: 10,
      name: "Plank",
      description: "A core-strengthening exercise for building stability and endurance.",
      category: "Strength",
      primaryMuscle: "Core",
      secondaryMuscles: [],
      equipment: [],
      image: "",
    ),
  ];

  List<Exercise> get exercises => _exercises;

  void addExercise(Exercise newExercise) {
    newExercise.id = _generateUniqueId();
    _exercises.add(newExercise);
    notifyListeners();
  }

  int _generateUniqueId() {
    final maxId = _exercises.isEmpty ? 0 : _exercises.map((exercise) => exercise.id).reduce((a, b) => a > b ? a : b);
    return maxId + 1;
  }

  Exercise? getExerciseById(int exerciseId) {
    try {
      return _exercises.firstWhere((exercise) => exercise.id == exerciseId);
    } catch (exception) {
      return null;
    }
  }

  void deleteExercise(int exerciseId) {
    _exercises.removeWhere((exercise) => exercise.id == exerciseId);
    notifyListeners();
  }

  void updateExercise(Exercise updatedExercise) {
    final index = _exercises.indexWhere((exercise) => exercise.id == updatedExercise.id);
    if (index != -1) {
      _exercises[index] = updatedExercise;
      notifyListeners();
    }
  }
}