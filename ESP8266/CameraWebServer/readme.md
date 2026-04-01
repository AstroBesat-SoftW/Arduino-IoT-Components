# Esp8266-Esp32Cam
<img width="1916" height="945" alt="image" src="https://github.com/user-attachments/assets/99dff9c9-a8b6-4dad-abbe-942893d70ce3" />

Serial print kısmında gelecek ip adresini alıyoruz ve giriyoruz tarayıcımızdan (aynı wifi bağlı olman gerek)!
-
Get the IP address displayed in the Serial Monitor and enter it into your browser (you must be connected to the same Wi-Fi network)!



.........................................................................................................................................................................................................................................................................................

kurulum ve bağlantı:
<img width="672" height="375" alt="image" src="https://github.com/user-attachments/assets/62fc3135-ed40-43bc-9a40-7873c61aae38" />

burada önemli olan "i" kısmına dikakt et esp32 cam de ve esp8266 da en soldaki kırmızı bağlantıya. bunları yapıp kodu çalıştır ama en altta dahil etmen gereken json ve kütüphane var indirmen gereken onlarıda yap ondan sonra çalıştır. çalıştırdıktan sonra kod yüklendikten sonra yapman gereken şu:

"i" bağlantısı var esp32cam kare içine aldım onu çıkar ve ardından esp32cam de buton var ona bas veya basılı tut arduino serial printte  sonra sana bağlantı başarılı diyip ip adresi verecek:
orn:
"WiFi connected
Camera Ready! Use 'http://172.20.10.2' to connect
"

artık kameranı kullanabilirsin.

soru? neden esp8266 da en solda kırmızılı olan "rst ve gnd" bir birine bağladık? onu bağlama sebebimiz açıkcası şöyle o bağlıyken esp8266 çalışmaz direkt esp32cam ile iletişim halinde olur gibi birşey kısa özet. bu sayede arduinoda ayarlardan esp8266 değil esp32cam seçer kodu ona göre çalıştırırım. bu kod ile işim bitince yani kamera ile işim bittince de esp8266 da olan "rst ve gnd" bağlantısını koparır artık esp8266 ya da kod yazabilir ve çalıştırabilir hale getiririm ve arduinodan esp8266 seçip ona kod yazar yüklerim (not bunlar ayrı yani esp8266 ve esp32cam ayrı işin özeti ayrı ayrı kod yüklüyoruz az önce anlattığım gibi. peki ikisini aynı anda nasıl kullanırız? ben şu şekil yaptım: ilk işte esp32cam e istediğim kodu yükledim mesela xxx siteme görüntüyü uyolladım oradan ardından esp8266 ya da o siteden  yolladığım görüntü ile çalışabilecek ortak bir kod yolladım. mesela uzaktan konttollu araç yapıyorsanız ilk esp32cam ile görüntümü yolladım siteme  esp8266 ile de işte dronu sağ ve sola hareket etmesini (motor çalışmasını sağlayan komutları kontrol eden sistem yaptım)   dıştan gören ise: görüntü ve uzaktan kontrol edebildiğim sistem.  yani iki parçayı tek parçada ayrı ayrı ama bir bütün oalrak birleştirdim. )






en alta start bas ve görüntü gelsin.

yüklediğim kütüphane:

esp32 2.0.5

dahil et: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json



