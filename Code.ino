#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Arduino.h"
#include "DFRobot_IL3895_SPI.h"
DFRobot_IL3895_SPI epaper;

#define EPAPER_CS  D3
#define Font_CS  D6
#define EPAPER_DC  D8
#define EPAPER_BUSY     D7

// WiFi parameters
const char* ssid = "SSID";
const char* password = "PASSWORD";
void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Move to next line
  
  Serial.println();
  // Connect to WiFi
  epaper.begin(EPAPER_CS, Font_CS, EPAPER_DC, EPAPER_BUSY);

  epaper.fillScreen(WHITE);//Clear the screen and display white 
  epaper.flush(FULL); //Refresh screen display  
  // Print WiFi Parameters
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop(){
  const char* condition;
  char tempar[5],humid[5];
    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/forecast?q=delhi,IN&appid=###### KEY #####&mode=json&units=metric&cnt=2");
    int httpCode = http.GET();
 
    if (httpCode > 0) {
      // Get payload
      String payload = http.getString();
      // JSON buffer 
      const size_t bufferSize = 2*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 4*JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 2*JSON_OBJECT_SIZE(7) + 2*JSON_OBJECT_SIZE(8) + 720;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      // Parse JSON data
      const char* json = payload.c_str();
      JsonObject& root = jsonBuffer.parseObject(json);
      // Root object
      JsonArray& list = root["list"];
      JsonObject& nowT = list[0];
      JsonObject& later = list[1];
      // Get main report
      condition = nowT["weather"][0]["description"];
      float tempNow = nowT["main"]["temp"];
      float humidityNow = nowT["main"]["humidity"];
      char teststr[20];
      strcpy(teststr, condition);
      Serial.print(tempNow);
      dtostrf(tempNow, 3, 2, tempar);
      dtostrf(humidityNow, 3, 1, humid);
      epaper.fillScreen(WHITE);
      epaper.disString(5,5,2,"WEATHER MONITOR",BLACK);
      epaper.disString(5,45,2,"T:",BLACK);
      epaper.disString(32,45,2,tempar,BLACK);
      epaper.disString(114,45,2,"c",BLACK);
      epaper.disString(145,45,2,"H:",BLACK);
      epaper.disString(175,45,2,humid,BLACK);
      epaper.disString(20,85,2,teststr,BLACK);
      epaper.flush(PART);
    }
    http.end();   //Close connection

    delay(20000);

}
