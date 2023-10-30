package com.example.lab01.ui.components

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material3.FilledTonalButton
import androidx.compose.material3.Icon
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.navigation.NavHostController
import com.example.lab01.R

@Composable
fun GenericTopNavigationBar(navController: NavHostController, titleContent: String, modifier: Modifier = Modifier) {
    Surface(
        color = Color.Black,
        modifier = modifier
            .fillMaxWidth()
            .height(60.dp)
    ) {
        Row(
            modifier = Modifier.fillMaxSize(),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Icon(
                painter = painterResource(id = R.drawable.home_icon),
                contentDescription = null,
                tint = Color.White,
                modifier = Modifier
                    .padding(10.dp)
                    .size(30.dp)
                    .clickable {
                        navController.navigate("exerciseList")
                    }
            )

            Spacer(modifier = Modifier.weight(1f))

            Text(
                text = titleContent,
                color = Color.White
            )

            Spacer(modifier = Modifier.weight(1f))

            Icon(
                painter = painterResource(id = R.drawable.settings_icon),
                contentDescription = null,
                tint = Color.White,
                modifier = Modifier
                    .padding(10.dp)
                    .size(30.dp)
            )
        }
    }
}

@Composable
fun ExerciseModificationTopNavigationBar(navController: NavHostController, titleContent: String, onSaveClick: () -> Unit, modifier: Modifier = Modifier) {
    Surface(
        color = Color.Black,
        modifier = modifier
            .fillMaxWidth()
            .height(60.dp)
    ) {
        Row(
            modifier = Modifier.fillMaxSize(),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Icon(
                painter = painterResource(id = R.drawable.home_icon),
                contentDescription = null,
                tint = Color.White,
                modifier = Modifier
                    .padding(10.dp)
                    .size(30.dp)
                    .clickable {
                        navController.navigate("exerciseList")
                    }
            )

            Spacer(modifier = Modifier.weight(1f))

            Text(
                text = titleContent,
                color = Color.White
            )

            Spacer(modifier = Modifier.weight(1f))

            Text(
                text = "Save",
                color = Color.Cyan,
                fontWeight = FontWeight.Bold,
                modifier = Modifier.padding(10.dp).clickable { onSaveClick() }
            )
        }
    }
}

@Composable
fun CreateExerciseNavigationBar(navController: NavHostController, modifier: Modifier = Modifier) {
    Surface(
        color = Color.Black,
        modifier = modifier
            .fillMaxWidth()
            .height(30.dp)
    ) {
        Row(
            modifier = Modifier.fillMaxSize(),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Spacer(modifier = Modifier.weight(1f))

            FilledTonalButton(
                onClick = { navController.navigate("exerciseCreate") },
            ) {
                Text(
                    text = "New exercise",
                    color = Color.Black,
                )
            }

            Spacer(modifier = Modifier.weight(1f))
        }
    }
}
