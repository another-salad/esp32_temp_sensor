#include <Arduino.h>
#include <Adafruit_PCT2075.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <WifiConfig.h>


Adafruit_PCT2075 PCT2075;
WebServer server(80);

void ConnectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WiFiPassword);
  Serial.print("Connecting to "); Serial.println(SSID);

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);

    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }

  Serial.print(F("Connected. IP address is: "));
  Serial.println(WiFi.localIP());
}

void setup() {
  PCT2075 = Adafruit_PCT2075();
  Serial.begin(115200);
  while (!Serial) { delay(1); }
  if (!PCT2075.begin()) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  ConnectToWiFi();
  server.on("/", returnTemp);
  server.begin();
}

void loop() {
  server.handleClient();
}

void returnTemp() {
  // create and serialise the return JSON
  DynamicJsonDocument doc(256);
  doc["error"] = 0;
  doc["loc"] = Location;
  doc["temp"] = PCT2075.getTemperature();
  doc.shrinkToFit();
  String json;
  serializeJson(doc, json);
  // return it
  server.send(200, "text/json", json);
}
