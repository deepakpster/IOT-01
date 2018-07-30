#include <ESP8266HTTPClient.h>

//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "iot-pd.firebaseio.com"
#define FIREBASE_AUTH "UPfyj5ctW8b2UJ3phMRbsQuInyxVhJpN9ARbbfNn"
#define WIFI_SSID "deepakpster"
#define WIFI_PASSWORD "fasttrack6917"
#define LED 2

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

bool LED_STATUS = false;

void loop() {
  // set value
  LED_STATUS = Firebase.getBool("LED_STATUS");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  if(LED_STATUS) {
    Serial.print("Turning ON the lights");
    digitalWrite(LED, HIGH);
  } else {
    Serial.print("Turning OFF the lights");
    digitalWrite(LED, LOW);
  }
  delay(1000);
}
