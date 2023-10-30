package com.example.lab01.ui.screens

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Card
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import com.example.lab01.data.ExerciseViewModel
import com.example.lab01.ui.components.GenericTopNavigationBar

@Composable
fun ExerciseDetail(exerciseId: Int, navController: NavHostController, exerciseViewModel: ExerciseViewModel) {
    val exercise = exerciseViewModel.getExerciseById(exerciseId)

    exercise?.let { selectedExercise ->
        Column(
            modifier = Modifier.fillMaxSize()
        ) {
            GenericTopNavigationBar(navController, exercise.name)

            Card(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(16.dp)
            ) {
                Column(
                    modifier = Modifier
                        .padding(16.dp)
                ) {
                    Text(
                        text = selectedExercise.name,
                        style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 24.sp),
                    )
                    Spacer(modifier = Modifier.height(16.dp))
                    Text(
                        text = "Category: ${selectedExercise.category}",
                        style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 18.sp),
                    )
                    Spacer(modifier = Modifier.height(8.dp))
                    Text(
                        text = selectedExercise.description,
                        style = TextStyle(fontSize = 18.sp),
                    )
                }
            }
        }
    }
}
