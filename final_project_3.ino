#include <Servo.h>
Servo servo1; //add servo
const int trigPin = 9; //define pins for the distance sensor
const int echoPin = 10; //define pins for the distance sensor
long duration; //part of the distance sensor code
int distanceCm, distanceInch; //create integers for the distance
void setup() {
   servo1.attach(8); //set servo pin
   pinMode(trigPin, OUTPUT); //make the trig pin an output
   pinMode(echoPin, INPUT); //make echo pin input
   Serial.begin(9600); //begin serial communication
}

void loop() {
  int i = 0;
  int o = isOpen();
  while(o == 0) {
    i++;
    if (i % 2 == 0) { Serial.print("door is "); Serial.println(isOpen() == 1 ? "open" : "closed"); }
    delay(500); //pause for .5 seconds
   o = isOpen();
  }
  Serial.println("door is now open");
  delay(500); //pause for .5 seconds
  
  o = isOpen();
  while(o == 1) {
    i++;
    if (i % 2 == 0) { Serial.print("door is "); Serial.println(isOpen() == 1 ? "open" : "closed"); }
    delay(500); //pause for .5 seconds
    o = isOpen();
  }
  Serial.println("door is now closed");
  delay(1500); //pause for 1.5 seconds

  Serial.println("locking door");
  lockDoor();

  Serial.println("waiting for some time...");
  long startTimeMillis = millis();
  while (millis() - startTimeMillis < 10000) {
    i++;
    if (i % 2 == 0) { Serial.print("door is "); Serial.println(isOpen() == 1 ? "open" : "closed"); }
    delay(500); //pause for .5 seconds
  }

  Serial.println("unlocking door");
  unlockDoor();
}

void lockDoor() {
  servo1.write(0); //turn servo all the way one way
}

void unlockDoor() {
  servo1.write(180); //turn servo all the way the other way
}

int isOpen() {
  int distance = getDistance(); //set the integer distance to the distance found by the sensor
  if (distance > 30) return 1; //if the distance is more than 30 cm, return 1. Otherwise
  return 0; //return 0
}

int getDistance() {  //all after this line is the distance sensor's code
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;
return distanceCm;
}
