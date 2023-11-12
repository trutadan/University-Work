class Exercise {
  int id;
  String name;
  String description;
  String category;
  String primaryMuscle;
  List<String> secondaryMuscles;
  List<String> equipment;
  String? image;

  Exercise({
    required this.id,
    required this.name,
    required this.description,
    required this.category,
    required this.primaryMuscle,
    required this.secondaryMuscles,
    required this.equipment,
    this.image,
  });
}