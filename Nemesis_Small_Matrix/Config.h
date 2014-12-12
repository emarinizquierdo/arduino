
#undef PROGMEM 
#define PROGMEM __attribute__(( section(".progmem.data") )) 
#undef PSTR 
#define PSTR(s) (__extension__({static prog_char __c[] PROGMEM = (s); &__c[0];})) 

int processMessage();
void send(const char *data);
bool connect(const char *hostname, const char *path="/", uint16_t port=80);

SoftwareSerial wifiSerial(7,6);
WiFly wifly;

//const char mySSID[] = "Orange-0cdc";
const char mySSID[] = "Mordor";
//const char myPassword[] = "F512DAD64F3753936F2EE1F73E";
const char myPassword[] = "AAAABBBBCCCCDDDDEEEEFFFF00";
int WPA_WEP_MODE = WIFLY_MODE_WPA;
//int WPA_WEP_MODE = WIFLY_MODE_WEP;

char server[] = "ec2-54-218-246-47.us-west-2.compute.amazonaws.com";//"echo.websocket.org";//

char inBuf[255];
boolean inPacket = false;
int OUTPUTS_OFFSET = 8;
int inBufInd = 0;
int outBufInd = 0;

const int numDevices = 1;      // number of MAX7219s used
const long scrollDelay = 100;   // adjust scrolling speed

unsigned long bufferLong [14] = {0};
