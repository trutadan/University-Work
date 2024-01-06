import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';
import 'package:logger/logger.dart';
import 'package:provider/provider.dart';

import 'exercise_model.dart';
import 'view_model.dart';

final Logger _logger = Logger();

class ExerciseUpdateScreen extends StatefulWidget {
  const ExerciseUpdateScreen({Key? key}) : super(key: key);

  @override
  _ExerciseUpdateScreenState createState() => _ExerciseUpdateScreenState();

  static int getExerciseId(BuildContext context) {
    return (ModalRoute.of(context)!.settings.arguments as Map<String, dynamic>)['exerciseId'];
  }
}

class _ExerciseUpdateScreenState extends State<ExerciseUpdateScreen> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final TextEditingController _nameController = TextEditingController();
  final TextEditingController _descriptionController = TextEditingController();
  final TextEditingController _categoryController = TextEditingController();
  final TextEditingController _primaryMuscleController = TextEditingController();
  final TextEditingController _secondaryMusclesController = TextEditingController();
  final TextEditingController _equipmentController = TextEditingController();

  final ImagePicker _imagePicker = ImagePicker();
  String? _selectedImagePath;

  late Exercise _exercise;

  @override
  Future<void> didChangeDependencies() async {
    super.didChangeDependencies();
    final int exerciseId = ExerciseUpdateScreen.getExerciseId(context);
    _exercise = (await Provider.of<ExerciseViewModel>(context).getExerciseById(exerciseId))!;

    _nameController.text = _exercise.name;
    _descriptionController.text = _exercise.description;
    _categoryController.text = _exercise.category;
    _primaryMuscleController.text = _exercise.primaryMuscle;
    _secondaryMusclesController.text = _exercise.secondaryMuscles.join(', ');
    _equipmentController.text = _exercise.equipment.join(', ');
    _selectedImagePath = _exercise.image;

    _logger.d('ExerciseUpdateScreen: Exercise loaded for update - ID: ${_exercise.id}, Name: ${_exercise.name}');
  }

  @override
  Widget build(BuildContext context) {
    _logger.d('ExerciseUpdateScreen: Building screen for exercise update');

    return Scaffold(
      appBar: AppBar(
        title: const Center(child: Text('Update Exercise')),
        backgroundColor: Colors.black,
        actions: [
          GestureDetector(
            onTap: () {
              _updateExercise();
            },
            child: Container(
              margin: const EdgeInsets.symmetric(horizontal: 16.0),
              alignment: Alignment.center,
              child: const Text(
                'Save',
                style: TextStyle(fontSize: 18.0, color: Colors.cyan),
              ),
            ),
          ),
        ],
      ),
      body: SingleChildScrollView(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              _buildImageContainer(),
              const SizedBox(height: 16.0),
              ExerciseAttributeUpdateTextField(
                label: "Name",
                controller: _nameController,
                validator: (value) => _validateInput(value, "Name is required"),
              ),

              ExerciseAttributeUpdateTextField(
                label: "Description",
                controller: _descriptionController,
                validator: (value) => _validateInput(value, "Description is required"),
              ),

              ExerciseAttributeUpdateTextField(
                label: "Category",
                controller: _categoryController,
                validator: (value) => _validateInput(value, "Category is required"),
              ),

              ExerciseAttributeUpdateTextField(
                label: "Primary Muscle",
                controller: _primaryMuscleController,
                validator: (value) => _validateInput(value, "Primary Muscle is required"),
              ),

              ExerciseAttributeUpdateTextField(
                label: "Secondary Muscles",
                controller: _secondaryMusclesController,
                validator: (value) => _validateInput(value, "Secondary Muscles is required"),
              ),

              ExerciseAttributeUpdateTextField(
                label: "Equipment",
                controller: _equipmentController,
                validator: (value) => _validateInput(value, "Equipment is required"),
              ),
            ],
          ),
        ),
      ),
    );
  }

  Widget _buildImageContainer() {
    return Column(
      children: [
        Stack(
          alignment: Alignment.bottomCenter,
          children: [
            Container(
              height: 150.0,
              width: 150.0,
              decoration: BoxDecoration(
                color: Colors.grey,
                shape: BoxShape.circle,
                image: DecorationImage(
                  fit: BoxFit.cover,
                  image: _selectedImagePath == null
                      ? const AssetImage('images/default_image.jpg')
                      : (kIsWeb
                      ? NetworkImage(_selectedImagePath!)
                      : FileImage(File(_selectedImagePath!))) as ImageProvider<Object>,
                ),
              ),
            ),
            Positioned(
              child: TextButton(
                onPressed: () {
                  _selectImage();
                },
                style: TextButton.styleFrom(
                  backgroundColor: Colors.black,
                ),
                child: const Text('Update Photo', style: TextStyle(color: Colors.white)),
              ),
            ),
          ],
        ),
        const SizedBox(height: 8.0),
      ],
    );
  }

  void _selectImage() async {
    final pickedFile = await _imagePicker.pickImage(source: ImageSource.gallery);

    if (pickedFile != null) {
      setState(() {
        _selectedImagePath = pickedFile.path;
      });
    }
  }

  void _updateExercise() async {
    if (_formKey.currentState!.validate()) {
      final int exerciseId = _exercise.id;

      String updatedImagePath = _exercise.image ?? _selectedImagePath ?? '';

      Exercise updatedExercise = Exercise(
        id: exerciseId,
        name: _nameController.text,
        description: _descriptionController.text,
        category: _categoryController.text,
        primaryMuscle: _primaryMuscleController.text,
        secondaryMuscles: _secondaryMusclesController.text.split(',').map((e) => e.trim()).toList(),
        equipment: _equipmentController.text.split(',').map((e) => e.trim()).toList(),
        image: updatedImagePath,
      );

      Provider.of<ExerciseViewModel>(context, listen: false).updateExercise(updatedExercise);

      Navigator.of(context).pop();
    }
  }

  String? _validateInput(String? value, String errorMessage) {
    if (value == null || value.isEmpty) {
      return errorMessage;
    }
    return null;
  }
}

class ExerciseAttributeUpdateTextField extends StatelessWidget {
  final String label;
  final TextEditingController controller;
  final String? Function(String?)? validator;

  const ExerciseAttributeUpdateTextField({
    Key? key,
    required this.label,
    required this.controller,
    required this.validator,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    _logger.d('ExerciseUpdateScreen: Building AttributeUpdateTextField for $label');
    return Padding(
      padding: const EdgeInsets.only(bottom: 16.0),
      child: TextFormField(
        controller: controller,
        decoration: InputDecoration(
          labelText: label,
          labelStyle: const TextStyle(color: Colors.black),
          focusedBorder: const OutlineInputBorder(
            borderSide: BorderSide(color: Colors.cyan),
          ),

          enabledBorder: const OutlineInputBorder(
            borderSide: BorderSide(color: Colors.black),
          ),

          errorBorder: const OutlineInputBorder(
            borderSide: BorderSide(color: Colors.red),
          ),

          errorStyle: const TextStyle(color: Colors.red),
        ),
        style: const TextStyle(color: Colors.black),
        validator: validator,
      ),
    );
  }
}
