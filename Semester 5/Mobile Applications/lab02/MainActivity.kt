package com.example.lab01

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.navigation.compose.NavHost
import androidx.navigation.NavHostController
import androidx.navigation.NavType
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.navigation.navArgument
import com.example.lab01.data.ExerciseViewModel
import com.example.lab01.ui.screens.ExerciseCreate
import com.example.lab01.ui.screens.ExerciseDetail
import com.example.lab01.ui.screens.ExerciseList
import com.example.lab01.ui.screens.ExerciseUpdate
import com.example.lab01.ui.theme.Lab01Theme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            Lab01Theme {
                MyApp(modifier = Modifier.fillMaxSize())
            }
        }
    }
}

@Composable
fun AppNavigation(navController: NavHostController, exerciseViewModel: ExerciseViewModel) {
    NavHost(navController = navController, startDestination = "exerciseList") {
        composable("exerciseList") {
            ExerciseList(exerciseViewModel, navController)
        }
        composable("exerciseDetail/{exerciseId}",
            arguments = listOf(navArgument("exerciseId") { type = NavType.IntType })
        ) { backStackEntry ->
            val exerciseId = backStackEntry.arguments?.getInt("exerciseId")
            exerciseId?.let { ExerciseDetail(it, navController, exerciseViewModel) }
        }
        composable("exerciseCreate") {
            ExerciseCreate(navController, exerciseViewModel)
        }
        composable("exerciseUpdate/{exerciseId}",
            arguments = listOf(navArgument("exerciseId") { type = NavType.IntType })
        ) { backStackEntry ->
            val exerciseId = backStackEntry.arguments?.getInt("exerciseId")
            exerciseId?.let { ExerciseUpdate(it, navController, exerciseViewModel) }
        }
    }
}

@Composable
fun MyApp(modifier: Modifier = Modifier) {
    Surface(modifier, color = MaterialTheme.colorScheme.background) {
        val navController = rememberNavController()
        val exerciseViewModel = ExerciseViewModel()
        AppNavigation(navController, exerciseViewModel)
    }
}