#define VERSION_NUM 003
#define VERSION_STRING "OKMQTT ver: 003"

#define DEBUG_PRINT

#include <SPI.h>
#include <WiFly.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
//#include "Credentials.h"
#include "Config.h"

/**************************************************** 
 * check we are still connected to MQTT
 * reconnect if needed
 *  
 ****************************************************/
void checkMQTT()
{
  	if(!client.connected()){
		if (client.connect(CLIENT_ID)) {
			client.publish(P_STATUS, RESTART);
			client.subscribe(S_RX);
			client.subscribe(S_STATUS);
#ifdef DEBUG_PRINT
			Serial.println("MQTT Reconnect");
#endif
		}else{
                      Serial.println("MQTT Error");
}
	}
} 

void setup()
{


    configuration();
    checkMQTT();
}

void loop() 
{


    
}


// Update these with values suitable for your network.
/*



void setup()
{
  Ethernet.begin(mac, ip);
  if (client.connect("arduinoClient")) {
    client.publish("outTopic","hello world");
    client.subscribe("inTopic");
  }
}

void loop()
{
  client.loop();
}

*/
