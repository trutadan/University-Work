import 'package:flutter/material.dart';
import 'package:lab03/exercise_update_screen.dart';
import 'package:provider/provider.dart';
import 'exercise_create_screen.dart';
import 'exercise_detail_screen.dart';
import 'exercise_view_model.dart';
import 'exercise_list_screen.dart';

void main() {
  runApp(
    ChangeNotifierProvider(
      create: (context) => ExerciseViewModel(),
      child: const MyApp(),
    ),
  );
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'FitLog',
      initialRoute: '/exerciseList',
      routes: {
        '/exerciseList': (context) => const ExerciseListScreen(),
        '/exerciseDetail': (context) => const ExerciseDetailScreen(),
        '/exerciseCreate': (context) => const ExerciseCreateScreen(),
        '/exerciseUpdate': (context) => const ExerciseUpdateScreen()
      },
    );
  }
}
