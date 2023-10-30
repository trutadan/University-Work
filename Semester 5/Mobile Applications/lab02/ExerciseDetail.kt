package com.example.lab01.ui.screens

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Card
import androidx.compose.material3.FilledTonalButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.runtime.getValue
import androidx.compose.runtime.setValue
import androidx.compose.ui.draw.clip
import androidx.compose.ui.res.painterResource
import androidx.navigation.NavHostController
import coil.compose.rememberAsyncImagePainter
import com.example.lab01.R
import com.example.lab01.data.Exercise
import com.example.lab01.ui.components.GenericTopNavigationBar

@Composable
fun ExerciseDetail(
    exerciseId: Int,
    navController: NavHostController,
    getExercise: (Int) -> Exercise?,
    deleteExercise: (Int) -> Unit
) {
    val exercise = getExercise(exerciseId)
    var showDeleteDialog by remember { mutableStateOf(false) }

    exercise?.let { selectedExercise ->
        Column(
            modifier = Modifier.fillMaxSize()
        ) {
            GenericTopNavigationBar(navController, "Exercise details")

            ExerciseDetailCard(exercise = selectedExercise)

            ActionButtons(
                onDeleteClick = { showDeleteDialog = true },
                onUpdateClick = { navController.navigate("exerciseUpdate/$exerciseId") }
            )

            if (showDeleteDialog) {
                DeleteConfirmationDialog(
                    onConfirmDelete = {
                        deleteExercise(exerciseId)
                        showDeleteDialog = false
                        navController.popBackStack()
                    },
                    onDismiss = { showDeleteDialog = false }
                )
            }
        }
    }
}

@Composable
fun ExerciseDetailCard(exercise: Exercise) {
    Card(
        modifier = Modifier.fillMaxWidth().padding(16.dp)
    ) {
        Column(modifier = Modifier.padding(16.dp)) {
            ExerciseImage(exercise.image)

            Text(
                text = exercise.name,
                style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 24.sp),
            )

            Spacer(modifier = Modifier.height(16.dp))

            Text(
                text = "Category: ${exercise.category}",
                style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 18.sp),
            )

            Spacer(modifier = Modifier.height(8.dp))

            Text(
                text = exercise.description,
                style = TextStyle(fontSize = 18.sp),
            )

            Spacer(modifier = Modifier.height(16.dp))

            Text(
                text = "Primary Muscle: ${exercise.primaryMuscle}",
                style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 18.sp),
            )

            Spacer(modifier = Modifier.height(8.dp))

            Text(
                text = "Secondary Muscles: ${exercise.secondaryMuscles.joinToString(", ")}",
                style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 18.sp),
            )

            Spacer(modifier = Modifier.height(8.dp))

            Text(
                text = "Equipment: ${exercise.equipment.joinToString(", ")}",
                style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 18.sp),
            )
        }
    }
}

@Composable
fun ExerciseImage(imageUrl: String) {
    Image(
        painter = if (imageUrl.isEmpty()) {
            painterResource(id = R.drawable.ic_launcher_foreground)
        } else {
            rememberAsyncImagePainter(model = imageUrl)
        },
        contentDescription = "",
        modifier = Modifier.fillMaxWidth().height(200.dp)
            .clip(MaterialTheme.shapes.medium)
    )
}

@Composable
fun ActionButtons(
    onDeleteClick: () -> Unit,
    onUpdateClick: () -> Unit
) {
    Row(modifier = Modifier.fillMaxWidth().padding(16.dp)) {
        FilledTonalButton(
            onClick = onDeleteClick,
            modifier = Modifier.weight(1f).padding(end = 8.dp)
        ) {
            Text(text = "DELETE", color = Color.Red)
        }

        FilledTonalButton(
            onClick = onUpdateClick,
            modifier = Modifier.weight(1f).padding(start = 8.dp)
        ) {
            Text(text = "UPDATE", color = Color.Blue)
        }
    }
}

@Composable
fun DeleteConfirmationDialog(
    onConfirmDelete: () -> Unit,
    onDismiss: () -> Unit
) {
    AlertDialog(
        onDismissRequest = onDismiss,
        title = { Text("Confirm delete") },
        text = { Text("Are you sure you want to delete this exercise?") },
        confirmButton = {
            TextButton(
                onClick = onConfirmDelete
            ) {
                Text("Yes")
            }
        },
        dismissButton = {
            TextButton(
                onClick = onDismiss
            ) {
                Text("No")
            }
        }
    )
}