
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



#include "ArduinoUTMWiFiPortal.h"

ArduinoUTMWiFiPortal::ArduinoUTMWiFiPortal(const char* username, const char* password) {
  _username = username;
  _password = password;
  _lastCheckTime = 0;
  _checkInterval = 300000; // Default to 5 minutes
  _secureClient.setInsecure(); // IMPORTANT for UTM portal
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