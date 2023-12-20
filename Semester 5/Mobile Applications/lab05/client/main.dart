import 'package:flutter/material.dart';
import 'package:lab04/service.dart';
import 'package:provider/provider.dart';
import 'create_screen.dart';
import 'detail_screen.dart';
import 'update_screen.dart';
import 'view_model.dart';
import 'list_screen.dart';
import 'utils.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await ExerciseService().asyncInit();

  runApp(
    MultiProvider(
      providers: [
        ChangeNotifierProvider<ExerciseViewModel>(
          create: (context) => ExerciseService().exerciseViewModel,
        ),
        ChangeNotifierProvider<OnlineStatusManager>.value(
          value: ExerciseService().onlineStatusManager,
        ),
      ],
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
        '/exerciseUpdate': (context) => const ExerciseUpdateScreen(),
      },
      builder: (context, child) {
        return Stack(
          children: [
            child!,
            const OfflineIndicator(),
          ],
        );
      },
    );
  }
}