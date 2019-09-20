/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <Stepper.h>

#include <SoftwareSerial.h>
#define SERVO_PIN 9
const int stepsPerRevolution = 520; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Servo myservo;  // create servo object to control a servo


int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

SoftwareSerial mySerial(7, 8); // RX, TX  

void setup() { 
  
  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {  
  int c;
  val = myservo.read(); //current servo position
         
 
  if (mySerial.available()) {
    c = mySerial.read();  
    Serial.println("Got input:");
    /*
    if (c == 1)
    {
      // Non-zero input means "increse angle".
      val = val + 5;
      Serial.println("  increase angle");
      myservo.write(val);// sets the servo position according to the scaled value
    }
    else if (c == 0)
    {
      // Input value zero means "decrease angle".
      val = val-5;
      Serial.println("decrease angle");
      myservo.write(val);// sets the servo position according to the scaled value
    }
    else if ( c == 2 )
      Serial.println("keep still");
      */
    if(c==1)
      stepperRotateClock(1);
      

  }
  //Serial.println(myservo.read()); 
  
  //delay(10);      // waits for the servo to get there
 
}

void stepperRotateClock(int angle) { 
  int step = map(angle,0,180,0,520);  
}

void stepperRotateAnti(int angle) {
  int step = map(angle, 0, 180, 0, 520);
}
}
