import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'exercise_create_screen.dart';
import 'exercise_database.dart';
import 'exercise_detail_screen.dart';
import 'exercise_repository.dart';
import 'exercise_update_screen.dart';
import 'exercise_view_model.dart';
import 'exercise_list_screen.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();

  ExerciseDatabase exerciseDatabase = ExerciseDatabase();
  await exerciseDatabase.database;

  ExerciseRepository exerciseRepository = ExerciseRepository(database: exerciseDatabase);

  runApp(
    ChangeNotifierProvider(
      create: (context) => ExerciseViewModel(exerciseRepository),
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