package com.example.lab01.data

import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import com.example.lab01.R

class ExerciseViewModel : ViewModel() {
    fun getExerciseById(exerciseId: Int): Exercise? {
        val exercisesList = exercises.value
        return exercisesList.find { it.id == exerciseId }
    }

    val exercises: MutableState<List<Exercise>> = mutableStateOf(
        listOf(
            Exercise(
                id = 1,
                name = "Bench Press",
                description = "A compound exercise for building upper body strength.",
                category = "Strength",
                primaryMuscles = listOf("Pectoralis Major", "Triceps"),
                secondaryMuscles = listOf("Anterior Deltoids", "Serratus Anterior"),
                equipment = listOf("Barbell", "Bench"),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 2,
                name = "Squats",
                description = "A fundamental lower body exercise for building leg strength.",
                category = "Strength",
                primaryMuscles = listOf("Quadriceps", "Glutes"),
                secondaryMuscles = listOf("Hamstrings", "Calves"),
                equipment = listOf("Barbell", "Squat Rack"),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 3,
                name = "Running",
                description = "An effective cardiovascular exercise for improving endurance.",
                category = "Cardio",
                primaryMuscles = listOf("Cardiovascular System"),
                secondaryMuscles = emptyList(),
                equipment = listOf("Running Shoes"),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 4,
                name = "Deadlift",
                description = "A compound exercise for developing overall strength and power.",
                category = "Strength",
                primaryMuscles = listOf("Erector Spinae", "Glutes"),
                secondaryMuscles = listOf("Hamstrings", "Quadriceps"),
                equipment = listOf("Barbell"),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 5,
                name = "Push-Ups",
                description = "A bodyweight exercise for building chest and tricep strength.",
                category = "Strength",
                primaryMuscles = listOf("Pectoralis Major", "Triceps"),
                secondaryMuscles = listOf("Deltoids", "Serratus Anterior"),
                equipment = emptyList(),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 6,
                name = "Yoga",
                description = "A practice for improving flexibility, balance, and relaxation.",
                category = "Flexibility",
                primaryMuscles = emptyList(),
                secondaryMuscles = emptyList(),
                equipment = emptyList(),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 7,
                name = "Cycling",
                description = "A great cardiovascular exercise that's easy on the joints.",
                category = "Cardio",
                primaryMuscles = listOf("Quadriceps", "Hamstrings"),
                secondaryMuscles = listOf("Calves", "Glutes"),
                equipment = listOf("Bicycle"),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 8,
                name = "Dumbbell Rows",
                description = "An exercise for developing upper back and arm strength.",
                category = "Strength",
                primaryMuscles = listOf("Latissimus Dorsi", "Biceps"),
                secondaryMuscles = listOf("Rhomboids", "Traps"),
                equipment = listOf("Dumbbell", "Bench"),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 9,
                name = "Jumping Jacks",
                description = "A simple and effective cardio exercise for all fitness levels.",
                category = "Cardio",
                primaryMuscles = emptyList(),
                secondaryMuscles = emptyList(),
                equipment = emptyList(),
                image = R.drawable.ic_launcher_foreground
            ),
            Exercise(
                id = 10,
                name = "Plank",
                description = "A core-strengthening exercise for building stability and endurance.",
                category = "Strength",
                primaryMuscles = listOf("Core"),
                secondaryMuscles = emptyList(),
                equipment = emptyList(),
                image = R.drawable.ic_launcher_foreground
            )
        )
    )
}
