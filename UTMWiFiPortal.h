
//  ______    ______                           __  __ 
// /      \  /      \                         /  |/  |
///$$$$$$  |/$$$$$$  |______   _______    ____$$ |$$/ 
//$$ |__$$ |$$ |_ $$//      \ /       \  /    $$ |/  |
//$$    $$ |$$   |   $$$$$$  |$$$$$$$  |/$$$$$$$ |$$ |
//$$$$$$$$ |$$$$/    /    $$ |$$ |  $$ |$$ |  $$ |$$ |
//$$ |  $$ |$$ |    /$$$$$$$ |$$ |  $$ |$$ \__$$ |$$ |
//$$ |  $$ |$$ |    $$    $$ |$$ |  $$ |$$    $$ |$$ |
//$$/   $$/ $$/      $$$$$$$/ $$/   $$/  $$$$$$$/ $$/ 
// Created by Afandi Azmi, 2025




#ifndef UTMWiFiPortal_h
#define UTMWiFiPortal_h

#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

class UTMWiFiPortal {
  public:
    // Constructor
    UTMWiFiPortal(const char* username, const char* password);

    // Set the interval for checking connection (in milliseconds)
    void setCheckInterval(unsigned long interval);

    // Call this repeatedly in your main loop()
    void keepConnected();

    // Perform a single login attempt (useful for initial login)
    bool attemptLogin();

    // Check internet connection status manually
    bool checkInternet();

  private:
    // Credentials
    String _username;
    String _password;

    // Timing
    unsigned long _lastCheckTime;
    unsigned long _checkInterval;

    // Clients (managed internally)
    WiFiClientSecure _secureClient;
    WiFiClient _standardClient;

    // Constants
    const char* _loginURL = "https://smartzone22.utm.my:9998/SubscriberPortal/hotspotlogin";
    const char* _connectionCheckUrl = "http://connectivitycheck.gstatic.com/generate_204";
};

#endif