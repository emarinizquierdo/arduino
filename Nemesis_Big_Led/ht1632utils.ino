void ht1632_send_bits (byte bits, byte firstbit)
{
  while (firstbit) {
    digitalWrite(ht1632_wrclk, LOW);
    if (bits & firstbit) digitalWrite(ht1632_data, HIGH);
    else digitalWrite(ht1632_data, LOW);
    digitalWrite(ht1632_wrclk, HIGH);
    firstbit >>= 1;
  }
}

static void ht1632_sendcmd (byte command)
{
  // select display
  digitalWrite(ht1632_cs, LOW);   
  ht1632_send_bits(HT1632_ID_CMD, 1<<2);  // send 3 bits of id: COMMMAND
  ht1632_send_bits(command, 1<<7);  // send the actual command
  ht1632_send_bits(0, 1); 	/* one extra dont-care bit in commands. */
  // unselect display
  digitalWrite(ht1632_cs, HIGH);
}

static void ht1632_send_data (byte address, byte data)
{
  // select display
  digitalWrite(ht1632_cs, LOW); 
  ht1632_send_bits(HT1632_ID_WR, 1<<2);  // send ID: WRITE to RAM
  ht1632_send_bits(address, 1<<6); // Send address
  ht1632_send_bits(data, 1<<7); // send 4 bits of data
  // unselect display
  digitalWrite(ht1632_cs, HIGH); 
}

void ht1632_clear()
{
  char i;
  // select display
  digitalWrite(ht1632_cs, LOW); 
  ht1632_send_bits(HT1632_ID_WR, 1<<2);  // send ID: WRITE to RAM
  ht1632_send_bits(0, 1<<6); // Send address
  for (i=0; i<32; i++) // Clear entire display
    ht1632_send_bits(0, 1<<7); // send 8 bits of data
  // unselect display
  digitalWrite(ht1632_cs, HIGH); 
}

static void ht1632_initialize()
{
  pinMode(ht1632_cs, OUTPUT);
  pinMode(ht1632_wrclk, OUTPUT);
  pinMode(ht1632_data, OUTPUT);

  ht1632_sendcmd(HT1632_CMD_SYSON);  // System on
  ht1632_sendcmd(HT1632_CMD_LEDON);  // LEDs on 

   // select display
  digitalWrite(ht1632_cs, LOW);
  digitalWrite(ht1632_vcc, HIGH);
}
