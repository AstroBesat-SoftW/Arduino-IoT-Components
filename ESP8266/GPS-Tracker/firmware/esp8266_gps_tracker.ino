#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Wi-Fi credentials — replace with your own
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Server info — replace with your own domain
const String serverName = "http://yourdomain.com/maps/kaydet.php";

static const int RXPin = 5; // D1
static const int TXPin = 4; // D2
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

unsigned long sonGonderim = 0;
const long beklemeSuresi = 5000;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPSBaud);

  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected! Listening for GPS data...");
  Serial.println("----------------------------------------");
}

void loop() {
  // 1. Continuously read data coming from the GPS module
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // 2. Check status every 5 seconds
  if (millis() - sonGonderim > beklemeSuresi) {

    // IF LOCATION IS VALID, SEND TO SERVER
    if (gps.location.isValid()) {

      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        String saatBilgisi = String(gps.time.hour() + 3) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());

        String url = serverName + "?lat=" + String(gps.location.lat(), 6) +
                     "&lng=" + String(gps.location.lng(), 6) +
                     "&alt=" + String(gps.altitude.meters(), 1) +
                     "&hiz=" + String(gps.speed.kmph(), 1) +
                     "&saat=" + saatBilgisi;

        Serial.print("Location found! Sending to server: ");
        Serial.println(url);

        http.begin(client, url);
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
          Serial.print("Success! Server response (200 expected): ");
          Serial.println(httpResponseCode);
        } else {
          Serial.print("HTTP send error: ");
          Serial.println(httpResponseCode);
        }
        http.end();
      } else {
        Serial.println("ERROR: Wi-Fi (internet) connection lost!");
      }

    }
    // IF LOCATION IS NOT YET VALID, PRINT INFO
    else {
      Serial.print("Wi-Fi connected but waiting for GPS fix... (satellites seen: ");
      Serial.print(gps.satellites.value());
      Serial.println(")");
    }

    sonGonderim = millis();
  }
}
