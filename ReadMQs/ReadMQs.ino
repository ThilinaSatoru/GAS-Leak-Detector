#include <SoftwareSerial.h>

#define Store_Sensor_PIN A0
#define Kitchen_Sensor_PIN A1

SoftwareSerial UNO_SoftSerial(10,11);
float Serial_sensor1 = 0.0;
float Serial_sensor2 = 0.0;



void setup() {
  pinMode(Store_Sensor_PIN, INPUT);
  pinMode(Kitchen_Sensor_PIN, INPUT);
  
  Serial.begin(9600);
  UNO_SoftSerial.begin(115200);
}

void MQread(){
  Serial_sensor1=0.0;
  Serial_sensor2=0.0;
  Serial_sensor1 = analogRead(Store_Sensor_PIN);
  Serial_sensor2 = analogRead(Kitchen_Sensor_PIN);
}

void loop() {
  MQread();

  UNO_SoftSerial.print(Serial_sensor1,2); UNO_SoftSerial.print("A");        
  UNO_SoftSerial.print(Serial_sensor2,2); UNO_SoftSerial.print("B");
  UNO_SoftSerial.print("\n");
  
  delay(500);
}
