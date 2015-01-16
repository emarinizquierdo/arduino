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

	Serial.println("Trying connect to MQTT broker");
	tryingConnectBroker = true;

	if (client.connect(CLIENT_ID)) {
		digitalWrite(MQTT_CONNECTED_PIN, HIGH);
  		Serial.println("Connected to MQTT Broker");
  		client.publish(P_STATUS, "OK");
  		brokerConnected = true;
  		tryingConnectBroker = false;
	}
	else {
		Serial.println("Connection to MQTT Broker failed.");
		brokerConnected = false;
		tryingConnectBroker = false;
	}

}

void statusDaemon(){
/*
	if(!client.connected()){
		wifiConnected = false;
		Serial.println("Wifi is not connected");
	}
*/
	if(!tryingConnectWifi && !tryingConnectBroker && wifiConnected && brokerConnected && (millis() - timestamp > MQTT_STATUS_DAEMON)) {
		timestamp = millis();
		client.publish(P_STATUS, "OK");
		delay(50);
		Serial.println("Daemon active");
		if(!client.loop()){
			brokerConnected = false;
		}
	}
	
}

void sentTemp(){

	uint8_t output[10];
	size_t output_len;
	char* sensorName;

	int randNumber;
	String str, str2;


	if(!tryingConnectWifi &&  !tryingConnectBroker && wifiConnected && brokerConnected && (( millis() - plottertimestamp ) > PLOTTER_TIMEOUT)) {

		plottertimestamp = millis();
		randNumber = random(100);
		str = String(randNumber);
		str2 = "{\"value\":" + str + "}";

		// Length (with one extra character for the null terminator)
		int str_len = str.length() + 1; 
		int str_len2 = str2.length() + 1; 

		// Prepare the character array (the buffer) 
		char char_array[str_len];
		char char_array2[str_len2];

		// Copy it over 
		str.toCharArray(char_array, str_len);
		str2.toCharArray(char_array2, str_len2);


		client.publish("/simpleLine/draw/a98a7226-ba29-44d8/78c42258-2d5f-40c8", char_array);
		

		delay(200);
		Serial.println(char_array);

		if(!client.loop()){
			Serial.println("el primer loop falla");
			brokerConnected = false;
		}

		client.publish("/plotter/draw/a98a7226-ba29-44d8/78c42258-2d5f-40c8", char_array2);

		delay(200);
		Serial.println(char_array2);

		if(!client.loop()){
			Serial.println("el segundo loop falla");
			brokerConnected = false;
		}

	}

	
}