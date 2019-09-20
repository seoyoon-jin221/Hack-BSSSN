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
    if (c == 0)
    {
      int angle = mySerial.read();
      stepperRotateClock(angle);
      Serial.println("Rotating clockwise: " + angle);
    } else if (c == 1) {
      int angle = mySerial.read();
      stepperRotateAnti(angle);
      Serial.println("Rotating clockwise: " + angle);
    }

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
    /*if(c==1)
      stepperRotateClock(1);
     */
     switch (c) {
      //move clockwise case
        case 1:
          stepperRotateClock(1);
          break;
        case 2:
          stepperRotateClock(2);
          break;
          case 3:
          stepperRotateClock(4);
          break;
          case 4:
          stepperRotateClock(8);
          break;
          case 5:
          stepperRotateClock(16);
          break;
          case 6:
          stepperRotateClock(32);
          break;
          case 7:
          stepperRotateClock(64);
          break;
          case 8:
          stepperRotateClock(128);
          break;
       //move counter-clockwise case   
          case 9:
          stepperRotateAnti(1);
          break;
          case 10:
          stepperRotateAnti(2);
          break;
          case 11:
          stepperRotateAnti(4);
          break;
          case 12:
          stepperRotateAnti(8);
          break;
          case 13:
          stepperRotateAnti(16);
          break;
          case 14:
          stepperRotateAnti(32);
          break;
          case 15:
          stepperRotateAnti(64);
          break;
          case 16:
          stepperRotateAnti(128);
          break;
          
        default:
          break;
} 
      

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
