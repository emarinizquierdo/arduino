/** Connect to a websocket server.
 */
bool connect(const char *hostname, const char *path, uint16_t port){

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

void messageToOutputs( char strOutputs[255] ){

  Serial.print("el strOutputs es: ");
  Serial.println(strlen(strOutputs));
  Serial.println(strOutputs);

  aJsonObject* _dataJson = aJson.parse((char*) strOutputs);
  aJsonObject* _type = aJson.getObjectItem(_dataJson, "type");
  Serial.print("El tipo es: ");
  Serial.println(_type->valuestring);
  aJsonObject* _message = aJson.getObjectItem(_dataJson, "message");

  unsigned long _icon[8];

  if( strcmp(_type->valuestring, "icon")  == 0 ){
    aJsonObject* _row = aJson.getObjectItem(_dataJson, "row0");
    _icon[0] = atoi(_row->valuestring);
    _row = aJson.getObjectItem(_dataJson, "row1");
    _icon[1] = atoi(_row->valuestring);
    _row = aJson.getObjectItem(_dataJson, "row2");
    _icon[2] = atoi(_row->valuestring);
    _row = aJson.getObjectItem(_dataJson, "row3");
    _icon[3] = atoi(_row->valuestring);
    _row = aJson.getObjectItem(_dataJson, "row4");
    _icon[4] = atoi(_row->valuestring);
    _row = aJson.getObjectItem(_dataJson, "row5");
    _icon[5] = atoi(_row->valuestring);
    _row = aJson.getObjectItem(_dataJson, "row6");
    _icon[6] = atoi(_row->valuestring);
    _row = aJson.getObjectItem(_dataJson, "row7");
    _icon[7] = atoi(_row->valuestring);
    /*
    _icon[1] = atoi(_row1->valuestring);
    _icon[2] = atoi(_row2->valuestring);
    _icon[3] = atoi(_row3->valuestring);
    _icon[4] = atoi(_row4->valuestring);
    _icon[5] = atoi(_row5->valuestring);
    _icon[6] = atoi(_row6->valuestring);
    _icon[7] = atoi(_row7->valuestring);
    */

    printRawMessage( _icon );

  }else{
    lc.clearDisplay(0);
    loadBufferLong(0x20);
    scrollMessage((char*)_message->valuestring);
    loadBufferLong(0x20);
  }  

}

int processMessage(){
  
  char _aux;
  
  if (wifly.available() > 0) {
    
    _aux = (char) wifly.read();
    
    if(_aux == '}' && inPacket){
      inBuf[inBufInd]* = _aux;
      Serial.print("Recibido: ");
      inBuf[inBufInd + 1] = '\0';
      Serial.println(inBuf);
      messageToOutputs(inBuf);
      inPacket = false;
      memset(inBuf, 0, sizeof inBuf);
      inBufInd = 0;
      return -1;
    }
    
    if(inPacket == true){
      inBuf[inBufInd] = _aux;
      inBufInd++;      
    }
    
    if(_aux == '{'){
      inBuf[0] = _aux;
      inPacket = true;
      inBufInd++;
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

// Display Buffer on LED matrix
void printRawMessage(unsigned long _data[]){
  
  for (int a=0;a<8;a++){                    // Loop 7 times for a 5x7 font
    unsigned long x = _data [a];   // Get high buffer entry                      // Send row to relevent MAX7219 chip
    lc.setRow(0,a,x);                       // Send row to relevent MAX7219 chip
  }

}

//Full LED print message:
//<255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B255B>