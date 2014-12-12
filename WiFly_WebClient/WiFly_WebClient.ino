
// (Based on Ethernet's WebClient Example)

#include <SPI.h>
#include <WiFly.h>
#include <SoftwareSerial.h>

#include "Credentials.h"

#define XV_TX 6
#define XV_RX 7

SoftwareSerial wiSerial(XV_RX, XV_TX);

byte server[] = { 66, 249, 89, 104 }; // Google

//Client client(server, 80);

WiFlyClient client;

void setup() {
  
  Serial.begin(9600);

  Serial.println("probando failed.");
  // Start wiSerial
  wiSerial.begin(9600);
  WiFly.setUart(&wiSerial);
	
  WiFly.begin();
  
  if (!WiFly.join(ssid, passphrase)) {
    Serial.println("Association failed.");
    while (1) {
      // Hang on failure.
    }
  }  

  Serial.println("connecting...");

  if (client.connect("google.com", 80)) {
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }
  
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}


