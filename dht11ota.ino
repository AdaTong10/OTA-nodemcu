#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include "DHT.h"


const char* ssid = "xxxxxxxxxxx"; //ssid wifi 
const char* password = "xxxxxxxxxx"; //password wifi


#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

ESP8266WebServer server(80);

void handleRoot() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    server.send(500, "text/plain", "Gagal membaca sensor DHT");
    return;
  }

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='5'>"; 
  html += "<style>";
  html += "body { font-family: Arial; background: #f2f2f2; margin:0; padding:0; }";
  html += ".card { max-width: 300px; margin: 30px auto; padding: 20px;";
  html += "background: white; box-shadow: 0 4px 8px rgba(0,0,0,0.2); border-radius: 10px;";
  html += "text-align: center; }";
  html += "h2 { color: #333; }";
  html += "</style></head><body>";
  html += "<div class='card'>";
  html += "<h2>Ada Tong</h2>";
  html += "<h3>Sensor DHT11</h3>";
  html += "<p><strong>Suhu:</strong> " + String(temp, 1) + " °C</p>";
  html += "<p><strong>Kelembapan:</strong> " + String(hum, 1) + " %</p>";
  html += "<p style='font-size:small;color:gray;'>Auto refresh tiap 5 detik</p>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  ArduinoOTA.begin();
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server aktif.");
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}



