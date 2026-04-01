
## Setup and Connection

<img width="672" height="375" alt="image" src="https://github.com/user-attachments/assets/62fc3135-ed40-43bc-9a40-7873c61aae38" />

### Important Connection Notes
* Pay close attention to the connection marked **"i"** on the ESP32-CAM, as well as the red connection on the far left of the ESP8266 (**RST to GND**). Make sure these are connected before uploading.
* **Before running the code:** Ensure you have added the necessary JSON board URLs in the Arduino IDE preferences and installed the required libraries mentioned at the bottom of this repository. 

### After Uploading the Code
Once the code is successfully compiled and uploaded, follow these steps:

1. Disconnect the **"i"** connection (the one boxed on the ESP32-CAM in the image).
2. Press (or press and hold) the reset button on the ESP32-CAM.
3. Open the Arduino IDE **Serial Monitor**. It should say the connection is successful and provide an IP address, like this:

    ```text
    WiFi connected
    Camera Ready! Use '[http://172.20.10.2](http://172.20.10.2)' to connect
    ```

You can now use your camera!
Get the IP address displayed in the Serial Monitor and enter it into your browser (you must be connected to the same Wi-Fi network)!
---

## FAQ

**Why do we connect the "RST" and "GND" pins on the ESP8266 (the red connection on the far left)?** Briefly, connecting these pins disables the ESP8266's microcontroller (keeps it in a reset state). This essentially turns the ESP8266 into a simple USB-to-Serial converter, allowing us to communicate directly with the ESP32-CAM. Because of this setup, you must select the **ESP32-CAM** board in the Arduino IDE settings (not the ESP8266) to upload the code.

Once you are done uploading the code to the camera, you can remove the "RST to GND" jumper on the ESP8266. This makes the ESP8266 programmable and functional again. You can then select the ESP8266 board in the Arduino IDE and upload code specifically to it. 
*(Note: As explained, the ESP8266 and ESP32-CAM are separate modules, and we upload code to them individually.)*

**How do we use both modules together at the same time?** Here is my approach for integrating them:
* First, I upload the video streaming code to the **ESP32-CAM** (e.g., sending the live feed to a custom web interface).
* Next, I upload complementary code to the **ESP8266** so it can work in tandem with the commands sent from that same web interface.

**Example Use Case (Remote-Controlled Vehicle):** If you are building an RC car or drone, the ESP32-CAM is solely responsible for streaming the video to your interface. Meanwhile, the ESP8266 handles the mechanical controls (receiving commands to drive motors, steer left/right, etc.). From an outside perspective, it functions as a single, fully integrated system—a remotely controllable vehicle with a live camera feed. You are essentially combining two separate microcontrollers to work together as a complete system.



yüklediğim kütüphane:
install library
esp32 2.0.5

dahil et: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json


<img width="1916" height="945" alt="image" src="https://github.com/user-attachments/assets/99dff9c9-a8b6-4dad-abbe-942893d70ce3" />







