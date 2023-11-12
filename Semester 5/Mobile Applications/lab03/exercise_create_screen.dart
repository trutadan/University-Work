import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';
import 'package:provider/provider.dart';
import 'exercise_model.dart';
import 'exercise_view_model.dart';

class ExerciseCreateScreen extends StatefulWidget {
  const ExerciseCreateScreen({Key? key}) : super(key: key);

  @override
  _ExerciseCreateScreenState createState() => _ExerciseCreateScreenState();
}

class _ExerciseCreateScreenState extends State<ExerciseCreateScreen> {
  var name = "";
  var description = "";
  var category = "";
  var primaryMuscle = "";
  var secondaryMuscles = "";
  var equipment = "";

  String? _selectedImagePath;

  final _formKey = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Center(child: Text('Create Exercise')),
        backgroundColor: Colors.black,
        actions: [
          GestureDetector(
            onTap: () {
              if (_formKey.currentState?.validate() ?? false) {
                _createExercise(
                  context,
                  name,
                  description,
                  category,
                  primaryMuscle,
                  secondaryMuscles,
                  equipment,
                  _selectedImagePath,
                );
              }
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
              ExerciseAttributeCreateTextField("Name", name, (value) {
                name = value;
              }, (value) => _validateInput(value, "Name is required")),

              ExerciseAttributeCreateTextField("Description", description, (value) {
                description = value;
              }, (value) => _validateInput(value, "Description is required")),

              ExerciseAttributeCreateTextField("Category", category, (value) {
                category = value;
              }, (value) => _validateInput(value, "Category is required")),

              ExerciseAttributeCreateTextField("Primary Muscle", primaryMuscle, (value) {
                primaryMuscle = value;
              }, (value) => _validateInput(value, "Primary Muscle is required")),

              ExerciseAttributeCreateTextField(
                "Secondary Muscles",
                secondaryMuscles,
                    (value) {
                  secondaryMuscles = value;
                },
                    (value) => _validateInput(value, "Secondary Muscles is required"),
              ),

              ExerciseAttributeCreateTextField("Equipment", equipment, (value) {
                equipment = value;
              }, (value) => _validateInput(value, "Equipment is required")),
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
                child: const Text('Add Photo', style: TextStyle(color: Colors.white)),
              ),
            ),
          ],
        ),
        const SizedBox(height: 8.0),
      ],
    );
  }

  void _selectImage() async {
    final pickedFile = await ImagePicker().pickImage(source: ImageSource.gallery);

    if (pickedFile != null) {
      setState(() {
        _selectedImagePath = pickedFile.path;
      });
    }
  }

  void _createExercise(
      BuildContext context,
      String name,
      String description,
      String category,
      String primaryMuscle,
      String secondaryMuscles,
      String equipment,
      String? imagePath,
      ) {
    final viewModel = Provider.of<ExerciseViewModel>(context, listen: false);

    final newExercise = Exercise(
      id: 0,
      name: name,
      description: description,
      category: category,
      primaryMuscle: primaryMuscle,
      secondaryMuscles: secondaryMuscles.split(", ").map((e) => e.trim()).toList(),
      equipment: equipment.split(", ").map((e) => e.trim()).toList(),
      image: imagePath,
    );

    viewModel.addExercise(newExercise);

    Navigator.of(context).pop();
  }

  String? _validateInput(String? value, String errorMessage) {
    if (value == null || value.isEmpty) {
      return errorMessage;
    }
    return null;
  }
}

class ExerciseAttributeCreateTextField extends StatelessWidget {
  final String label;
  final String value;
  final ValueChanged<String> onValueChange;
  final String? Function(String?)? validator;

  const ExerciseAttributeCreateTextField(
      this.label,
      this.value,
      this.onValueChange,
      this.validator, {
        Key? key,
      }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.only(bottom: 16.0),
      child: TextFormField(
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
        onChanged: onValueChange,
        validator: validator,
      ),
    );
  }
}

