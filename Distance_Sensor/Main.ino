#include <Arduino.h>

#define vcc 2
#define gnd 5
#define trigPin 3
#define echoPin 4


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(vcc, OUTPUT);
  pinMode(gnd, OUTPUT);

  digitalWrite(vcc, HIGH);
  digitalWrite(gnd, LOW); 
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {  // This is where the LED On/Off happens
    //digitalWrite(pin1,HIGH); // When the Red condition is met, the Green LED should turn off
    
}
  else {
    //digitalWrite(pin1,LOW);
    //digitalWrite(led,LOW);
    //digitalWrite(led2,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.write(distance);
  }
  else {
    Serial.write(distance);
    //Serial.println(" cm");
  }
  delay(500);
}