
#include "mqtt_configuration.h"

void setupWifi(){

	tryingConnect = true;
	
	digitalWrite(MQTT_CONNECTED_PIN, LOW);

	delay(5000);
	
	Serial.begin(XRF_BAUD);
    wiSerial.begin(XV_BAUD);

	WiFly.setUart(&wiSerial); // Tell the WiFly library that we are not using the SPIUart
	WiFly.begin();
	
	// Join the WiFi network
	if (!WiFly.join(ssid, passphrase, mode)) {
		Serial.println("Association failed.");
		setupWifi();
	}else{
		Serial.println("Association succeeded.");
		mqttConnect();
	}

	
}


