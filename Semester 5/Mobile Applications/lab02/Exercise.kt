package com.example.lab01.data

import androidx.compose.runtime.Immutable

@Immutable
data class Exercise(
    var id: Int,
    val name: String,
    val description: String,
    val category: String,
    val primaryMuscle: String,
    val secondaryMuscles: List<String>,
    val equipment: List<String>,
    val image: String
)
