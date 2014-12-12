#include "Arduino.h"
#include <WiFlyHQ.h>
#include <SoftwareSerial.h>
#include "ht1632c.h"
#include "Config.h"

void setup(){
	ht1632_initialize();
	configuration();   
}

void loop(){  
	processMessage();
	readTerminal();  
}
