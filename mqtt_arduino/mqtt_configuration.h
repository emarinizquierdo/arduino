
#ifndef  mqtt_configuration_h
#define  mqtt_configuration_h

#include <SPI.h>
#include <WiFly.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include "Credentials.h"

/**************************************************** 
 * genral defines
 * use for staic config bits
 ****************************************************/
// Status LED
#define STATUS_LED 17
#define STATUS_TOGGLE_TIMEOUT 500
#define MQTT_CONNECTED_PIN 13
#define MQTT_STATUS_DAEMON 3000
unsigned long statusTimeOut = 0;
static unsigned long timestamp = 0;
bool tryingConnect = false;
bool connected = false;
byte statusState = 0;

// baud rate for the XRF
#define XRF_BAUD 9600


// WiFly RN-XV details
#define XV_BAUD 9600
#define XV_TX 6
#define XV_RX 7


//LLAP messgaes are 12 char's long + NULL terminator
#define LLAP_BUFFER_LENGTH 13
#define LLAP_DEVID_LENGTH 2
#define LLAP_DATA_LENGTH 9

#define MQTT_PORT 1883

// ClientId for connecting to MQTT
#define CLIENT_ID "8567d471-b163-4318"
#define CLIENT_SECRET "/f27b6108-195a-48e8"

// Subscribe to topics
#define S_RX		"ok/tx/#"
#define S_RX_MASK   "ok/tx/"

// Publish Topics
#define P_TX		"ok/rx/"

// Status Topic, use to say we are alive or DEAD (will)
#define S_STATUS "/sloriini/status/8567d471-b163-4318/f27b6108-195a-48e8"
#define P_STATUS "/sloriini/status/8567d471-b163-4318/f27b6108-195a-48e8"
#define STATUS_STRING "STATUS"
#define RUNNING "Running: OKMQTT"
#define RESTART "Restart: OKMQTT"

/****************************************************
 * function definitions
 *
 ****************************************************/
void callback(char* topic, uint8_t* payload, unsigned int length);
void setupWifi();

/**************************************************** 
 * global vars
 * 
 ****************************************************/
char LLAPmsg[LLAP_BUFFER_LENGTH];
SoftwareSerial wiSerial(XV_RX, XV_TX);


/**************************************************** 
 * Ethernet settings
 * Update these with values suitable for your network.
 *
 ****************************************************/
// WiFly library currently only uses DHCP
 byte server[] = { 192, 168, 1, 7 };
//char *server = "hermes-nefele.rhcloud.com";
char *mac;				//wifly mac address
char channel[30];		//topic to subscribe to (s + mac)

/**************************************************** 
 * MQTT settings
 *
 ****************************************************/
WiFlyClient wiFlyClient;
PubSubClient client(server, MQTT_PORT, callback, wiFlyClient);

#endif