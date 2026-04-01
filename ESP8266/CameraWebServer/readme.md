# Esp8266-Esp32Cam
<img width="1916" height="945" alt="image" src="https://github.com/user-attachments/assets/99dff9c9-a8b6-4dad-abbe-942893d70ce3" />

Serial print kısmında gelecek ip adresini alıyoruz ve giriyoruz tarayıcımızdan (aynı wifi bağlı olman gerek)!
-
Get the IP address displayed in the Serial Monitor and enter it into your browser (you must be connected to the same Wi-Fi network)!



.........................................................................................................................................................................................................................................................................................

## Installation and Wiring

<img width="672" height="375" alt="image" src="https://github.com/user-attachments/assets/62fc3135-ed40-43bc-9a40-7873c61aae38" />

**Important Wiring Notes:** Pay close attention to the connection marked with **"i"** on the ESP32-CAM and the red wire connection on the far left of the ESP8266. 

Before uploading the code, make sure you have added the necessary board manager JSON URLs and downloaded the required libraries mentioned at the bottom of this documentation.

### After Uploading the Code:
Once the code has been successfully uploaded to the ESP32-CAM, follow these steps:

1. **Disconnect** the jumper wire marked **"i"** (the one highlighted in the square) on the ESP32-CAM.
2. Press or hold the **RESET button** on the ESP32-CAM.
3. Open the **Arduino Serial Monitor**. You should see a successful connection message along with your local IP address:

```text
WiFi connected
Camera Ready! Use '[http://172.20.10.2](http://172.20.10.2)' to connect''' 








yüklediğim kütüphane:

esp32 2.0.5

dahil et: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json



