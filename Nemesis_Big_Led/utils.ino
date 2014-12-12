/** Connect to a websocket server.
 */
bool connect(const char *hostname, const char *path, uint16_t port)
{
    if (!wifly.open(hostname, port)) {
        Serial.println(F("connect: failed to open TCP connection"));
	return false;
    }

    wifly.print(F("GET "));
    wifly.print(path);
    wifly.println(F(" HTTP/1.1"));
    wifly.print(F("Host: "));
    wifly.println(hostname);
    wifly.println(F("Upgrade: websocket"));
    wifly.println(F("Connection: Upgrade"));
    wifly.println(F("Sec-WebSocket-Key:/b1L5mR7Rp7gYgxo5+R6UQ=="));
    wifly.println(F("Origin: http://kayak.com"));
    wifly.println(F("Sec-WebSocket-Protocol: chat, superchat"));
    wifly.println(F("Sec-WebSocket-Version:13"));
    wifly.println();

    /* Wait for the handshake response */
    if (wifly.match(F("HTTP/1.1 101"), 2000)) {
	wifly.flushRx(200);
	return true;
    }

    Serial.println(F("connect: handshake failed"));
    wifly.close();

    return false;
}

void messageToOutputs( char *strOutputs ){
 
  int size = strlen(strOutputs);
  int i = 0;
  
  char *result = NULL;
  result = strtok( strOutputs, "B" );

  while( result != NULL ) {
    ht1632_send_data(i,(byte)atoi(result));
    result = strtok( NULL, "B" );    
    i += 2;
  }
  
}


int processMessage(){
  
    int len = 0; 
    char _aux;
    
    if (wifly.available() > 0) {
      
      _aux = (char) wifly.read();
      
      if(_aux == '>' && inPacket){
	Serial.print("Recibido: ");
        Serial.println(inBuf);
        messageToOutputs(inBuf);
        inPacket = false;
        memset(inBuf, 0, 128);
        inBufInd = 0;
      }
      
      if(inPacket){
        inBuf[inBufInd] = _aux;
        inBufInd++; 
      }
      
      if(_aux == '<'){
        inBuf[0] = 0;
        inPacket = true;
      }
              
    }
}

void readTerminal(){
  if (Serial.available()) {
        char ch = Serial.read();
        if (ch == '\r') {
	    /* Got a carriage return, send the message */
	    outBuf[outBufInd] = 0;
	    send(outBuf);
	    outBufInd = 0;
	    Serial.println();
	} else if (outBufInd < (sizeof(outBuf) - 1)) {
	    outBuf[outBufInd] = ch;
	    outBufInd++;
	    Serial.write(ch);
	}
    }
}

/** Send a message to the server */
void send(char *str) {
    int size = strlen(str);

    // string type
    wifly.write(0x81);

    // NOTE: no support for > 16-bit sized messages
    if (size > 125) {
        wifly.write(126);
        wifly.write((uint8_t) (size >> 8));
        wifly.write((uint8_t) (size && 0xFF));
    } else {
        wifly.write((uint8_t) size);
    }

    for (int i=0; i<size; ++i) {
        wifly.write(str[i]);
    }
}

//Full LED print message:
//<255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B>