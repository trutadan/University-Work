import 'dart:io';
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:logger/logger.dart';
import 'exercise_model.dart';
import 'exercise_view_model.dart';
import 'navigation_bars.dart';

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
  final Logger _logger = Logger();

  ExerciseDetailBody({Key? key, required this.exerciseId}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var viewModel = Provider.of<ExerciseViewModel>(context);

    return FutureBuilder<Exercise?>(
      future: viewModel.getExerciseById(exerciseId),
      builder: (context, snapshot) {
        _logger.d('Exercise Detail Body - Building FutureBuilder');
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const CircularProgressIndicator();
        } else if (snapshot.hasError || snapshot.data == null) {
          _logger.e('Error loading exercise: ${snapshot.error}');
          return const Text('Error loading exercise!');
        } else {
          Exercise exercise = snapshot.data!;
          return Scaffold(
            body: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [
                const TopNavigationBar(title: 'Exercise Details'),
                ExerciseDetailCard(exercise: exercise),
                ActionButtons(
                  onDeleteClick: () {
                    _logger.d('Delete button clicked');
                    showDeleteConfirmationDialog(context, viewModel);
                  },
                  onUpdateClick: () {
                    _logger.d('Update button clicked');
                    Navigator.pushNamed(
                      context,
                      '/exerciseUpdate',
                      arguments: {'exerciseId': exerciseId},
                    );
                  },
                ),
              ],
            ),
          );
        }
      },
    );
  }

  void showDeleteConfirmationDialog(BuildContext context, ExerciseViewModel viewModel) {
    _logger.d('Showing delete confirmation dialog');
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Confirm delete'),
        content: const Text('Are you sure you want to delete this exercise?'),
        actions: [
          TextButton(
            onPressed: () {
              _logger.d('Delete cancelled');
              Navigator.of(context).pop();
            },
            child: const Text('No'),
          ),

          TextButton(
            onPressed: () {
              _logger.d('Delete confirmed');
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
  final Logger _logger = Logger();

  ExerciseDetailCard({Key? key, required this.exercise}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    _logger.d('Exercise Detail Card - Building exercise detail card');
    return Card(
      margin: const EdgeInsets.all(16.0),
      child: Column(
        children: [
          ExerciseImage(imageUrl: exercise.image),
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
  final String? imageUrl;
  final Logger _logger = Logger();

  ExerciseImage({Key? key, required this.imageUrl}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    _logger.d('Exercise Image - Building exercise image');
    return Container(
      height: 150.0,
      width: 200.0,
      decoration: BoxDecoration(
        shape: BoxShape.rectangle,
        image: DecorationImage(
          fit: BoxFit.cover,
          image: imageUrl == null || imageUrl!.isEmpty
              ? const AssetImage('images/default_image.jpg')
              : (kIsWeb
              ? NetworkImage(imageUrl!)
              : FileImage(File(imageUrl!))) as ImageProvider<Object>,
        ),
      ),
    );
  }
}

class ActionButtons extends StatelessWidget {
  final VoidCallback onDeleteClick;
  final VoidCallback onUpdateClick;
  final Logger _logger = Logger();

  ActionButtons({
    Key? key,
    required this.onDeleteClick,
    required this.onUpdateClick,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    _logger.d('Action Buttons - Building action buttons');
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
