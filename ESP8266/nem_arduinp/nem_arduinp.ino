#include <Servo.h>

Servo benimServom;       // Servo nesnesini oluşturuyoruz
const int servoPin = D0; // Servonun sinyal kablosunun bağlı olduğu pin

void setup() {
  benimServom.attach(servoPin); 
  
  // İlk merkezi 20 derece olarak ayarlıyoruz
  benimServom.write(20);        
  delay(2000); // 2 saniye bekle
}

void loop() {
  // Merkezden (20°) 40 derece yukarı çık (20 + 40 = 60 derece)
  benimServom.write(40);
  delay(2000); // 2 saniye bekle

  // Merkezden (20°) 40 derece aşağı inmek -20 derece yapar.
  // Servo 0'ın altına inemeyeceği için güvenli alt sınır olan 0'a gidiyoruz.
  benimServom.write(10);
  delay(2000); // 2 saniye bekle
  
  // Tekrar merkeze (20 dereceye) dön
  benimServom.write(20);   
  delay(2000); // 2 saniye bekle
}
