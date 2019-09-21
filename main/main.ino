#include <Servo.h>
#include <Stepper.h>

#include <SoftwareSerial.h>
const int stepsPerRevolution = 520; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Servo heightServo;  // create servo object to control a servo
Servo distanceServoLeft; // servo to control bar moving back and forth
Servo distanceServoRight;
Servo clawServo;

SoftwareSerial mySerial(12, 13); // RX, TX  

int clawPos = 0;
int heightPos = 0; 
int distancePos = 0; 

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
  int h = height;
  heightServo.write(h);
  heightPos = h;
}

void setDistance(int distance) {
  int d = distance;
  distanceServoLeft.write(d);
  distanceServoRight.write(180-d);
  distancePos = d;
}

void setClaw(int pos) {
  for (int i = clawPos; i < pos; i++) {
    clawServo.write(i);
    delay(100);
  }
  
  clawPos = pos;
  
}

void setup() { 
  Serial.begin(9600);
  mySerial.begin(9600);
  myStepper.setSpeed(12);
  heightServo.attach(7);
  heightServo.write(0);
  distanceServoLeft.attach(6);
  distanceServoLeft.write(0);
  distanceServoRight.attach(5);
  distanceServoRight.write(180);
  clawServo.attach(4);
  clawServo.write(0);
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
      case 3:
      Serial.println("Changing Distance");
      if (mySerial.available()) {
        int distance = mySerial.read();
        Serial.println(distance);
        setDistance(distance);
      }
      case 4:
      Serial.println("Changing Claw");
      if (mySerial.available()) {
        int clawPos = mySerial.read();
        Serial.println(clawPos);
        setClaw(clawPos);
      }
      break;
      case 5:
      Serial.println("Step close Claw");
      setClaw(clawPos + 5);
      break;
      case 6:
      Serial.print("Step increase distance");
      setDistance(distancePos + 15);
      break;
      case 7: 
      Serial.print("Step decrease distance");
      setDistance(distancePos - 15);
      break;
      case 8: 
      Serial.print("Step increase Height");
      setHeight(heightPos + 10);
      break;
      case 9:
      Serial.print("Step decrease Height");
      setHeight(heightPos - 10);
      break;
    }
  }
}
