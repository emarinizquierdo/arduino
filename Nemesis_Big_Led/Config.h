
#undef PROGMEM 
#define PROGMEM __attribute__(( section(".progmem.data") )) 
#undef PSTR 
#define PSTR(s) (__extension__({static prog_char __c[] PROGMEM = (s); &__c[0];})) 

int processMessage();
void send(const char *data);
bool connect(const char *hostname, const char *path="/", uint16_t port=80);

SoftwareSerial wifiSerial(7,6);
WiFly wifly;

const char mySSID[] = "Orange-0cdc"; //"Mordor";
const char myPassword[] = "F512DAD64F3753936F2EE1F73E";//"AAAABBBBCCCCDDDDEEEEFFFF00";

char server[] = "ec2-54-218-141-96.us-west-2.compute.amazonaws.com";//"echo.websocket.org";//

char inBuf[128];
char outBuf[128];
boolean inPacket = false;
int OUTPUTS_OFFSET = 8;
uint8_t inBufInd = 0;
uint8_t outBufInd = 0;

/*
 * Set these constants to the values of the pins connected to the SureElectronics Module
 */
static const byte ht1632_data = 9;  // Data pin (pin 7)
static const byte ht1632_wrclk = 8; // Write clock pin (pin 5)
static const byte ht1632_cs = 10;    // Chip Select (pin 1)
static const byte ht1632_vcc = 11;
