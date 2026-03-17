#include <NewPing.h>

//#define TRIGGER_PIN 9
//#define ECHO_PIN 10
#define TRIGGER_PIN D1  // GPIO5
#define ECHO_PIN D2     // GPIO4

#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;

//const int buzzerPin = 11;
const int buzzerPin = D3;  // GPIO0

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  noInterrupts(); // Kesme vektörünü devre dışı bırak
}

void loop() {
  distance = sonar.ping_cm();

  Serial.print("Mesafe = ");

  if (distance >= 400 || distance <= 2) {
    Serial.println("Aralık dışında");
    digitalWrite(buzzerPin, LOW);
  } else if (distance == 20) {
    Serial.println(distance);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  } else if (distance == 40) {
    Serial.println(distance);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  } else if (distance > 40 && distance < 100) {
    Serial.println(distance);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
  } else {
    Serial.println(distance);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }

  delay(500);
  interrupts(); // Kesme vektörünü yeniden etkinleştir
}





/*#include "NewPing.h"
// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 9
#define ECHO_PIN 10
// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400  
// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;
void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
  // Send ping, get distance in cm
  distance = sonar.ping_cm();
  
  // Send results to Serial Monitor
  Serial.print("Mesafe = ");
  
  if (distance >= 400 || distance <= 2) 
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
} */
