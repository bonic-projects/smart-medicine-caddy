// File generated by FlutterFire CLI.
// ignore_for_file: lines_longer_than_80_chars, avoid_classes_with_only_static_members
import 'package:firebase_core/firebase_core.dart' show FirebaseOptions;
import 'package:flutter/foundation.dart'
    show defaultTargetPlatform, kIsWeb, TargetPlatform;

/// Default [FirebaseOptions] for use with your Firebase apps.
///
/// Example:
/// ```dart
/// import 'firebase_options.dart';
/// // ...
/// await Firebase.initializeApp(
///   options: DefaultFirebaseOptions.currentPlatform,
/// );
/// ```
class DefaultFirebaseOptions {
  static FirebaseOptions get currentPlatform {
    if (kIsWeb) {
      return web;
    }
    switch (defaultTargetPlatform) {
      case TargetPlatform.android:
        return android;
      case TargetPlatform.iOS:
        return ios;
      case TargetPlatform.macOS:
        return macos;
      case TargetPlatform.windows:
        throw UnsupportedError(
          'DefaultFirebaseOptions have not been configured for windows - '
          'you can reconfigure this by running the FlutterFire CLI again.',
        );
      case TargetPlatform.linux:
        throw UnsupportedError(
          'DefaultFirebaseOptions have not been configured for linux - '
          'you can reconfigure this by running the FlutterFire CLI again.',
        );
      default:
        throw UnsupportedError(
          'DefaultFirebaseOptions are not supported for this platform.',
        );
    }
  }

  static const FirebaseOptions web = FirebaseOptions(
    apiKey: 'AIzaSyDxVxWzk8Xhhh8F0M5jDwO1At07HGLSqos',
    appId: '1:557638764824:web:65850ecca31e5b4fadb66d',
    messagingSenderId: '557638764824',
    projectId: 'canon-6b776',
    authDomain: 'canon-6b776.firebaseapp.com',
    storageBucket: 'canon-6b776.appspot.com',
    measurementId: 'G-5K9NGQBBBJ',
  );

  static const FirebaseOptions android = FirebaseOptions(
    apiKey: 'AIzaSyAPftjEYwuGnrDGUubFJmAkohMD7p4bObY',
    appId: '1:557638764824:android:fc881afbebf6c3daadb66d',
    messagingSenderId: '557638764824',
    projectId: 'canon-6b776',
    storageBucket: 'canon-6b776.appspot.com',
  );

  static const FirebaseOptions ios = FirebaseOptions(
    apiKey: 'AIzaSyBG-eybUTuW10XL1v_MOBxy7bAcSc_5sy8',
    appId: '1:557638764824:ios:5af88a07f4afd6e3adb66d',
    messagingSenderId: '557638764824',
    projectId: 'canon-6b776',
    storageBucket: 'canon-6b776.appspot.com',
    iosClientId: '557638764824-qv0kal72m6qrikiocmfpufhqme7kc78b.apps.googleusercontent.com',
    iosBundleId: 'com.example.secretApp',
  );

  static const FirebaseOptions macos = FirebaseOptions(
    apiKey: 'AIzaSyBG-eybUTuW10XL1v_MOBxy7bAcSc_5sy8',
    appId: '1:557638764824:ios:5af88a07f4afd6e3adb66d',
    messagingSenderId: '557638764824',
    projectId: 'canon-6b776',
    storageBucket: 'canon-6b776.appspot.com',
    iosClientId: '557638764824-qv0kal72m6qrikiocmfpufhqme7kc78b.apps.googleusercontent.com',
    iosBundleId: 'com.example.secretApp',
  );
}