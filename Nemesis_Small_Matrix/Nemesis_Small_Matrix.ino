#include "utility/stringbuffer.h"
#include "aJSON.h"
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <LedControl.h>
#include <SoftwareSerial.h>
#include <WiFlyHQ.h>
#include "Config.h"



LedControl lc=LedControl(13,11,12,1);

void setup(){

	lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
    lc.setIntensity(0,5);       // Set the brightness to default value
    lc.clearDisplay(0);         // and clear the display
    
	configuration();   

}

void loop(){
	processMessage();  	
}
