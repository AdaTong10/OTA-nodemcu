# 🌡️ NodeMCU + DHT11 Web Server + OTA (ESP8266)

Proyek ini menampilkan data suhu dan kelembapan dari sensor **DHT11** menggunakan **NodeMCU ESP8266**.  
Data dikirim melalui **web server lokal**, dan mendukung **OTA (Over-the-Air) update** untuk memprogram NodeMCU tanpa kabel USB.

## 🔧 Perangkat Keras (Hardware)
- NodeMCU ESP8266 (v1.0 atau lainnya)
- Sensor DHT11
- Kabel jumper
- Breadboard

## 💻 Software & Library
- Arduino IDE
- Board: ESP8266 by ESP8266 Community
- Library:
  - `DHT sensor library` by Adafruit
  - `ESP8266WiFi`
  - `ESP8266WebServer`
  - `ArduinoOTA`

## 📷 Tampilan Web Server
Menampilkan:
- Suhu (°C)
- Kelembapan (%)

Data ditampilkan secara real-time di halaman browser melalui alamat IP lokal dari NodeMCU.

## 🔁 OTA Update
Fitur OTA memungkinkan kamu mengupload sketch Arduino langsung via WiFi tanpa perlu kabel USB.  
Pastikan perangkat terhubung ke jaringan WiFi yang sama.

```cpp
ArduinoOTA.begin();
ArduinoOTA.handle();
