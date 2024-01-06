class Exercise {
  int id;
  String name;
  String description;
  String category;
  String primaryMuscle;
  List<String> secondaryMuscles;
  List<String> equipment;
  String? image;
  bool synchronized;

  Exercise({
    required this.id,
    required this.name,
    required this.description,
    required this.category,
    required this.primaryMuscle,
    required this.secondaryMuscles,
    required this.equipment,
    this.image = '',
    this.synchronized = true
  });

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'description': description,
      'category': category,
      'primaryMuscle': primaryMuscle,
      'secondaryMuscles': secondaryMuscles.join(','),
      'equipment': equipment.join(','),
      'image': image,
    };
  }

  Map<String, dynamic> toMapWithId() {
    return {
      'id': id,
      'name': name,
      'description': description,
      'category': category,
      'primaryMuscle': primaryMuscle,
      'secondaryMuscles': secondaryMuscles.join(','),
      'equipment': equipment.join(','),
      'image': image,
    };
  }

  Map<String, dynamic> toMapWithIdAndSynchronized() {
    return {
      'id': id,
      'name': name,
      'description': description,
      'category': category,
      'primaryMuscle': primaryMuscle,
      'secondaryMuscles': secondaryMuscles.join(','),
      'equipment': equipment.join(','),
      'image': image,
      'synchronized': synchronized,
    };
  }

  factory Exercise.fromMap(Map<String, dynamic> map) {
    return Exercise(
      id: map['id'],
      name: map['name'],
      description: map['description'],
      category: map['category'],
      primaryMuscle: map['primaryMuscle'],
      secondaryMuscles: (map['secondaryMuscles'] as String).split(','),
      equipment: (map['equipment'] as String).split(','),
      image: map['image'],
      synchronized: map['synchronized'] == 1,
    );
  }

  Map<String, dynamic> toJson() {
    return {
      'name': name,
      'description': description,
      'category': category,
      'primary_muscle': primaryMuscle,
      'secondary_muscles': secondaryMuscles.join(','),
      'equipment': equipment.join(','),
      'image': image,
    };
  }

  factory Exercise.fromJson(Map<String, dynamic> json) {
    return Exercise(
      id: json['id'],
      name: json['name'],
      description: json['description'],
      category: json['category'],
      primaryMuscle: json['primary_muscle'],
      secondaryMuscles: (json['secondary_muscles'] as String).split(','),
      equipment: (json['equipment'] as String).split(','),
      image: json['image'],
    );
  }

  @override
  String toString() {
    return 'Exercise{id: $id, name: $name, description: $description, '
        'category: $category, primaryMuscle: $primaryMuscle, '
        'secondaryMuscles: $secondaryMuscles, equipment: $equipment, '
        'image: $image, synchronized: $synchronized}';
  }
}