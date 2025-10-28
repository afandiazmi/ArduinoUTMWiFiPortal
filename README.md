# ArduinoUTMWiFiPortal

[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/afandiazmi/ArduinoUTMWiFiPortal)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

A library for Arduino ESP32 that handles automatic login and reconnection to the Universiti Teknologi Malaysia (UTM) WiFi captive portal. It periodically checks internet connectivity and re-authenticates if the connection is lost, ensuring seamless internet access for your ESP32 projects.

## Features

- Automatic login to UTM WiFi captive portal
- Periodic internet connectivity checks
- Re-authentication on connection loss
- Configurable check intervals
- Simple API for integration into your projects
- Designed specifically for ESP32 boards

## Installation

### Via Arduino IDE Library Manager

1. Open the Arduino IDE
2. Go to **Sketch** > **Include Library** > **Manage Libraries...**
3. Search for "ArduinoUTMWiFiPortal"
4. Click **Install**

### Manual Installation

1. Download the latest release from [GitHub](https://github.com/afandiazmi/ArduinoUTMWiFiPortal/releases)
2. Extract the ZIP file
3. Copy the `ArduinoUTMWiFiPortal` folder to your Arduino libraries directory (usually `~/Documents/Arduino/libraries/` on Windows)

### Dependencies

This library requires the following Arduino libraries:

- WiFi
- HTTPClient

Make sure these are installed in your Arduino IDE.

## Usage

1. Include the library in your sketch:

   ```cpp
   #include <ArduinoUTMWiFiPortal.h>
   ```

2. Create an instance with your portal credentials:

   ```cpp
   const char* PORTAL_USER = "YourID";
   const char* PORTAL_PASS = "YourPassword";
   ArduinoUTMWiFiPortal portal(PORTAL_USER, PORTAL_PASS);
   ```

3. In `setup()`, connect to WiFi and perform initial login:

   ```cpp
   WiFi.begin(WIFI_SSID, WIFI_PASS);
   // ... wait for connection ...
   portal.attemptLogin();
   ```

4. In `loop()`, call `keepConnected()` to maintain the connection:
   ```cpp
   portal.keepConnected();
   ```

## Example

See the `examples/SimpleConnectionExample/` directory for a complete working example.

```cpp
#include <WiFi.h>
#include <ArduinoUTMWiFiPortal.h>

const char* WIFI_SSID = "UTMWiFi";
const char* PORTAL_USER = "YourID";
const char* PORTAL_PASS = "YourPassword";

ArduinoUTMWiFiPortal portal(PORTAL_USER, PORTAL_PASS);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  portal.setCheckInterval(120000); // Check every 2 minutes
  portal.attemptLogin();
}

void loop() {
  portal.keepConnected();
  // Your code here
  delay(50);
}
```

## API Reference

### Constructor

- `ArduinoUTMWiFiPortal(const char* username, const char* password)` - Create a portal instance with credentials

### Methods

- `void setCheckInterval(unsigned long intervalMs)` - Set the interval for connectivity checks (default: 60000ms)
- `bool attemptLogin()` - Attempt to log in to the portal
- `bool checkInternet()` - Check if internet connectivity is available
- `void keepConnected()` - Maintain connection by checking and re-authenticating if needed

## Compatibility

- **Board**: ESP32
- **Arduino IDE**: 1.8.0 or later

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

**Afandi Azmi** - [afandi_army@live.com](mailto:afandi_army@live.com)

## Repository

[https://github.com/afandiazmi/ArduinoUTMWiFiPortal](https://github.com/afandiazmi/ArduinoUTMWiFiPortal)
