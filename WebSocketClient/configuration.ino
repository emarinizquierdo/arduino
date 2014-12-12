
void callbackMQTT(char* topic, byte* payload, unsigned int length) {
	
}

void configuration(){
  // Start Serial
  Serial.begin(XRF_BAUD);
#ifdef DEBUG_PRINT
  Serial.println(VERSION_STRING);
#endif
  
  // Start wiSerial
  wiSerial.begin(XV_BAUD);
  WiFly.setUart(&wiSerial);
  
  WiFly.begin();
  
  // Join the WiFi network
  if (!WiFly.join(mySSID, myPassword, WPA_MODE)) {
    while (1) {
      // Hang on failure.
#ifdef DEBUG_PRINT
      Serial.println("Failed to join/DHCP wifi");
#endif
    }
  } 
  
#ifdef DEBUG_PRINT
  Serial.println("Ethernet Up");
#endif  

   
}
