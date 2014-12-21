#include "mqtt_configuration.h"

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

void mqttConnect(){

	if (client.connect(CLIENT_ID)) {
		digitalWrite(MQTT_CONNECTED_PIN, HIGH);
  		Serial.println("Connected to MQTT Broker");
  		client.publish(P_STATUS, "OK");
  		connected = true;
  		tryingConnect = false;
	}
	else {
		Serial.println("Connection failed.");
		connected = false;
		tryingConnect = false;
		setupWifi();
	}
}

void statusDaemon(){

	if(!tryingConnect && !client.loop()) {
		digitalWrite(MQTT_CONNECTED_PIN, LOW);
		connected = false;
		Serial.println("Client disconnected.");
		setupWifi();
	}

	if(connected && !tryingConnect && (millis() - timestamp > MQTT_STATUS_DAEMON)) {
		timestamp = millis();
		client.publish(P_STATUS, "OK");
		Serial.println("Daemon active");
	}

	
}