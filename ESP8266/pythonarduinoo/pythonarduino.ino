#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "?__?";  // WiFi ağ adı
const char* password = "?__?";  // WiFi şifresi

ESP8266WebServer server(80);

// LED D3 Pin
const int LED_PIN = D3;
const int LED_PIN2 = D4;

void handleLEDOn() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN2, LOW);
  server.send(200, "text/plain", "LED Açıldı");
}

void handleLEDOff() {
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN2, HIGH);
  server.send(200, "text/plain", "LED Kapatıldı");
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN2, LOW);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("WiFi bağlanıyor");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Bağlandı!");
  Serial.println(WiFi.localIP());

  server.on("/led_on", handleLEDOn);
  server.on("/led_off", handleLEDOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
