package com.example.lab01.data

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel

class ExerciseViewModel : ViewModel() {
    private val _exercises = mutableStateOf(
        listOf(
            Exercise(
                id = 1,
                name = "Bench Press",
                description = "A compound exercise for building upper body strength.",
                category = "Strength",
                primaryMuscle = "Pectoralis Major",
                secondaryMuscles = listOf("Anterior Deltoids", "Triceps"),
                equipment = listOf("Barbell", "Bench"),
                image = ""
            ),
            Exercise(
                id = 2,
                name = "Squats",
                description = "A fundamental lower body exercise for building leg strength.",
                category = "Strength",
                primaryMuscle = "Quadriceps",
                secondaryMuscles = listOf("Glutes", "Hamstrings"),
                equipment = listOf("Barbell", "Squat Rack"),
                image = ""
            ),
            Exercise(
                id = 3,
                name = "Running",
                description = "An effective cardiovascular exercise for improving endurance.",
                category = "Cardio",
                primaryMuscle = "Cardiovascular System",
                secondaryMuscles = emptyList(),
                equipment = listOf("Running Shoes"),
                image = ""
            ),
            Exercise(
                id = 4,
                name = "Deadlift",
                description = "A compound exercise for developing overall strength and power.",
                category = "Strength",
                primaryMuscle = "Erector Spinae",
                secondaryMuscles = listOf("Glutes", "Hamstrings", "Quadriceps"),
                equipment = listOf("Barbell"),
                image = ""
            ),
            Exercise(
                id = 5,
                name = "Push-Ups",
                description = "A bodyweight exercise for building chest and tricep strength.",
                category = "Strength",
                primaryMuscle = "Pectoralis Major",
                secondaryMuscles = listOf("Triceps", "Deltoids", "Serratus Anterior"),
                equipment = emptyList(),
                image = ""
            ),
            Exercise(
                id = 6,
                name = "Yoga",
                description = "A practice for improving flexibility, balance, and relaxation.",
                category = "Flexibility",
                primaryMuscle = "",
                secondaryMuscles = emptyList(),
                equipment = emptyList(),
                image = ""
            ),
            Exercise(
                id = 7,
                name = "Cycling",
                description = "A great cardiovascular exercise that's easy on the joints.",
                category = "Cardio",
                primaryMuscle = "Quadriceps",
                secondaryMuscles = listOf("Hamstrings", "Calves", "Glutes"),
                equipment = listOf("Bicycle"),
                image = ""
            ),
            Exercise(
                id = 8,
                name = "Dumbbell Rows",
                description = "An exercise for developing upper back and arm strength.",
                category = "Strength",
                primaryMuscle = "Latissimus Dorsi",
                secondaryMuscles = listOf("Rhomboids", "Traps", "Biceps"),
                equipment = listOf("Dumbbell", "Bench"),
                image = ""
            ),
            Exercise(
                id = 9,
                name = "Jumping Jacks",
                description = "A simple and effective cardio exercise for all fitness levels.",
                category = "Cardio",
                primaryMuscle = "",
                secondaryMuscles = emptyList(),
                equipment = emptyList(),
                image = ""
            ),
            Exercise(
                id = 10,
                name = "Plank",
                description = "A core-strengthening exercise for building stability and endurance.",
                category = "Strength",
                primaryMuscle = "Core",
                secondaryMuscles = emptyList(),
                equipment = emptyList(),
                image = ""
            )
        )
    )

    val exercises: State<List<Exercise>> = _exercises

    fun getExerciseById(exerciseId: Int): Exercise? {
        val exercisesList = exercises.value
        return exercisesList.find { it.id == exerciseId }
    }

    fun deleteExercise(exerciseId: Int) {
        val currentExercises = exercises.value.toMutableList()
        val exerciseToDelete = currentExercises.find { it.id == exerciseId }

        exerciseToDelete?.let {
            currentExercises.remove(it)
            _exercises.value = currentExercises
        }
    }

    fun updateExercise(updatedExercise: Exercise) {
        val updatedList = exercises.value.toMutableList()
        val index = updatedList.indexOfFirst { it.id == updatedExercise.id }

        if (index != -1) {
            updatedList[index] = updatedExercise
            _exercises.value = updatedList
        }
    }

    fun addExercise(newExercise: Exercise) {
        newExercise.id = generateUniqueId()
        _exercises.value = exercises.value + newExercise
    }

    private fun generateUniqueId(): Int {
        val maxId = exercises.value.maxByOrNull { it.id }?.id ?: 0
        return maxId + 1
    }
}
