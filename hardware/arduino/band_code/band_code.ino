#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Wire.h>
#include "time.h"
#include <TimeLib.h>


// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Autobonics_4G"
#define WIFI_PASSWORD "autobonics@27"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBoU0q5WTFkn3cdW1AOIhEM00Y52D4RE5E"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "device@autobonics.com"
#define USER_PASSWORD "12345678"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://smart-medical-caddy-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Database main path (to be updated in setup with the user UID)
String databasePathData = "device/data/";
String databasePathReading = "device/reading/";
// Database child nodes

int timestamp;
FirebaseJson json;

const char* ntpServer = "pool.ntp.org";


// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 10000;


#include <Servo.h>
//Leds
#define led1 21
#define led2 19
#define led3 18
//Servos
#define s1 24
#define s2 33
#define s3 32
Servo servo1;
Servo servo2;
Servo servo3;
//Ir
#define ir1 14
#define ir2 27
#define ir3 13

//Caddys time storage
int caddy1;
int caddy2;
int caddy3;

int currentTime;

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setupComponents(){
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT);  

  pinMode(ir1, INPUT); 
  pinMode(ir2, INPUT); 
  pinMode(ir3, INPUT);  

  servo1.attach(s1);
  servo2.attach(s2);
  servo3.attach(s3);
}

void setup(){
  Serial.begin(115200);

  initWiFi();
  configTime(0, 0, ntpServer);

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  setupComponents();
}



void loop(){
  

  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Get current timestamp
    timestamp = getTime() * 1000;
    Serial.print ("time: ");
    Serial.println(timestamp);
    Serial.print("Time: ");
    currentTime =  minute(timestamp);
    Serial.println(currentTime);

    json.set("ts", int(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, databasePathReading.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());

    Serial.println("get data");

    //Getting data
    FirebaseJson jVal;
    Serial.printf("Get json ref... %s\n", Firebase.RTDB.getJSON(&fbdo, databasePathData.c_str(), &jVal) ? jVal.raw() : fbdo.errorReason().c_str());
    FirebaseJsonData delayTime;
    FirebaseJsonData cd1;
    FirebaseJsonData cd2;
    FirebaseJsonData cd3;
    jVal.get(delayTime, "delay");
    jVal.get(cd1, "1");
    jVal.get(cd2, "2");
    jVal.get(cd3, "3");
    if (delayTime.success && cd1.success && cd1.success && cd2.success && cd3.success)
    {
      timerDelay = delayTime.to<int>();
      int ct1 = cd1.to<int>();
      int ct2 = cd2.to<int>();
      int ct3 = cd3.to<int>();
//      caddy1 = hour(ct1) + minute(ct1);
      caddy1 = minute(ct1);
      caddy2 = minute(ct2);
      caddy3 = minute(ct3);
      Serial.println(timerDelay);
      Serial.println(caddy1);
      Serial.println(caddy2);
      Serial.println(caddy3);
      Serial.println(currentTime - caddy1);
    }
  }

  if(currentTime - caddy1 > 0 && currentTime - caddy1 < 5){
    servo1.write(90);
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
    servo1.write(0);
  }

  if(currentTime - caddy2 > 0 && currentTime - caddy2 < 5){
    servo1.write(90);
    digitalWrite(led2, HIGH);
  } else {
    servo1.write(0);
    digitalWrite(led2, LOW);
  }

  if(currentTime - caddy3 > 0 && currentTime - caddy3 < 5){
    servo1.write(90);
    digitalWrite(led3, HIGH);
  } else {
    servo1.write(0);
    digitalWrite(led3, LOW);
  }
  
}