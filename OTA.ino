#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>


const char* ssid = "xxxxxxxx";
const char* password = "xxxxxxx";


ESP8266WebServer server(80);
Adafruit_BMP280 bmp;

float temperature = 0;
float pressure = 0;


void handleRoot() {
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>BMP280 Monitor</title>";
  html += "<meta http-equiv='refresh' content='2'>";
 
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; background-color: #f4f4f9; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
  html += "div.container { text-align: center; padding: 20px; background-color: #fff; border-radius: 8px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); }";
  html += "h2 { color: #333; font-size: 24px; margin-bottom: 20px; }";
  html += "p { font-size: 18px; color: #555; margin: 10px 0; }";
  html += "strong { color: #000; }";
  html += "</style>";
  html += "</head><body>";
  
 
  html += "<div class='container'>";
  html += "<h2>Ada Tong</h2>";
  html += "<h3>Monitoring Sensor BMP280</h3>";
  html += "<p><strong>Suhu:</strong> " + String(temperature, 2) + " °C</p>";
  html += "<p><strong>Tekanan:</strong> " + String(pressure / 100.0, 2) + " hPa</p>";
  html += "<p>IP NodeMCU: " + WiFi.localIP().toString() + "</p>";
  html += "</div>";

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setupOTA() {
  ArduinoOTA.setHostname("NodeMCU-BMP");

  ArduinoOTA.onStart([]() { Serial.println("Mulai OTA"); });
  ArduinoOTA.onEnd([]() { Serial.println("\nSelesai OTA"); });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error OTA [%u]\n", error);
  });

  ArduinoOTA.begin();
  Serial.println("OTA siap.");
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi terhubung. IP: " + WiFi.localIP().toString());

  if (!bmp.begin(0x76)) { 
    Serial.println("Sensor BMP280 tidak ditemukan!");
    while (1); 
  }

  server.on("/", handleRoot);
  server.begin();
  setupOTA();
}


void loop() {
  ArduinoOTA.handle();
  server.handleClient();

  temperature = bmp.readTemperature();
  pressure = bmp.readPressure();

  delay(1000); 
}
