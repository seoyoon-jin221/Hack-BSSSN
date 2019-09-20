#include <Servo.h>
#include <Stepper.h>

#include <SoftwareSerial.h>
const int stepsPerRevolution = 520; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Servo heightServo;  // create servo object to control a servo

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

void setHeight(int height) {
  Serial.println("Changing Height");
  int h = map(height, 0, 90, 0, 180);
  heightServo.write(h);
}

void setup() { 
  Serial.begin(9600);
  mySerial.begin(9600);
  myStepper.setSpeed(12);
  heightServo.attach(7);
  heightServo.write(0);
}

void loop() {  
  int c;

  //val = myservo.read(); //current servo position
         
 
  if (mySerial.available()) {
    c = mySerial.read();  
    Serial.println("Got input: ");
    Serial.println(c);
    switch (c) {
      case 0:
      Serial.println("Rotate Clockwise");
      if (mySerial.available()) {
        int angle = mySerial.read();
        Serial.println(angle);
        stepperRotateClock(angle);
      }
      break;
      case 1:
      Serial.println("Rotate Anti Clockwise");
      if (mySerial.available()) {
        int angle = mySerial.read();
        Serial.println(angle);
        stepperRotateAnti(angle);
      }
      break;
      case 2: 
      Serial.println("Changing Height");
      if (mySerial.available()) {
        int height = mySerial.read();
        Serial.println(height);
        setHeight(height);
      }
      break;
    }
  }
}
