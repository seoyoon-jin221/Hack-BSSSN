#include <Servo.h>
#include <Stepper.h>

#include <SoftwareSerial.h>
const int stepsPerRevolution = 520; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
//Servo myservo;  // create servo object to control a servo

SoftwareSerial mySerial(12, 13); // RX, TX  

void stepperRotateClock(int angle) { 
  Serial.println("rotating");
  int s = map(angle,0,360,0,520);  
  myStepper.step(s);
  delay(500);
}

void stepperRotateAnti(int angle) {
  Serial.println("anticlock");
  int s = map(angle, 0, 360, 0, 520);
  myStepper.step(-s);
  delay(500);
}

void setup() { 
  myStepper.setSpeed(12);
  Serial.begin(9600);
  mySerial.begin(9600);
 // myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {  
  int c;

  //val = myservo.read(); //current servo position
         
 
  if (mySerial.available()) {
    c = mySerial.read();  
    Serial.println("Got input: ");
    Serial.println(c);
    if (c == 0)
    {
      Serial.println("waiting for another bit");
      if (mySerial.available()) {
        Serial.println("another bit loaded");
        int angle = mySerial.read();
        Serial.println(angle);
        stepperRotateClock(angle);
      }
    } else if (c == 1) {
      Serial.println("waiting for another bit");
      if (mySerial.available()) {
        Serial.println("another bit loaded");
        int angle = mySerial.read();
        Serial.println(angle);
        stepperRotateAnti(angle);
      }
    }
  }
}
