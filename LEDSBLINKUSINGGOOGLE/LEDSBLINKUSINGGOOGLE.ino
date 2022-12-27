//SIMPLE PROGRAM TO ON AND OFF TWO LEDS IN ESP32 USING GOOGLE ASSISTANT AND ALEXA WITH ESP32
//Create an Account on SinricPro
//Create a room in profile
//Create two devices as switch
//Name them LED1 and LED2
//Copy the credentials and paste it in code
//Enter your WIFI Credentials
//Connect +ive of LEDs and -ive to GRD
//Upload the code to ESP 32

#include <Arduino.h>
#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#define WIFI_SSID         "your SSID"    
#define WIFI_PASS         "your PASSWORD"
#define APP_KEY           "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#define APP_SECRET        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"   
#define LED1              "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"    
#define LED2              "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"


#define BAUD_RATE         115200     

#define relayPIN1 13 
#define relayPIN2 12   

bool onPowerState1(const String &deviceId, bool &state) {
  Serial.printf("Device 1 turned %s\r\n", state?"on":"off");
  digitalWrite(relayPIN1,state); 
  return true;
}

bool onPowerState2(const String &deviceId, bool &state) {
  Serial.printf("Device 2 turned %s\r\n", state?"on":"off");
  digitalWrite(relayPIN2,state); 
  digitalWrite(2,state);
  return true;
}
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  WiFi.setAutoReconnect(true);
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  SinricProSwitch& mySwitch1 = SinricPro[LED1];
  mySwitch1.onPowerState(onPowerState1);
  SinricProSwitch& mySwitch2 = SinricPro[LED2];
  mySwitch2.onPowerState(onPowerState2);
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro();
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}
void loop() {
  SinricPro.handle();
}
