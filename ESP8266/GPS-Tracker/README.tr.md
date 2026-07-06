[🇬🇧 Click for English](README.en.md) | 🇹🇷 Türkçe (mevcut)

# ESP8266 Canlı GPS Takip Sistemi

**ESP8266** ve **NEO-6M GPS modülü** kullanılarak yapılmış basit bir gerçek zamanlı konum takip sistemi. Cihaz GPS koordinatlarını okur, Wi-Fi üzerinden bir PHP servisine gönderir ve bir web sayfası, birkaç saniyede bir kendini yenileyen etkileşimli **Leaflet.js** haritası üzerinde canlı konumu gösterir.

## 📸 Önizleme

Panelde anlık saat, rakım, hız ve son güncelleme zamanı gösterilir; harita üzerindeki pin de cihazın konumunu takip eder.

## 🧩 Nasıl Çalışır?

```
[ NEO-6M GPS ] --(seri port)--> [ ESP8266 ] --(Wi-Fi / HTTP GET)--> [ kaydet.php ] --> [ konum.json ]
                                                                                              |
                                                                                              v
                                                                              [ index.html + Leaflet.js ]
                                                                              (her 3 saniyede konum.json'u okur)
```

1. **NEO-6M GPS modülü**, ham NMEA verilerini yazılımsal seri port (software serial) üzerinden ESP8266'ya gönderir.
2. **ESP8266**, bu verileri `TinyGPS++` kütüphanesi ile ayrıştırır (parse eder).
3. Her 5 saniyede bir, geçerli bir GPS konumu (fix) varsa, ESP8266 koordinatları (enlem, boylam, rakım, hız, saat) HTTP GET isteği ile bir PHP betiğine gönderir.
4. **PHP betiği** (`kaydet.php`) gelen parametreleri alır ve `konum.json` dosyasına yazar.
5. **Web sayfası** (`index.html`), Leaflet.js kullanarak bir harita gösterir; her 3 saniyede bir `konum.json` dosyasını çeker ve pinin konumunu günceller.

## 📁 Proje Yapısı

| Dosya | Açıklama |
|---|---|
| `firmware/esp8266_gps_tracker.ino` | ESP8266 üzerinde çalışan, GPS verisini okuyup sunucuya gönderen Arduino kodu |
| `server/kaydet.php` | GET ile gelen GPS verisini alıp JSON olarak kaydeden PHP servisi |
| `server/index.html` | Leaflet.js kullanan, JSON dosyasını periyodik çeken ve pini güncelleyen ön yüz (harita) sayfası |
| `server/konum.json` | En son konum bilgisini tutan örnek/otomatik oluşturulan veri dosyası (PHP tarafından oluşturulur) |

## 🛠️ Gerekli Donanımlar

- ESP8266 kart (örn. NodeMCU, Wemos D1 Mini)
- NEO-6M (veya uyumlu) GPS modülü
- Jumper kablolar
- PHP destekleyen bir web sunucusu (paylaşımlı hosting de yeterlidir)

### Bağlantı Şeması

| GPS Modülü | ESP8266 |
|---|---|
| TX | D1 (GPIO5) |
| RX | D2 (GPIO4) |
| VCC | 3.3V / 5V (modülünüzün özelliklerini kontrol edin) |
| GND | GND |

## ⚙️ Kurulum Talimatları

### 1. Sunucu Tarafı

1. `server/kaydet.php` ve `server/index.html` dosyalarını PHP destekleyen hosting hesabınıza yükleyin.
2. `kaydet.php`'nin `konum.json` dosyasını oluşturabilmesi/güncelleyebilmesi için sunucu dizininin yazılabilir olduğundan emin olun.
3. Sunucu adresinizi not edin, örn. `http://siteadresiniz.com/maps/kaydet.php`.

### 2. Donanım/Yazılım (Firmware) Tarafı

1. `firmware/esp8266_gps_tracker.ino` dosyasını Arduino IDE'de açın.
2. Kütüphane Yöneticisi'nden gerekli kütüphaneleri yükleyin:
   - `ESP8266WiFi` (ESP8266 kart paketiyle birlikte gelir)
   - `ESP8266HTTPClient` (ESP8266 kart paketiyle birlikte gelir)
   - `TinyGPS++`
3. Aşağıdaki değişkenleri kendi bilgilerinizle güncelleyin:

```cpp
const char* ssid = "WIFI_ADINIZ";
const char* password = "WIFI_SIFRENIZ";
const String serverName = "http://siteadresiniz.com/maps/kaydet.php";
```

4. GPS modülünü yukarıdaki şemaya göre bağlayın.
5. Kodu ESP8266'ya yükleyin.
6. Wi-Fi bağlantısını ve GPS konum durumunu kontrol etmek için Seri Port Monitörünü (115200 baud) açın.

### 3. Canlı Haritayı Görüntüleme

Sunucunuzda barındırılan `index.html` dosyasını bir tarayıcıda açın. İlk geçerli GPS konumu alındığında harita cihazın konumuna odaklanacak ve güncellemeler geldikçe pini takip etmeye devam edecektir.

## 🔒 Güvenlik Notları

- Bu örnek, verileri kimlik doğrulaması olmadan düz HTTP üzerinden gönderir — URL'yi bilen herkes teorik olarak sahte konum verisi gönderebilir. Gerçek kullanım için `kaydet.php` içine bir API anahtarı/token kontrolü eklemenizi ve HTTPS'ye geçmenizi öneririz.
- Gerçek Wi-Fi bilgilerinizi veya gerçek sunucu adresinizi herkese açık bir repoya commit etmeyin. Paylaşmadan önce bunları örnek/placeholder değerlerle değiştirin (bkz. `firmware/esp8266_gps_tracker.ino`).

## 📄 Lisans

Bu proje MIT Lisansı altında paylaşılmıştır. Ayrıntılar için [LICENSE](LICENSE) dosyasına bakın.

## 🙌 Teşekkürler

- GPS ayrıştırma için [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus) kütüphanesi
- Etkileşimli harita için [Leaflet.js](https://leafletjs.com/)
- Harita katmanları için [OpenStreetMap](https://www.openstreetmap.org/)
