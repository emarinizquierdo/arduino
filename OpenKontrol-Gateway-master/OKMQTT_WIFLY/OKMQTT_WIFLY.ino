#include <SPI.h>
#include <WiFly.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include "Credentials.h"

// Update these with values suitable for your network.
//byte server[] = { 192, 168, 0, 195 };
SoftwareSerial wiSerial(7, 6);

// Update these with values suitable for your network.
//uint8_t server[] = { 150, 140, 5, 20 };
char *server = "hermes-nefele.rhcloud.com";

char *mac;				//wifly mac address
char channel[30];		//topic to subscribe to (s + mac)

WiFlyClient wiFlyClient;
PubSubClient client(server, 8000, callback, wiFlyClient);

void callback(char* topic, uint8_t* payload, unsigned int length) {
	// handle message arrived
	/* topic = part of the variable header:has topic name of the topic where the publish received
	 * NOTE: variable header does not contain the 2 bytes with the 
	 *       publish msg ID
	 * payload = pointer to the first item of the buffer array that
	 *           contains the message tha was published
	 *          EXAMPLE of payload: lights,1
	 * length = the length of the payload, until which index of payload
	 */
	digitalWrite(8, HIGH);
	delay(200);
	digitalWrite(8, LOW);
	delay(200);
	
}

void setup()
{
	pinMode(8,OUTPUT);

	// lots of time for the WiFly to start up
	delay(5000);
	
	Serial.begin(9600);   // Start hardware Serial for the RN-XV

        wiSerial.begin(9600);
	WiFly.setUart(&wiSerial); // Tell the WiFly library that we are not using the SPIUart
	
	WiFly.begin();
	
	// Join the WiFi network
	if (!WiFly.join(ssid, passphrase, mode)) {
		Serial.println("Association failed.");
		while(1){
			// Hang on failure.
		}
	}
	Serial.println("Association succeeded.");


  Serial.println("connecting...");
WiFlyClient client2;
  if (client2.connect(server, 8000)) {
    Serial.println("connected");
    client2.println("GET /devices HTTP/1.0");
    client2.println();
  } else {
    Serial.println("connection failed");
  }
  
	if (client.connect("8567d471-b163-4318")) {

  Serial.println("allright");
  
	}
	else
		Serial.println("Connection failed.");
}

void loop()
{
	static unsigned long timestamp = 0;
	if(!client.loop()) {
		Serial.println("Client disconnected.");
		while(1) {}
	}
	if(millis() - timestamp > 30000) {
		timestamp = millis();
		
	}
}

