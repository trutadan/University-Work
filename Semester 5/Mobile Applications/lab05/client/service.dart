import 'package:lab04/server_repository.dart';
import 'package:lab04/utils.dart';
import 'package:lab04/view_model.dart';

import 'database_handler.dart';

class ExerciseService{
  ExerciseService._oneTime();

  late ExerciseDatabase _exerciseServerDatabase;
  late ExerciseServerRepository _exerciseServerRepository;
  late OnlineStatusManager _onlineStatusManager;
  late ExerciseViewModel _exerciseViewModel;
  late StatusNotification _notificationService;

  static final _instance = ExerciseService._oneTime();

  factory ExerciseService(){
    return _instance;
  }

  ExerciseDatabase get exerciseServerDatabase => _exerciseServerDatabase;
  ExerciseServerRepository get exerciseServerRepository => _exerciseServerRepository;
  OnlineStatusManager get onlineStatusManager => _onlineStatusManager;
  ExerciseViewModel get exerciseViewModel => _exerciseViewModel;
  StatusNotification get notificationService => _notificationService;

  Future <void> asyncInit() async {
    _notificationService = StatusNotification();

    _exerciseServerDatabase = ExerciseDatabase(tableName: 'exercises_server');
    await _exerciseServerDatabase.database;

    _onlineStatusManager = OnlineStatusManager();

    _exerciseServerRepository = ExerciseServerRepository(
      database: _exerciseServerDatabase,
    );

    _exerciseViewModel = ExerciseViewModel(_exerciseServerRepository);
  }
}