import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart'; // Assuming you're using Provider for state management
import 'exercise_model.dart';
import 'exercise_view_model.dart';
import 'navigation_bars.dart'; // Import your Exercise model

class ExerciseDetailScreen extends StatelessWidget {
  const ExerciseDetailScreen({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final Map<String, dynamic> args = ModalRoute.of(context)!.settings.arguments as Map<String, dynamic>;
    final int exerciseId = args['exerciseId'];

    return ExerciseDetailBody(exerciseId: exerciseId);
  }
}

class ExerciseDetailBody extends StatelessWidget {
  final int exerciseId;

  const ExerciseDetailBody({Key? key, required this.exerciseId}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var viewModel = Provider.of<ExerciseViewModel>(context);
    var exercise = viewModel.getExerciseById(exerciseId);

    return exercise != null
        ? Scaffold(
      body: Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          const TopNavigationBar(title: 'Exercise Details'),

          ExerciseDetailCard(exercise: exercise),

          ActionButtons(
            onDeleteClick: () {
              showDeleteConfirmationDialog(context, viewModel);
            },
            onUpdateClick: () {
              Navigator.pushNamed(
                context,
                '/exerciseUpdate',
                arguments: {'exerciseId': exerciseId},
              );
            },
          ),
        ],
      ),
    )
        : Container();
  }

  void showDeleteConfirmationDialog(BuildContext context, ExerciseViewModel viewModel) {
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Confirm delete'),
        content: const Text('Are you sure you want to delete this exercise?'),
        actions: [
          TextButton(
            onPressed: () {
              Navigator.of(context).pop();
            },
            child: const Text('No'),
          ),

          TextButton(
            onPressed: () {
              viewModel.deleteExercise(exerciseId);
              Navigator.of(context).pop();
              Navigator.of(context).pop();
            },
            child: const Text('Yes'),
          ),
        ],
      ),
    );
  }
}

class ExerciseDetailCard extends StatelessWidget {
  final Exercise exercise;

  const ExerciseDetailCard({Key? key, required this.exercise}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Card(
      margin: const EdgeInsets.all(16.0),
      child: Column(
        children: [
          ExerciseImage(imageUrl: exercise.image!),
          Padding(
            padding: const EdgeInsets.all(16.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  exercise.name,
                  style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 24.0),
                ),

                const SizedBox(height: 8.0),
                Text(
                  exercise.description,
                  style: const TextStyle(fontSize: 18.0),
                ),

                const SizedBox(height: 16.0),
                Text(
                  'Category: ${exercise.category}',
                  style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 18.0),
                ),

                const SizedBox(height: 16.0),
                Text(
                  'Primary Muscle: ${exercise.primaryMuscle}',
                  style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 18.0),
                ),

                const SizedBox(height: 8.0),
                Text(
                  'Secondary Muscles: ${exercise.secondaryMuscles.join(', ')}',
                  style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 18.0),
                ),

                const SizedBox(height: 8.0),
                Text(
                  'Equipment: ${exercise.equipment.join(', ')}',
                  style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 18.0),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}

class ExerciseImage extends StatelessWidget {
  final String imageUrl;

  const ExerciseImage({Key? key, required this.imageUrl}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      height: 150.0,
      width: 200.0,
      decoration: BoxDecoration(
        shape: BoxShape.rectangle,
        image: DecorationImage(
          fit: BoxFit.cover,
          image: imageUrl.isEmpty
              ? const AssetImage('images/default_image.jpg')
              : (kIsWeb
              ? NetworkImage(imageUrl)
              : FileImage(File(imageUrl))) as ImageProvider<Object>,
        ),
      ),
    );
  }
}

class ActionButtons extends StatelessWidget {
  final VoidCallback onDeleteClick;
  final VoidCallback onUpdateClick;

  const ActionButtons({
    Key? key,
    required this.onDeleteClick,
    required this.onUpdateClick,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceAround,
      children: [
        ElevatedButton(
          onPressed: onDeleteClick,
          style: ElevatedButton.styleFrom(backgroundColor: Colors.red),
          child: const Text('DELETE'),
        ),

        ElevatedButton(
          onPressed: onUpdateClick,
          style: ElevatedButton.styleFrom(backgroundColor: Colors.blue),
          child: const Text('UPDATE'),
        ),
      ],
    );
  }
}
