




// BUNU YENİ YAPARSIN YENİ BİTKİ 
#include <Arduino.h>
#include <TimeLib.h>
#include <DallasTemperature.h>
#include <OneWire.h>
//#include <RTClib.h> // RTC modülü için kütüphane saat için

//RTC_DS3231 rtc; // RTC modülü nesnesi saat için
//char* ntpServerName = "time.google.com"; // tarih için
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 10800, 60000); // 10 saniyede bir NTP sunucusundan zaman al



#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#elif defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#include <FirebaseESP8266.h>
#endif


#define  trigPin  D1
#define echoPin D2
#define ahnatarPin D4


#define SOUND_VELOCITY 0.034
#define NUM_READINGS 10 // Hareketli ortalama için kullanılacak ölçüm sayısı

long readings[NUM_READINGS];
int diziIndex = 0; // "index" yerine "diziIndex" kullanıyoruz
long total = 0;
int sayac = 0;





long duration;
float distanceCm;



// Belirteç oluşturma süreci bilgisini sağlama
#include <addons/TokenHelper.h>

// RTDB verisi yazdırma bilgilerini ve diğer yardımcı işlevleri sağlama
#include <addons/RTDBHelper.h>




#define WIFI_SSID "wifi name"
#define WIFI_PASSWORD "sifre "


// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* API Key */
#define API_KEY "buraya firebase api keyi"

/* RTDB URL */
#define DATABASE_URL " firebase url" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4.  kullanıcı Email ve şifre  */
#define USER_EMAIL "firebase kullanıcı @gmail.com"
#define USER_PASSWORD "firabE kullanıco şifresi"

// Firebase Veri nesnesini tanımlayın
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

void setup()
{
  
  Serial.begin(115200);
   // RTC modülünü başlat
  
 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ahnatarPin, OUTPUT);  
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  multi.addAP(WIFI_SSID, WIFI_PASSWORD);
  multi.run();
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    if (millis() - ms > 1000)
      break;
#endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /*API anahtarını atıyorum */
  config.api_key = API_KEY;

  /* Kullanıcı oturum açma kimlik bilgilerini atıyorum */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* RTDB URL'sini atıyoruz  */
  config.database_url = DATABASE_URL;

  /*Uzun süredir devam eden belirteç oluşturma görevi için geri arama işlevini atayın */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // WiFi kimlik bilgileri Pico W için gereklidir
  // nedeniyle yeniden bağlanma özelliği yoktur.
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  config.wifi.clearAP();
  config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

  
  Firebase.begin(&config, &auth);

  // WiFi yeniden bağlantısı kodunuz veya üçüncü taraf kitaplığınız tarafından kontrol edildiğinde yorum yapın veya yanlış değer iletin
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  
  // NTP sunucusuna bağlan
  timeClient.begin();
 

}
void loop() {
  delay(1000); // 1 saniye bekle
     if (Firebase.ready()) {
       
       int isulamik = 1;
       
    
    Serial.printf("------------bu telefondan cekilen ışık verisi --> %s\n", Firebase.getInt(fbdo, F("/test/json/isik"), &isulamik) ? String(isulamik).c_str() : fbdo.errorReason().c_str()); 
  
if (isulamik == 1 && WiFi.status() == WL_CONNECTED) {
  digitalWrite(ahnatarPin, LOW);
  delay(1000);
} else {
  digitalWrite(ahnatarPin, HIGH);
}

  

  

      }
  long distance[3]; // Ölçülen mesafeleri saklamak için bir dizi

  for (int i = 0; i < 3; i++) {
    // Mesafe ölçümü yap
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    distance[i] = duration * SOUND_VELOCITY / 2;
    delay(400); // Ölçümler arasında kısa bir bekleme
  }

  // Ölçülen mesafeleri sırala
  for (int i = 0; i < 2; i++) {
    for (int j = i + 1; j < 3; j++) {
      if (abs(distance[i] - distance[j]) > 30) {
        // Eğer iki ölçüm arasındaki fark 30'dan fazla ise, bu ölçümleri kabul etme
        continue;
      }

      // İki ölçümün ortalamasını al
      long avgDistance = (distance[i] + distance[j]) / 2;

      double angle = (sayac - 1) * (M_PI / 30.0); // Her seferinde 10 derece arttır
      float x = avgDistance * cos(angle);
      float y = avgDistance * sin(angle);
      if (sayac < 60) {
      if (Firebase.ready()) {
        Serial.println("Ölçüm sayısı: " + String(sayac));
        FirebaseJson json2;
        String xKey = "/test/json/olcum/deger" + String(sayac) + "/x";
        String yKey = "/test/json/olcum/deger" + String(sayac) + "/y";
        Firebase.setDouble(fbdo, xKey.c_str(), x);
        Firebase.setDouble(fbdo, yKey.c_str(), y);
        Serial.println("Ölçüm değeri: " + String(avgDistance));
       int isulamik = 1;
       
    
    Serial.printf("------------bu telefondan cekilen ışık verisi --> %s\n", Firebase.getInt(fbdo, F("/test/json/isik"), &isulamik) ? String(isulamik).c_str() : fbdo.errorReason().c_str()); 
  
if (isulamik == 1 && WiFi.status() == WL_CONNECTED) {
  digitalWrite(ahnatarPin, LOW);
  delay(1000);
} else {
  digitalWrite(ahnatarPin, HIGH);
}

  

  

      }

      sayac += 1;

    }
    
    
      if (sayac > 251) {
        sayac = 1; // 120'den sonra tekrar 1'e dön
        
      }

      

      break; // İki yakın ölçüm bulunduğunda döngüyü sonlandır
    }
  }



  



}




  
