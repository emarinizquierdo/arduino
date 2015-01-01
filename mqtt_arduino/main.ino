#include "mqtt_configuration.h"


void setup()
{

	pinMode(MQTT_CONNECTED_PIN,OUTPUT);

	setupWifi();	

}

void loop(){
	//statusDaemon();
	sentTemp();
	client.loop();
}

