import 'dart:io';
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:logger/logger.dart';

import 'exercise_view_model.dart';
import 'exercise_model.dart';
import 'navigation_bars.dart';

final Logger _logger = Logger();

class ExerciseListScreen extends StatefulWidget {
  const ExerciseListScreen({Key? key}) : super(key: key);

  @override
  _ExerciseListScreenState createState() => _ExerciseListScreenState();
}

class _ExerciseListScreenState extends State<ExerciseListScreen> {
  String searchText = '';

  void filterExercises(String text) {
    setState(() {
      searchText = text;
    });
    _logger.d('Filtered exercises with text: $text');
  }

  @override
  Widget build(BuildContext context) {
    _logger.d('Building ExerciseListScreen');
    return Scaffold(
      body: Column(
        children: [
          const TopNavigationBar(title: "Exercises"),

          SearchTextField(onChanged: filterExercises),

          Expanded(
            child: ExerciseListView(searchText: searchText),
          ),

          const CreateExerciseNavigationBar(),
        ],
      ),
    );
  }
}

class SearchTextField extends StatelessWidget {
  final ValueChanged<String> onChanged;

  const SearchTextField({super.key, required this.onChanged});

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: const EdgeInsets.all(8),
      child: TextField(
        onChanged: onChanged,
        decoration: const InputDecoration(
          labelText: 'Search exercise',
          prefixIcon: Icon(
            Icons.search,
            color: Colors.grey,
          ),
          border: OutlineInputBorder(),
        ),
      ),
    );
  }
}

class ExerciseListView extends StatelessWidget {
  final String searchText;

  const ExerciseListView({super.key, required this.searchText});

  @override
  Widget build(BuildContext context) {
    _logger.d('Building ExerciseListView');
    final exerciseViewModel = Provider.of<ExerciseViewModel>(context);
    final filteredExercises = exerciseViewModel.exercises
        .where((exercise) => exercise.name.toLowerCase().contains(searchText.toLowerCase()))
        .toList();

    return ListView.builder(
      itemCount: filteredExercises.length,
      itemBuilder: (context, index) {
        final exercise = filteredExercises[index];
        _logger.d('Building ExerciseItem for ${exercise.name}');
        return ExerciseItem(
          exercise: exercise,
          onTap: () {
            Navigator.pushNamed(
              context,
              '/exerciseDetail',
              arguments: {'exerciseId': exercise.id},
            );
          },
        );
      },
    );
  }
}

class ExerciseItem extends StatelessWidget {
  final Exercise exercise;
  final VoidCallback onTap;

  const ExerciseItem({super.key, required this.exercise, required this.onTap});

  @override
  Widget build(BuildContext context) {
    _logger.d('Building ExerciseItem for ${exercise.name}');
    return Card(
      margin: const EdgeInsets.all(8),
      child: ListTile(
        onTap: onTap,
        leading: CircleAvatar(
          radius: 30,
          backgroundImage: exercise.image?.isEmpty ?? true
              ? const AssetImage('images/default_image.jpg')
              : (kIsWeb
              ? NetworkImage(exercise.image!)
              : FileImage(File(exercise.image!))) as ImageProvider<Object>,
        ),
        title: Text(
          exercise.name,
          style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 18),
        ),
        subtitle: Text(
          exercise.primaryMuscle,
          style: const TextStyle(fontSize: 18),
        ),
        trailing: const Icon(
          Icons.keyboard_arrow_right,
          size: 30,
          color: Colors.grey,
        ),
      ),
    );
  }
}
