#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SoftwareSerial.h>
SoftwareSerial nodeMCU_Serial (D1, D2);

#define R 13 // D5
#define G 12 // D6
#define B 14 // D7
#define buzzer 15 // D8

// set sensor condition
int min_Range = 240;
int max_Range = 350;

char c;
String dataIn;
uint8_t indexOfA, indexOfB; 
String Serial_sensor1, Serial_sensor2;

// Replace with your network credentials
const char* ssid = "SLT @samurai";
const char* password = "@samurai1creeds";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char* PARAM_INPUT_1 = "state";
String requestMessage;
bool store_stat = false, kitchen_stat = false;
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;    // will store last time DHT was updated
const long interval = 500;
