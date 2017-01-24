#include <Servo.h>
#include <SPI.h>

Servo s1;

// set joystick pin numbers:
const int joystickSel = 5;     // the number of the joystick select pin
const int joystickX = 2;       // the number of the joystick X-axis analog
const int joystickY =  26;     // the number of the joystick Y-axis analog

const int joystickOffsetPos = 15;
const int joystickOffsetNeg = -15;
int joystickXState, joystickYState; 

int ledPin = 39;
int buttonPin = 32;
int servoValue = 0;
int deltaServo = 0;
char userInput;
bool autoPilot;

void setup() {
  autoPilot = false;
  Serial.begin(9600);
  while(!Serial);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  s1.attach(19);
}

void loop() {
  joystickXState = analogRead(joystickX);
  joystickXState = map(joystickXState, 0, 1024, -100, 100);

  digitalWrite(ledPin, autoPilot);
  
  //Serial.println(joystickXState);
  if(joystickXState > joystickOffsetPos){
    //digitalWrite(ledPin, HIGH);
    autoPilot = false;
    deltaServo = -2;
  }
  else if(joystickXState < joystickOffsetNeg) {
    autoPilot = false;
    //digitalWrite(ledPin, HIGH);
    deltaServo = 2;
  } else {
    //Wait for servo value
    //digitalWrite(ledPin, LOW);
    if(autoPilot) {
      if(Serial.available() > 0) {
        userInput = Serial.read();
      } 
      else {
        userInput = 'c';
      }
  
      Serial.print("User Input: ");
      Serial.println(userInput);
  
      switch(userInput) {
        case 'r': deltaServo = -3;
        break;
        case 'l': deltaServo = 3;
        break;
        case 'R': deltaServo = -5;
        break;
        case 'L': deltaServo = 5;
        break;
        default:  deltaServo = 0;
      }
    } else {
      while(Serial.available() > 0) 
        char t = Serial.read();
      deltaServo = 0;
    }

    if(digitalRead(buttonPin) == LOW) autoPilot = true;
  }

  Serial.print("Delta servo: ");
  Serial.println(deltaServo);
  
  //Adjust servo value
  servoValue += deltaServo;
  if(servoValue > 180)
    servoValue = 180;
  else if(servoValue < 0)
    servoValue = 0;

  //Set servo value
  //Serial.print("Servo go to position ");
  //Serial.println(servoValue);
  s1.write(servoValue);  
  
  /*
  //while(Serial.available() > 0) 
  //  char t = Serial.read();
  
  while(Serial.available() == 0);
  userInput = Serial.read();

  switch(userInput) {
    case 'r': deltaServo = -10;
    break;
    case 'l': deltaServo = 10;
    break;
    default:  deltaServo = 0;
  }
  
  servoValue += deltaServo;
  if(servoValue > 180)
    servoValue = 180;
  else if(servoValue < 0)
    servoValue = 0;

  Serial.print("Servo go to position ");
  Serial.println(servoValue);
  s1.write(servoValue);  
  */

  delay(3);
}


