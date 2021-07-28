#include <Arduino.h>
#include <Adafruit_PCT2075.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <WifiConfig.h>


Adafruit_PCT2075 PCT2075;
WebServer server(80);

// create the return JSON document
DynamicJsonDocument doc(256);


void ConnectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WiFiPassword);
  Serial.print("Connecting to "); Serial.println(SSID);

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(500);
    if ((++i % 16) == 0){
      Serial.println(F(" still trying to connect"));
    }
  }

  Serial.print(F("Connected. IP address is: "));
  Serial.println(WiFi.localIP());
}

void setup() {
  // init temp sensor, serial and connect to wifi
  PCT2075 = Adafruit_PCT2075();
  Serial.begin(115200);
  while (!Serial) { delay(1); }
  if (!PCT2075.begin()) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  ConnectToWiFi();

  // set default values to JSON doc
  doc["loc"] = Location;
  doc["error"] = 0;
  doc["temp"] = 99.9999;
  doc.shrinkToFit();

  // setup and start webserver
  server.on("/", returnTemp);
  server.begin();
}

void loop() {
  server.handleClient();
}

void returnTemp() {
  doc["error"] = 0;
  doc["temp"] = PCT2075.getTemperature();
  String json;
  serializeJson(doc, json);
  // return it
  server.send(200, "text/json", json);
}
