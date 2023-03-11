#include <Arduino.h>

#include "WiFi.h"
#include "ESPAsyncWebServer.h"

#include <Wire.h>

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

#define BUTTON_PIN 4


char readButton(int pin) {
  if (digitalRead(pin) == 1) {
    return 'T';
  }

  else {return 'F';}
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  Serial.println();

  pinMode(BUTTON_PIN, INPUT_PULLUP);  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);


  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readButton(BUTTON_PIN).c_str());
  });

  
  bool status;

  // Start server
  server.begin();
}
 
void loop(){

  Serial.print(readButton(BUTTON_PIN));
  
}

