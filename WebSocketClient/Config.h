// baud rate for the XRF
#define XRF_BAUD 9600


// WiFly RN-XV details
#define XV_BAUD 9600
#define XV_TX 6
#define XV_RX 7


SoftwareSerial wiSerial(XV_RX, XV_TX);

WiFlyClient wifly;

const char mySSID[] = /*"Mordor";*/"Orange-0cdc";
const char myPassword[] = /*"AAAABBBBCCCCDDDDEEEEFFFF00";*/ "F512DAD64F3753936F2EE1F73E";

char *server = "hermes-nefele.rhcloud.com";//"echo.websocket.org";//

char inBuf[128];
char outBuf[128];
boolean inPacket = false;
int OUTPUTS_OFFSET = 8;
uint8_t inBufInd = 0;
uint8_t outBufInd = 0;

//char* mqttIp = "hermes-nefele.rhcloud.com";
byte mqttIp[] = {192,168,0,195};

#define MQTT_PORT 8000
// forward def of callback
void callbackMQTT(char*, byte*, unsigned int);
PubSubClient client(mqttIp, MQTT_PORT, callbackMQTT, wifly);

// ClientId for connecting to MQTT
#define CLIENT_ID "8567d471-b163-4318"

// Subscribe to topics
#define S_RX		"ok/tx/#"
#define S_RX_MASK   "ok/tx/"

// Publish Topics
#define P_TX		"ok/rx/"

// Status Topic, use to say we are alive or DEAD (will)
#define S_STATUS "ok/status"
#define P_STATUS "/sloriini/status"
#define STATUS_STRING "STATUS"
#define RUNNING "Running: OKMQTT"
#define RESTART "Restart: OKMQTT"
