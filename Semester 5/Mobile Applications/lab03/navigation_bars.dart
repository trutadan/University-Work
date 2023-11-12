import 'package:flutter/material.dart';

class TopNavigationBar extends StatelessWidget {
  final String title;

  const TopNavigationBar({Key? key, required this.title}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Colors.black,
      padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
      child: Row(
        children: [
          GestureDetector(
            onTap: () {
              Navigator.pushNamed(context, '/exerciseList');
            },
            child: const Icon(
              Icons.home,
              size: 30,
              color: Colors.white,
            ),
          ),

          const Spacer(),

          Text(
            title,
            style: const TextStyle(color: Colors.white),
          ),

          const Spacer(),

          const Icon(
            Icons.settings,
            size: 30,
            color: Colors.white,
          ),
        ],
      ),
    );
  }
}

class CreateExerciseNavigationBar extends StatelessWidget {
  const CreateExerciseNavigationBar({super.key});

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Colors.black,
      height: 30,
      child: Row(
        children: [
          const Spacer(),

          ElevatedButton(
            onPressed: () {
              Navigator.pushNamed(context, '/exerciseCreate');
            },
            style: ElevatedButton.styleFrom(backgroundColor: Colors.white),
            child: const Text(
              'New exercise',
              style: TextStyle(color: Colors.black),
            ),
          ),

          const Spacer(),
        ],
      ),
    );
  }
}