import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:connectivity/connectivity.dart';
import 'package:flutter/services.dart';
import 'package:http/http.dart' as http;
import 'package:flutter/material.dart';
import 'package:lab04/service.dart';
import 'package:logger/logger.dart';
import 'package:provider/provider.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'package:fluttertoast/fluttertoast.dart';

import 'consts.dart';

final Logger _logger = Logger();

class TopNavigationBar extends StatelessWidget {
  final String title;

  const TopNavigationBar({Key? key, required this.title}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    _logger.d('Building TopNavigationBar for title: $title');
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
    _logger.d('Building CreateExerciseNavigationBar');
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

class OnlineStatusManager extends ChangeNotifier {
  late WebSocketChannel _channel;

  bool _online = false;

  bool get isOnline => _online;

  set online(bool value) {
    _online = value;
  }

  Future<void> checkOnline() async {
    try {
      _logger.d('Checking if server is online');
      var response = await http.get(
          Uri.parse('$SERVER_URL/check_connection')
      ).timeout(const Duration(seconds: 3));

      _logger.d('Server response: ${response.body}');
      if (response.statusCode == 200) {
          if (_online == false) {
            _logger.d('Server is back online');
            _online = true;
            await connectToWebSocketAndSynchronize();
            ExerciseService().notificationService.showToast('Connection is back online');
            notifyListeners();
          }
      } else {
        _logger.e('Server is offline');
        _online = false;
        notifyListeners();
      }
    } on SocketException {
      _logger.e('Server is offline');
      _online = false;
      notifyListeners();
    } on TimeoutException {
      _logger.e('Server request timed out');
      _online = false;
      notifyListeners();
    } catch (e) {
      _logger.e('Error checking if the server is online: $e');
      _online = false;
      notifyListeners();
    } finally {
      notifyListeners();
    }
  }

  Future<void> connectToWebSocketAndSynchronize() async {
    try {
      _logger.d('Connecting to WebSocket and synchronizing databases');
      _connectToWebsocket();
      await ExerciseService().exerciseServerRepository.synchronizeDatabases();
    } catch (e) {
      _logger.e('Error connecting to WebSocket and synchronizing databases: $e');
    }
  }

  void _connectToWebsocket() {
    _logger.d('Connecting to WebSocket');
    _channel = WebSocketChannel.connect(Uri.parse(WEBSOCKET_SERVER_URL));

    _channel.sink.add(jsonEncode({
      'command': 'subscribe',
      'identifier': jsonEncode({
        'channel': 'ExerciseChannel',
      }),
    }));

    _channel.stream.listen(
      (data) {
        ExerciseService().exerciseServerRepository.listenToServer(data);
      },
      onDone: () {
        _logger.d('WebSocket channel closed');
        _online = false;
      },
      onError: (error) {
        _logger.e('Error listening to the server: $error');
        _online = false;
      },
    );
  }

  @override
  void dispose() {
    super.dispose();
    _channel.sink.close();
  }
}

class OfflineIndicator extends StatefulWidget {
  const OfflineIndicator({Key? key}) : super(key: key);

  @override
  _OfflineIndicatorState createState() => _OfflineIndicatorState();
}

class _OfflineIndicatorState extends State<OfflineIndicator> {
  final Connectivity _connectivity = Connectivity();
  late StreamSubscription<ConnectivityResult> _connectivitySubscription;
  bool _hasInternet = false;

  @override
  void initState() {
    super.initState();

    _connectivitySubscription =
        _connectivity.onConnectivityChanged.listen(_updateConnectivity);
  }

  @override
  Widget build(BuildContext context) {
    return Consumer<OnlineStatusManager>(
      builder: (context, onlineStatusManager, child) {
        if (!_hasInternet) {
          return _buildNoInternetMessage(context);
        } else if (!onlineStatusManager.isOnline) {
          return _buildOfflineMessage(context, onlineStatusManager);
        } else {
          return Container();
        }
      },
    );
  }

  Future<void> _checkInternetConnection() async {
    try {
      final connection = await _connectivity.checkConnectivity();
      final hasInternet = connection == ConnectivityResult.mobile ||
          connection == ConnectivityResult.wifi;

      setState(() {
        _hasInternet = hasInternet;
      });
    } on PlatformException catch (e) {
      _logger.e('Error checking internet connectivity: $e');
      setState(() {
        _hasInternet = false;
      });
    }
  }

  void _updateConnectivity(ConnectivityResult result) {
    if (result == ConnectivityResult.none) {
      setState(() {
        _hasInternet = false;
      });
    } else {
      _checkInternetConnection();
    }
  }

  Widget _buildNoInternetMessage(BuildContext context) {
    return Positioned(
      bottom: 50.0,
      left: 15,
      right: 15,
      child: Container(
        decoration: BoxDecoration(
          color: Colors.grey,
          borderRadius: BorderRadius.circular(10.0),
        ),
        height: 50,
        padding: const EdgeInsets.symmetric(horizontal: 16.0),
        child: const Center(
          child: Text(
            'No internet connection.',
            style: TextStyle(
              fontSize: 16,
              color: Colors.black,
            ),
          ),
        ),
      ),
    );
  }

  Widget _buildOfflineMessage(
      BuildContext context, OnlineStatusManager onlineStatusManager) {
    return Positioned(
      bottom: 50.0,
      left: 15,
      right: 15,
      child: Container(
        decoration: BoxDecoration(
          color: Colors.grey,
          borderRadius: BorderRadius.circular(10.0),
        ),
        height: 50,
        padding: const EdgeInsets.symmetric(horizontal: 16.0),
        child: SingleChildScrollView(
          scrollDirection: Axis.horizontal,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Text(
                'You are currently offline.',
                style: TextStyle(
                  fontSize: 16,
                  color: Colors.black,
                ),
              ),
              const SizedBox(width: 8.0),
              ElevatedButton(
                onPressed: () async {
                  await onlineStatusManager.checkOnline();
                },
                style: ElevatedButton.styleFrom(
                  primary: Colors.white,
                  onPrimary: Colors.black,
                ),
                child: const Text('Retry'),
              ),
            ],
          ),
        ),
      ),
    );
  }

  @override
  void dispose() {
    _connectivitySubscription.cancel();
    super.dispose();
  }
}

class StatusNotification {
  void showToast(String message, {Color backgroundColor = Colors.green}) {
    Fluttertoast.showToast(
      msg: message,
      toastLength: Toast.LENGTH_SHORT,
      gravity: ToastGravity.TOP,
      backgroundColor: backgroundColor,
      textColor: Colors.white,
    );
  }
}