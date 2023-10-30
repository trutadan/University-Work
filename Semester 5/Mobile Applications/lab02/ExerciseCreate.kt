package com.example.lab01.ui.screens

import android.net.Uri
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import androidx.compose.runtime.getValue
import androidx.compose.runtime.setValue
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import coil.compose.rememberAsyncImagePainter
import com.example.lab01.R
import com.example.lab01.data.Exercise
import com.example.lab01.ui.components.ExerciseModificationTopNavigationBar

@Composable
fun ExerciseCreate(
    navController: NavHostController,
    addExercise: (Exercise) -> Unit
) {
    var name by remember { mutableStateOf("") }
    var nameError by remember { mutableStateOf("") }

    var description by remember { mutableStateOf("") }
    var descriptionError by remember { mutableStateOf("") }

    var category by remember { mutableStateOf("") }
    var categoryError by remember { mutableStateOf("") }

    var primaryMuscle by remember { mutableStateOf("") }
    var primaryMuscleError by remember { mutableStateOf("") }

    var secondaryMuscles by remember { mutableStateOf("") }
    var secondaryMusclesError by remember { mutableStateOf("") }

    var equipment by remember { mutableStateOf("") }
    var equipmentError by remember { mutableStateOf("") }

    var selectedImageUri by remember { mutableStateOf<Uri?>(null) }
    var isEditingImage by remember { mutableStateOf(false) }

    val image = if (selectedImageUri != null) {
        selectedImageUri.toString()
    } else {
        ""
    }

    val imagePicker = rememberLauncherForActivityResult(ActivityResultContracts.GetContent()) { uri: Uri? ->
        if (uri != null) {
            selectedImageUri = uri
        }
    }

    Column(
        modifier = Modifier.fillMaxWidth().verticalScroll(rememberScrollState()),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Top
    ) {
        ExerciseModificationTopNavigationBar(navController, "Create exercise", {
            val isNameValid = name.isNotBlank()
            val isDescriptionValid = description.isNotBlank()
            val isCategoryValid = category.isNotBlank()
            val isPrimaryMuscleValid = primaryMuscle.isNotBlank()
            val isSecondaryMusclesValid = secondaryMuscles.isNotBlank()
            val isEquipmentValid = equipment.isNotBlank()

            if (isNameValid && isDescriptionValid && isCategoryValid && isPrimaryMuscleValid && isSecondaryMusclesValid && isEquipmentValid) {
                val newExercise = Exercise(
                    id = 0,
                    name = name,
                    description = description,
                    category = category,
                    primaryMuscle = primaryMuscle,
                    secondaryMuscles = secondaryMuscles.split(", ").map { it.trim() },
                    equipment = equipment.split(", ").map { it.trim() },
                    image = image
                )

                addExercise(newExercise)
                navController.popBackStack()
            } else {
                nameError = if (!isNameValid) "Name is required" else ""
                descriptionError = if (!isDescriptionValid) "Description is required" else ""
                categoryError = if (!isCategoryValid) "Category is required" else ""
                primaryMuscleError = if (!isPrimaryMuscleValid) "Primary muscle is required" else ""
                secondaryMusclesError = if (!isSecondaryMusclesValid) "Secondary muscles are required" else ""
                equipmentError = if (!isEquipmentValid) "Equipment is required" else ""
            }
        })

        Spacer(modifier = Modifier.height(8.dp))

        Box(
            modifier = Modifier
                .size(150.dp)
                .clip(CircleShape)
                .background(Color.Gray)
        ) {
            if (selectedImageUri != null) {
                Image(
                    painter = rememberAsyncImagePainter(model = selectedImageUri),
                    contentDescription = "Exercise Image",
                    modifier = Modifier.fillMaxSize().clickable {
                        isEditingImage = true
                    }
                )
            } else {
                Image(
                    painter = if (image.isEmpty()) {
                        painterResource(id = R.drawable.ic_launcher_foreground)
                    } else {
                        rememberAsyncImagePainter(model = image)
                    },
                    contentDescription = "Exercise Image",
                    modifier = Modifier.fillMaxSize().clickable {
                        isEditingImage = true
                    }
                )
            }

            if (isEditingImage) {
                Button(
                    onClick = {
                        imagePicker.launch("image/*")
                        isEditingImage = false
                    },
                    modifier = Modifier
                        .align(Alignment.BottomCenter)
                        .padding(8.dp)
                ) {
                    Text(text = "Add image", fontSize = 12.sp)
                }
            }
        }

        ExerciseAttributeCreateTextField("Name", name) { name = it }
        if (nameError.isNotEmpty()) {
            Text(text = nameError, color = Color.Red)
        }

        ExerciseAttributeCreateTextField("Description", description) { description = it }
        if (equipmentError.isNotEmpty()) {
            Text(text = equipmentError, color = Color.Red)
        }

        ExerciseAttributeCreateTextField("Category", category) { category = it }
        if (categoryError.isNotEmpty()) {
            Text(text = categoryError, color = Color.Red)
        }

        ExerciseAttributeCreateTextField("Primary Muscle", primaryMuscle) { primaryMuscle = it }
        if (primaryMuscleError.isNotEmpty()) {
            Text(text = primaryMuscleError, color = Color.Red)
        }

        ExerciseAttributeCreateTextField("Secondary Muscles", secondaryMuscles) { secondaryMuscles = it }
        if (secondaryMusclesError.isNotEmpty()) {
            Text(text = secondaryMusclesError, color = Color.Red)
        }

        ExerciseAttributeCreateTextField("Equipment", equipment) { equipment = it }
        if (equipmentError.isNotEmpty()) {
            Text(text = equipmentError, color = Color.Red)
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun ExerciseAttributeCreateTextField(
    label: String,
    value: String,
    onValueChange: (String) -> Unit
) {
    OutlinedTextField(
        value = value,
        onValueChange = onValueChange,
        label = { Text(label) },
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp)
    )
}