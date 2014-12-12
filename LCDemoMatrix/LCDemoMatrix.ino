// based on an orginal sketch by Arduino forum member "danigom"
// http://forum.arduino.cc/index.php?action=profile;u=188950

#include <avr/pgmspace.h>
#include <LedControl.h>

const int numDevices = 1;      // number of MAX7219s used
const long scrollDelay = 100;   // adjust scrolling speed

unsigned long bufferLong [14] = {0}; 

LedControl lc=LedControl(13,11,12,numDevices);

prog_uchar scrollText[] PROGMEM ={
    "  Testing MAX7219  \0"};

void setup(){
    for (int x=0; x<numDevices; x++){
        lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
        lc.setIntensity(x,5);       // Set the brightness to default value
        lc.clearDisplay(x);         // and clear the display
    }
}

void loop(){ 
  
  scrollMessage(scrollText);
    //scrollFont();
}


