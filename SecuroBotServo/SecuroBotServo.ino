/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int maxPos = 150;
int midPos = 85;
int minPos = 20;
int initPos = midPos;
int pos = minPos;    // variable to store the servo position 
int relayPin = 7;

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(relayPin, OUTPUT);
  initServo(initPos);
  Serial.begin(9600);
  delay(3000);
  digitalWrite(relayPin, HIGH);
} 
 
void loop() 
{
  if(Serial.available()) {
    int readVal = Serial.read();
    Serial.print("Serial Value Read: ");
    Serial.println(readVal);
    switch(readVal) {
      case 1: 
          moveServo(minPos);
          break;
      case 2: 
          moveServo(midPos);
          break;
      case 3: 
          moveServo(maxPos);
          break;
      default: 
          //moveServo(midPos);
          break;
    }
  }
} 

void moveServo(int newPos) {
  if(newPos>pos) {  //fwd
    for(; pos <= newPos; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    delay(500);
  }
  else if(newPos<pos) { //rev
    for(; pos >= newPos; pos -= 1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    delay(500);
  }
  serialResponse();
}

void initServo(int start) {
  myservo.write(start);
  delay(1500);
}

void serialResponse() {
  Serial.write(0x01);
}

