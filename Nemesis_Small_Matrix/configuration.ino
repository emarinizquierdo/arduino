void configuration(){
  Serial.begin(115200);
    wifiSerial.begin(9600);

    for(int i = OUTPUTS_OFFSET; i <= 13; i++){
      pinMode(i, OUTPUT);
      //digitalWrite(i,LOW);
    }
    
    if (!wifly.begin(&wifiSerial, &Serial)) {
        Serial.println(F("Failed to start wifly"));
	wifly.terminal();
    }

    /* Join wifi network if not already associated */
    if (!wifly.isAssociated()) {
	Serial.println(F("Joining network"));
	if (wifly.join(mySSID, myPassword, true, WPA_WEP_MODE, 10000)) {
	    wifly.save();
	    Serial.println(F("Joined wifi network"));
	} else {
	    Serial.println(F("Failed to join wifi network"));
	    wifly.terminal();
	}
    } else {
        Serial.println(F("Already joined network"));
    }

    if (!connect(server)) {
	Serial.print(F("Failed to connect to "));
	Serial.println(server);
	wifly.terminal();
    }else{
        Serial.print("Connected to ");
        Serial.println(server);
    }

}
