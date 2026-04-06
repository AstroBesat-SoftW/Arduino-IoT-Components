import cv2
import requests

# ESP8266'nın IP adresi ve portu
ESP8266_IP = "http://192.168.117.205"  # ESP8266 IP'sini güncelleyin
LED_ON_ENDPOINT = f"{ESP8266_IP}/led_on"
LED_OFF_ENDPOINT = f"{ESP8266_IP}/led_off"

# Haar Cascade model dosyasını yükle
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")

# Kamerayı başlat
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Gri tonlamaya dönüştür
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # İnsan (yüz) algıla
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # Algılanan yüzlerin etrafına dikdörtgen çiz
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)

    # Görüntüyü göster
    cv2.imshow("Kamera", frame)

    # Eğer yüz algılandıysa LED'i yak
    if len(faces) > 0:
        print("İnsan algılandı! LED'i yakıyorum...")
        try:
            requests.get(LED_ON_ENDPOINT)
        except:
            print("ESP8266'ya bağlanılamadı.")
    else:
        try:
            requests.get(LED_OFF_ENDPOINT)
        except:
            print("ESP8266'ya bağlanılamadı.")

    # 'q' tuşuna basarak çık
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
