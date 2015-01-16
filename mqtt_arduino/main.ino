#include "mqtt_configuration.h"


void setup()
{

	pinMode(MQTT_CONNECTED_PIN,OUTPUT);

	setupWifi();

}

void loop(){

	if(!wifiConnected){
		setupWifi();
	}

	if(!brokerConnected){
		mqttConnect();
	}

	statusDaemon();
	
	sentTemp();

}

