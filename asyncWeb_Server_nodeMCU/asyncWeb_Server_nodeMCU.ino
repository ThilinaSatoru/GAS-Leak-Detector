#include "config.h"
#include "html.h"
#include "functions.h"

void setup(){///////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  nodeMCU_Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); 
    Serial.println("...");
  }
  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  server.on("/Vstore", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(Serial_sensor1).c_str());
  });
  server.on("/Vkitchen", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(Serial_sensor2).c_str());
  });
  
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam(PARAM_INPUT_1)){
      if(request->getParam(PARAM_INPUT_1)->value()== "1"){
        //off store
        store_stat = false;
      }
      if(request->getParam(PARAM_INPUT_1)->value()== "2"){
        //off kit
        kitchen_stat = false;
      }
      if(request->getParam(PARAM_INPUT_1)->value()== "3"){
        // on store
        store_stat = true;
      }
      if(request->getParam(PARAM_INPUT_1)->value()== "4"){
        // on kit
        kitchen_stat = true;
      }
    }
    Serial.println(request->getParam(PARAM_INPUT_1)->value());
    request->send_P(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}


void loop(){///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Rx Tx get info from arduino
    while(nodeMCU_Serial.available()>0){
      c = nodeMCU_Serial.read();
      if(c =='\n'){ break; }
      else        { dataIn+=c; }
    }
    
    if(store_stat == false && kitchen_stat == false){
      off(); flash(B);
    }
    else if(store_stat == true || kitchen_stat == true){
      if(c=='\n'){
        Parse_the_Data();
        //serialMonitor();
        //reset
        c=0; dataIn="";
      }
      off(); 
      OutputLogic(min_Range, max_Range);
    }


    
  }
}/////////////////////////////////////////////////////////////////////////
