


// LINK REQUIRED LIBRARY //
#include <Servo.h>        // Link to servo library
#include<SoftwareSerial.h>
SoftwareSerial BT(3, 4); //TX, RX respetively

// PIN SETUP //

const byte lServoPin    =   10;   // Servo pin for left legs
const byte rServoPin    =  9;   // Servo pin for right legs
const byte cServoPin    =  11;   // Servo pin for center legs
const byte whiteLED     =  13;   // Pin for onboard white LED
String response;

// CREATE INSTANCES OF SERVO OBJECTS //
Servo leftLegs;
Servo rightLegs;
Servo centerLegs;

// SERVO VARIABLES //
byte lServoAngle         =  90;  // Angle of left leg servo (
const byte lServoMIN     =  30;  // Mechanical limits of left leg servo
const byte lServoMAX     = 120;  // Left leg servo range (40-130, 90 degrees)

byte rServoAngle         =  90;  // Angle of right leg servo
const byte rServoMIN     =  30;  // Mechanical limits of right leg servo
const byte rServoMAX     = 120;  // Right leg servo range (30-120, 90 degrees)

byte cServoAngle         =  90;  // Angle of center leg servo
const byte cServoMIN     =  30;  // Mechanical limits of center leg servo 50
const byte cServoMAX     =  120;  // Center leg servo range (60-80, 20 degrees) 80


// STATE MACHINE VARIABLES //
 byte forwardState;
 byte reverseState;
 byte leftState;
 byte rightState;
 byte doNothing;

boolean stepPhase        =   0;  // Flag indicating which half of step cycle we are in
const byte servoDelay    =  10;  // Set delay (in milliseconds) between servo positions
const byte servoSpeed    =   4;  // Distance in degrees that servos will move in each program loop
byte state, oldState     =   0;  // Stores current/previous mode value

const byte dwellDuration =   6;  // Number of half steps robot will stay in turn/back-up mode
byte dwellTimer          =   0;  // Keeps track of number of "ticks" remaining in a "dwell" state
byte dwellTotalTicks     =   ((lServoMAX - lServoMIN) / servoSpeed) * dwellDuration;  // Number of "frames" in a complete step * number of steps to dwell


// PROGRAM SETUP //
void setup(){
  Serial.begin(9600);
  BT.begin(9600);
  leftLegs.attach(lServoPin);    // Attach servos to pins
  rightLegs.attach(rServoPin);
  centerLegs.attach(cServoPin);
}


// PROGRAM MAIN LOOP //
void loop(){
   serialRead();
  switch(state){               // Determine which mode we are currently in
    case 1:
      moveForward();           // Call the function to walk forward
    break;
    case 2:
      moveReverse();           // Call the function to walk backward
    break;
    case 3:
      moveTurnLeft();          // Call the function to turn left
    break;
    case 4:
      moveTurnRight();         // Call the function to turn right
    break;
    case 5:
        Stop();
       
      break;
  }  
}

void serialRead(){
  while (BT.available())
    {
      char c = BT.read();
      response += c;
       if(response.length()>0){
    Serial.println(response);
  
    if(response == "w"){
      state = 1;
      
    }
    else if( response == "b"){
     state = 2;
    }
    else if(response == "l"){
      state = 3;
      
    }
    else if(response == "r"){
      state = 4;
    }
    else if(response == "s"){
      state = 5;
    }
    
} 
response ="";
    }
}







void moveForward(){                        // Servo routine for walking forward (Exactly the same as "moveBackward" except center leg position is inverted)
  Serial.println("fwd");
  if (!stepPhase){                         // First half of step cycle (Left leg extend, right leg retract)
    cServoAngle = cServoMIN;               // Set position of center legs for this half of the cycle
    if (lServoAngle < lServoMAX){          // Make sure legs aren't at their limit
      lServoAngle += servoSpeed;           // Move legs "servoSpeed" degrees once per loop
      rServoAngle += servoSpeed;
    }else {
      lServoAngle = lServoMAX;             // If a leg is at its limit, toggle stepPhase to run second half of step cycle
      rServoAngle = rServoMAX;
      stepPhase = !stepPhase;
    }
    centerLegs.write(cServoAngle);         // Write new positions to servos
    leftLegs.write(lServoAngle);
    rightLegs.write(rServoAngle);
  }else {                                  // Second half of step cycle (Left leg retract, right leg extend)
    cServoAngle = cServoMAX;               // Set position of center legs for this half of the cycle
    if (lServoAngle > lServoMIN){
      lServoAngle -= servoSpeed;           // Move legs "servoSpeed" degrees once per loop
      rServoAngle -= servoSpeed;
    }else {
      lServoAngle = lServoMIN;             // If a leg is at its limit, toggle stepPhase to run first half of step cycle
      rServoAngle = rServoMIN;
      stepPhase = !stepPhase;  
    }
    centerLegs.write(cServoAngle);
    leftLegs.write(lServoAngle);           // Write new positions to servos
    rightLegs.write(rServoAngle);
  }
  delay(servoDelay);                       // Wait so movement is slowed and smooth
}


void moveReverse(){                        // Servo routine for walking backward (Exactly the same as "moveForward" except center leg position is inverted)
  Serial.println("bck");
  dwellTimer = dwellTotalTicks;            // Set a timer to help the robot from getting stuck at the edge of its' sensor range
  while(dwellTimer){                       // Lock state inside loop so it can't be interupted until "dwellTimer" runs out
    if (stepPhase){                        // First half of step cycle (Left leg extend, right leg retract)
      cServoAngle = cServoMAX;             // Set position of center legs for this cycle
      if (lServoAngle < lServoMAX){
        lServoAngle += servoSpeed;         // Move legs "servoSpeed" degrees once per loop
        rServoAngle += servoSpeed;
      }else {
        lServoAngle = lServoMAX;           // If a leg is at its limit, toggle stepPhase to run second half of step cycle
        rServoAngle = rServoMAX;
        stepPhase = !stepPhase;
      }
      centerLegs.write(cServoAngle);       // Write new positions to servos
      leftLegs.write(lServoAngle);
      rightLegs.write(rServoAngle);
    }else {                                // Second half of step cycle (Left leg retract, right leg extend)
      cServoAngle = cServoMIN;             // Set position of center legs for this cycle
      if (lServoAngle > lServoMIN){
        lServoAngle -= servoSpeed;         // Move leg "servoSpeed" degrees once per loop
        rServoAngle -= servoSpeed;
      }else {
        lServoAngle = lServoMIN;           // If a leg is at its limit, toggle stepPhase to run first half of step cycle
        cServoAngle = cServoMIN;
        stepPhase = !stepPhase;
      }
      centerLegs.write(cServoAngle);       // Write new positions to servos
      leftLegs.write(lServoAngle);
      rightLegs.write(rServoAngle);
    }
    delay(servoDelay);                     // Wait so movement is slowed and smooth
    dwellTimer--;                          // Subtract from "dwellTimer" and start "while()" loop again
  }
}


void moveTurnLeft(){                       // Servo routine for turning left (Exactly the same as moveTurnRight except center leg position is inverted)
  Serial.println("left");
  dwellTimer = dwellTotalTicks;            // Set a timer to help the robot from getting stuck at the edge of its' sensor range
  while(dwellTimer){                       // Lock state inside loop so it can't be interupted until "dwellTimer" runs out
    if (stepPhase){                        // First half of step cycle (Left leg extend, right leg extend)
      cServoAngle = cServoMAX;             // Set position of center legs for this cycle
      if (lServoAngle < lServoMAX){
        lServoAngle += servoSpeed;         // Move legs "servoSpeed" degrees once per loop
        rServoAngle -= servoSpeed;
      }else {
        lServoAngle = lServoMAX;           // If a leg is at its limit, toggle stepPhase to run second half of step cycle
        rServoAngle = rServoMIN;
        stepPhase = !stepPhase;
      }
      centerLegs.write(cServoAngle);
      leftLegs.write(lServoAngle);         // Write new positions to servos
      rightLegs.write(rServoAngle);
    }else {                                // Second half of step cycle (Left leg retract, right leg retract)
      cServoAngle = cServoMIN;             // Set position of center legs for this cycle
      if (lServoAngle > lServoMIN){
        lServoAngle -= servoSpeed;         // Move leg "servoSpeed" degrees once each program loop
        rServoAngle += servoSpeed;
      }else {
        lServoAngle = lServoMIN;           // If a leg is at its limit, toggle stepPhase to run first half of step cycle
        rServoAngle = rServoMAX;
        stepPhase = !stepPhase;  
      }
      centerLegs.write(cServoAngle);       // Write new positions to servos
      leftLegs.write(lServoAngle);
      rightLegs.write(rServoAngle);
    }
    delay(servoDelay);                     // Wait so movement is slowed and smooth
    dwellTimer--;                          // Subtract from "dwellTimer" and start "while()" loop again
  }
}


void moveTurnRight(){                      // Servo routine for turning right (Exactly the same as moveTurnLeft except center leg position is inverted)
  Serial.println("right");
  dwellTimer = dwellTotalTicks;            // Set a timer to help the robot from getting stuck at the edge of its' sensor range
  while(dwellTimer){                       // Lock state inside loop so it can't be interupted until "dwellTimer" runs out
    if (!stepPhase){                       // First half of step cycle (Left leg extend, right leg extend)
      cServoAngle = cServoMIN;             // Set position of center legs for this cycle
      if (lServoAngle < lServoMAX){
        lServoAngle += servoSpeed;         // Move legs "servoSpeed" degrees once per loop
        rServoAngle -= servoSpeed;
      }else {
        lServoAngle = lServoMAX;           // If a leg is at its limit, toggle stepPhase to run second half of step cycle
        rServoAngle = rServoMIN;
        stepPhase = !stepPhase;
      }
      centerLegs.write(cServoAngle);
      leftLegs.write(lServoAngle);         // Write new positions to servos
      rightLegs.write(rServoAngle);
    }else {                                // Second half of step cycle (Left leg retract, right leg retract)
      cServoAngle = cServoMAX;             // Set position of center legs for this cycle
      if (lServoAngle > lServoMIN){
        lServoAngle -= servoSpeed;         // Move leg "servoSpeed" degrees once each program loop
        rServoAngle += servoSpeed;
      }else {
        lServoAngle = lServoMIN;           // If a leg is at its limit, toggle stepPhase to run first half of step cycle
        rServoAngle = rServoMAX;
        stepPhase = !stepPhase;   
      }
      centerLegs.write(cServoAngle);       // Write new positions to servos
      leftLegs.write(lServoAngle);
      rightLegs.write(rServoAngle);
    }
    delay(servoDelay);                     // Wait so movement is slowed and smooth
    dwellTimer--;                          // Subtract from "dwellTimer" and start "while()" loop again
  }
}


void Stop(){
  byte lServoAngle         =  90;  // Angle of left leg servo (


byte rServoAngle         =  90;  // Angle of right leg servo


byte cServoAngle         =  90;  // Angle of center leg servo
leftLegs.write(lServoAngle);
      rightLegs.write(rServoAngle);
      centerLegs.write(cServoAngle);
Serial.println("Stop");
}

