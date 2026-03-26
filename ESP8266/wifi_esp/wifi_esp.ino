#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// "bitki" Wi-Fi ağı
const char *sta_ssid = "bitki";
const char *sta_password = "12345678";

// "baglan" hotspot ağı
const char *ap_ssid = "baglan";
const char *ap_password = "";

// DNS ve Web Sunucusu
DNSServer dnsServer;
ESP8266WebServer server(80);

// ESP'nin IP adresi
IPAddress apIP(192, 168, 4, 1);

// HTML içeriği
const char *htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bağlantı Sayfası</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: column;
            height: 100vh;
            margin: 0;
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #f0f0f0;
        }
        .gif-container {
            margin-bottom: 20px;
        }
        img {
            width: 150px;
            height: 150px;
        }
        h1 {
            margin-bottom: 20px;
        }
        form {
            display: flex;
            flex-direction: column;
            align-items: center;
        }
        input {
            margin-bottom: 10px;
            padding: 10px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        button {
            padding: 10px 20px;
            font-size: 16px;
            color: white;
            background-color: #007bff;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        button:hover {
            background-color: #0056b3;
        }
    </style>
</head>
<body>
    <div class="gif-container">
        <img src="https://media.giphy.com/media/26BRrSvJUa0crqw4E/giphy.gif" alt="Gif">
    </div>
    <h1>Hoş Geldiniz</h1>
    <form action="/check_answer" method="POST">
        <label for="answer">Türkiye'de Cumhuriyetin ilan edildiği yıl nedir?</label><br>
        <input type="text" id="answer" name="answer" placeholder="Cevabınızı girin..." required>
        <button type="submit">Gönder</button>
    </form>
</body>
</html>
)rawliteral";

void connectToWiFi() {
  Serial.println("Wi-Fi'ye bağlanıyor...");
  WiFi.softAPdisconnect(true); // Hotspot'u kapat
  WiFi.begin(sta_ssid, sta_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi'ye bağlandı!");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  // SoftAP başlat (hotspot)
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // IP yapılandırması
  WiFi.softAP(ap_ssid, ap_password);

  Serial.println("Hotspot oluşturuldu:");
  Serial.print("SSID: ");
  Serial.println(ap_ssid);

  // DNS sunucusu başlat (tüm istekleri ESP'ye yönlendir)
  dnsServer.start(53, "*", apIP);

  // Ana sayfa (Captive Portal)
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  // Cevap kontrolü
  server.on("/check_answer", HTTP_POST, []() {
    if (server.hasArg("answer")) {
      String answer = server.arg("answer");
      if (answer == "1923") {
        server.send(200, "text/html", "<h1>Tebrikler, dogru cevap!</h1><a href='/connect'><button>internete baglan</button></a>");
      } else {
        server.send(200, "text/html", "<h1>Yanlis cevap. Tekrar deneyin.</h1><a href='/'><button>Geri Don</button></a>");
      }
    } else {
      server.send(400, "text/plain", "Cevap alınamadı!");
    }
  });

  // Bağlanma işlemi
  server.on("/connect", []() {
    server.send(200, "text/plain", "Wi-Fi'ye bağlanılıyor...");
    connectToWiFi();
  });

  // Yönlendirme
  server.onNotFound([]() {
    server.sendHeader("Location", String("http://192.168.4.1/"), true);
    server.send(302, "text/plain", "");
  });

  server.begin();
  Serial.println("Web sunucusu başlatıldı...");
}

void loop() {
  dnsServer.processNextRequest(); // DNS taleplerini yönet
  server.handleClient();          // Web sunucusu taleplerini yönet
}
