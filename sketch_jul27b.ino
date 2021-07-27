#include <Arduino.h>
#include <Adafruit_PCT2075.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "plop";
const char* password = "Farting_4_Fun!#";

WebServer server(80);

void ConnectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to "); Serial.println(ssid);

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
  Serial.begin(115200);
  ConnectToWiFi();
  server.on("/", returnTemp);
  server.begin();
}

void loop() {
  server.handleClient();
}

void returnTemp() {
  server.send(200, "text/html", "<html><h1>hello</h1><html>");
}
