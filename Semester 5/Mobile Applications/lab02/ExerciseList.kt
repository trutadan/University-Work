package com.example.lab01.ui.screens

import androidx.compose.foundation.Image
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.KeyboardArrowRight
import androidx.compose.material3.Card
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import com.example.lab01.data.Exercise
import com.example.lab01.data.ExerciseViewModel
import com.example.lab01.ui.components.CreateExerciseNavigationBar
import com.example.lab01.ui.components.GenericTopNavigationBar

@Composable
fun ExerciseItem(exercise: Exercise, onClick: () -> Unit) {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .clickable(onClick = onClick)
            .padding(8.dp)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp),
            verticalAlignment = Alignment.CenterVertically
        ) {
            if (exercise.image != 0) {
                Image(
                    painter = painterResource(id = exercise.image),
                    contentDescription = exercise.name,
                    modifier = Modifier
                        .size(80.dp)
                        .clip(CircleShape)
                )
            }

            Spacer(modifier = Modifier.width(8.dp))

            Column {
                Text(
                    text = exercise.name,
                    style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 18.sp)
                )

                Text(
                    text = exercise.primaryMuscles.firstOrNull() ?: "",
                    style = TextStyle(fontSize = 18.sp)
                )
            }

            Spacer(modifier = Modifier.weight(1f))

            Icon(
                imageVector = Icons.Default.KeyboardArrowRight,
                contentDescription = null,
                tint = Color.Gray,
                modifier = Modifier.size(30.dp),
            )
        }
    }
}

@Composable
fun ExerciseList(exerciseViewModel: ExerciseViewModel, navController: NavHostController) {
    val exercises = exerciseViewModel.exercises.value

    Column(
        modifier = Modifier.fillMaxSize(),
    ) {
        GenericTopNavigationBar(navController, "Exercises")

        Box(
            modifier = Modifier
                .weight(1f)
        ) {
            LazyColumn {
                items(exercises) { exercise ->
                    ExerciseItem(exercise = exercise, onClick = {
                        navController.navigate("exerciseDetail/${exercise.id}")
                    })
                }
            }
        }

        CreateExerciseNavigationBar(navController)
    }
}
