package com.example.lab01.ui.screens

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.navigation.NavHostController
import com.example.lab01.ui.components.ExerciseModificationTopNavigationBar

@Composable
fun ExerciseCreate(navController: NavHostController, onImageUpload: () -> Unit) {
    Column(
        modifier = Modifier.fillMaxSize()
    ) {
        ExerciseModificationTopNavigationBar(navController, "Create exercise")

        CircleImageSection(onImageUpload)
    }
}

@Composable
fun CircleImageSection(onImageUpload: () -> Unit) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .padding(16.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        // Circle image (you can replace this with your image upload logic)
        Box(
            modifier = Modifier
                .size(120.dp)
                .clip(CircleShape)
                .background(Color.Gray)
                .clickable(onClick = onImageUpload)
        ) {
            // You can display an uploaded image here or an "Add image" icon.
        }
        Text(
            text = "Add Image",
            color = Color.Cyan,
            fontWeight = FontWeight.Bold,
            modifier = Modifier.clickable(onClick = onImageUpload)
        )
    }
}
