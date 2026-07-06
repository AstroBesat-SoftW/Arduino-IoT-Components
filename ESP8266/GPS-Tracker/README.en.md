[🇹🇷 Türkçe için tıklayın](README.tr.md) | 🇬🇧 English (current)

# ESP8266 Live GPS Tracker

A simple real-time GPS tracking system built with an **ESP8266** and a **NEO-6M GPS module**. The device reads GPS coordinates, sends them to a PHP endpoint over Wi-Fi, and a web page displays the live location on an interactive **Leaflet.js** map that auto-refreshes every few seconds.

## 📸 Preview

The dashboard shows the current time, altitude, speed, and last update time, alongside a live map marker that follows the device's position.

## 🧩 How It Works

```
[ NEO-6M GPS ] --(serial)--> [ ESP8266 ] --(Wi-Fi / HTTP GET)--> [ kaydet.php ] --> [ konum.json ]
                                                                                          |
                                                                                          v
                                                                          [ index.html + Leaflet.js ]
                                                                          (polls konum.json every 3s)
```

1. The **NEO-6M GPS module** sends raw NMEA data to the ESP8266 over a software serial connection.
2. The **ESP8266** parses this data using the `TinyGPS++` library.
3. Every 5 seconds, if a valid GPS fix is available, the ESP8266 sends the coordinates (latitude, longitude, altitude, speed, time) to a PHP script via an HTTP GET request.
4. The **PHP script** (`kaydet.php`) receives the parameters and writes them to a `konum.json` file on the server.
5. The **web page** (`index.html`) uses Leaflet.js to display a map, fetching `konum.json` every 3 seconds and updating the marker position live.

## 📁 Project Structure

| File | Description |
|---|---|
| `firmware/esp8266_gps_tracker.ino` | Arduino sketch that runs on the ESP8266, reads GPS data, and sends it to the server |
| `server/kaydet.php` | PHP endpoint that receives GPS data via GET and saves it as JSON |
| `server/index.html` | Front-end map page using Leaflet.js, polls the JSON file and updates the marker |
| `server/konum.json` | Example/generated data file holding the latest location (auto-created by the PHP script) |

## 🛠️ Hardware Requirements

- ESP8266 board (e.g. NodeMCU, Wemos D1 Mini)
- NEO-6M (or compatible) GPS module
- Jumper wires
- A web server with PHP support (shared hosting works fine)

### Wiring

| GPS Module | ESP8266 |
|---|---|
| TX | D1 (GPIO5) |
| RX | D2 (GPIO4) |
| VCC | 3.3V / 5V (check your module's specs) |
| GND | GND |

## ⚙️ Setup Instructions

### 1. Server side

1. Upload `server/kaydet.php` and `server/index.html` to your web hosting (must support PHP).
2. Make sure the server directory is writable so `kaydet.php` can create/update `konum.json`.
3. Note your server URL, e.g. `http://yourdomain.com/maps/kaydet.php`.

### 2. Firmware side

1. Open `firmware/esp8266_gps_tracker.ino` in the Arduino IDE.
2. Install the required libraries via Library Manager:
   - `ESP8266WiFi` (bundled with ESP8266 board package)
   - `ESP8266HTTPClient` (bundled with ESP8266 board package)
   - `TinyGPS++`
3. Update the following variables with your own credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const String serverName = "http://yourdomain.com/maps/kaydet.php";
```

4. Wire the GPS module as described above.
5. Upload the sketch to your ESP8266.
6. Open the Serial Monitor (115200 baud) to confirm Wi-Fi connection and GPS fix status.

### 3. View the live map

Open `index.html` (hosted on your server) in a browser. The map will center on the device's location once the first valid GPS fix is received, and will keep following the marker as it updates.

## 🔒 Security Notes

- This example sends data over plain HTTP with no authentication — anyone with the URL could theoretically post fake location data. For production use, consider adding an API key/token check in `kaydet.php` and switching to HTTPS.
- Do not commit real Wi-Fi credentials or your real server domain to a public repository. Replace them with placeholders before pushing (see `firmware/esp8266_gps_tracker.ino`).

## 📄 License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.

## 🙌 Credits

- [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus) library for GPS parsing
- [Leaflet.js](https://leafletjs.com/) for the interactive map
- [OpenStreetMap](https://www.openstreetmap.org/) for map tiles
