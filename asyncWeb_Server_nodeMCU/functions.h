void flash(char output){
  digitalWrite(output, HIGH);
}
void off(){
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
}
void buzz(int Delay1, int Delay2){
  digitalWrite(buzzer, HIGH);
  delay(Delay1);
  digitalWrite(buzzer, LOW);
  delay(Delay2);
}
void serialMonitor(){
  //Monitor
  Serial.print(" Store : ");
  Serial.print(Serial_sensor1.toFloat());
  Serial.print(" kitchen : ");
  Serial.print(Serial_sensor2);
  Serial.println("");
  Serial.println("=============================");
}
void OutputLogic(int min_R,int max_R){    
  if(
    ((Serial_sensor1.toFloat() >= min_R) || (Serial_sensor2.toFloat() >= min_R)) 
    && 
    ((Serial_sensor1.toFloat() <= max_R) || (Serial_sensor2.toFloat() <= max_R))
    )
  {
    off();
    flash(G);
    buzz(50,500);
//  Serial.print("green");
  }
  else if((Serial_sensor1.toFloat() > max_R) || (Serial_sensor2.toFloat() > max_R)){
    off();
    flash(R);
    buzz(500,50);
//  Serial.print("red");
  }
}

//////////////////////////////////////////////////////////
void Parse_the_Data(){
  indexOfA = dataIn.indexOf("A");
  indexOfB = dataIn.indexOf("B");

  Serial_sensor1 = dataIn.substring (0, indexOfA);
  Serial_sensor2 = dataIn.substring (indexOfA+1, indexOfB);
}
//////////////////////////////////////////////////////////
