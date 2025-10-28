// // This example demonstrates a simple usage of the ArduinoArduinoUTMWiFiPortal library to connect
// // to the UTM WiFi captive portal and maintain the connection.
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

#include <WiFi.h>
#include <ArduinoArduinoUTMWiFiPortal.h> // Include the library header

// --- Your Credentials ---
const char* WIFI_SSID = "UTMWiFi"; // Or your specific SSID
const char* WIFI_PASS = "";        // Password if needed
const char* PORTAL_USER = "YourID";
const char* PORTAL_PASS = "YourPassword";

// --- Create an instance of the library ---
ArduinoArduinoUTMWiFiPortal portal(PORTAL_USER, PORTAL_PASS);

void setup() {
  Serial.begin(115200);
  Serial.println("\nBooting...");

  Serial.print("Connecting to WiFi: "); Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(500); }
  Serial.println("\nWiFi connected!"); Serial.print("IP address: "); Serial.println(WiFi.localIP());

  // --- Set custom check interval (e.g., 2 minutes = 120000 ms) ---
  portal.setCheckInterval(120000);

  // --- Perform initial login ---
  Serial.println("Performing initial portal login...");
  if (portal.attemptLogin()) {
    Serial.println("Initial login attempt successful (check internet next).");
  } else {
    Serial.println("Initial login attempt failed.");
  }

  // --- Wait a bit and check connection ---
  delay(2000);
  if (portal.checkInternet()) {
     Serial.println("Setup complete: Internet OK.");
     // You could send a Telegram message here if needed
  } else {
     Serial.println("Setup complete: Internet check FAILED after login.");
     // You could send a Telegram message here if needed
  }
  Serial.println("Main loop starting...");
}

void loop() {
  // --- Keep the portal connection alive ---
  portal.keepConnected();

  // --- Your other code (like checking Telegram bot) goes here ---
  // Example:
  // if (millis() > lastTimeBotRan + botRequestDelay) {
  //   // check bot messages...
  //   lastTimeBotRan = millis();
  // }

  // Add a small delay if your loop is very fast
   delay(50);
}