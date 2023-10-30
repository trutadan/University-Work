package com.example.lab01.data

import androidx.compose.runtime.Immutable

@Immutable
data class Exercise(
    val id: Int,
    val name: String,
    val description: String,
    val category: String,
    val primaryMuscles: List<String>,
    val secondaryMuscles: List<String>,
    val equipment: List<String>,
    val image: Int
)
