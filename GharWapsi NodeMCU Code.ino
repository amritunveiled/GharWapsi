#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Wi-Fi Credentials
#define WIFI_SSID "Rnsit library"
#define WIFI_PASSWORD "Library$123"

// Firebase Credentials
#define FIREBASE_HOST "missing-person-123-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "gc0GGu706xIeNRHkLbIplvBiiWCA4mFuVLFC1TSS"

// GPS Pins (D2 = GPIO4, D1 = GPIO5)
const int RXPin = 4, TXPin = 5;
SoftwareSerial neo6m(RXPin, TXPin);
TinyGPSPlus gps;

// Firebase objects
FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

// Person Info
String personID = "person1";
String name = "Ankit Yadav";
String Identity_Mark = "Cut Mark on Left Cheek";
String contact_No = "+91 7033111345";
int age = 5;
String gender = "Male";

void setup() {
  Serial.begin(115200);
  neo6m.begin(9600);

  wifiConnect();

  Serial.println("Connecting to Firebase...");

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Firebase connected.");
}

void loop() {
  smartdelay_gps(1000);

  if (gps.location.isValid()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();

    uploadPersonData(personID, latitude, longitude, name, age, gender,Identity_Mark,contact_No);
  } else {
    Serial.println("No valid GPS data found.");
  }

  delay(10000); // Wait 10 seconds before next update
}

void uploadPersonData(String personID, float lat, float lng, String name, int age, String gender, String Identity_Mark, String contact_No) {
  String basePath = "/People/" + personID;

  bool success = true;
  success &= Firebase.setFloat(firebaseData, basePath + "/latitude", lat);
  success &= Firebase.setFloat(firebaseData, basePath + "/longitude", lng);
  success &= Firebase.setString(firebaseData, basePath + "/name", name);
  success &= Firebase.setInt(firebaseData, basePath + "/age", age);
  success &= Firebase.setString(firebaseData, basePath + "/gender", gender);
  success &= Firebase.setString(firebaseData, basePath + "/Identity_Mark", Identity_Mark);
  success &= Firebase.setString(firebaseData, basePath + "/contact_No", contact_No);

  if (success) {
    Serial.println("Data uploaded:");
    Serial.println("Name: " + name);
    Serial.println("Age: " + String(age));
    Serial.println("Gender: " + gender);
    Serial.println("Identity_Mark: " + Identity_Mark);
    Serial.println("contact_No: " + contact_No);
    Serial.println("Latitude: " + String(lat, 6));
    Serial.println("Longitude: " + String(lng, 6));
    print_ok();
  } else {
    Serial.println("Upload failed.");
    print_fail();
  }
}

static void smartdelay_gps(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (neo6m.available()) {
      gps.encode(neo6m.read());
    }
  } while (millis() - start < ms);
}

void wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected. IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void print_ok() {
  Serial.println("------------------------------------");
  Serial.println("STATUS: OK");
  Serial.println("PATH: " + firebaseData.dataPath());
  Serial.println("TYPE: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.println("------------------------------------\n");
}

void print_fail() {
  Serial.println("------------------------------------");
  Serial.println("STATUS: FAILED");
  Serial.println("REASON: " + firebaseData.errorReason());
  Serial.println("------------------------------------\n");
}

