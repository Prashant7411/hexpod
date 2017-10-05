#include<Servo.h>
Servo servoFrontLeft;
Servo baseServoFrontLeft;
Servo invbaseservoright;
Servo baseServoRight;
Servo invBaseServoLeft;
Servo servoFrontRight;
int pos = 90; //side servo 1,3,5
int basepos=90; //base servo 1,3
int invpos=90; //base servo 5
int baseposright=90; //base servo 4,5
int sideposright=90; //side servo 4,5,2
int invRightBase=90; //base servo 2 
int Servopins[6]={3,5,6,9,10,11};

void setup() {
  // put your setup code here, to run once:
  int i;
servoFrontLeft.attach(Servopins[5]);//side 1,3,5 pin 11
baseServoFrontLeft.attach(Servopins[0]);//base 1,3 pin 3
servoFrontLeft.write(pos);
baseServoFrontLeft.write(pos);
invbaseservoright.attach(Servopins[1]);//base 5 pin 5
invbaseservoright.write(invpos);
baseServoRight.attach(Servopins[2]); //base servo 4,6 pin 6
baseServoRight.write(pos);
invBaseServoLeft.attach(Servopins[3]); //base servo 2 pin 9
invBaseServoLeft.write(invpos);
servoFrontRight.attach(Servopins[4]); //side servo 2,4,6 pin 10
servoFrontRight.write(sideposright);
delay(2000);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String response;
  while (Serial.available())
    {
      char c = Serial.read();
      response += c;
      
    }
  if(response.length()>0){
    Serial.println(response);
  
    if(response == "a"){
      fwd();
    }
    else if( response == "b"){
      servoFrontLeft.write(pos);
baseServoFrontLeft.write(pos);
    }
    else if(response == "c"){
      bck();
    }
    
  
   response ="";
  delay(1000);
    
  
  }
}


void fwd(){
  for(pos =90;pos<=150;pos++){ //lift side servo 1,3,5
    servoFrontLeft.write(pos);
    delay(15);
  }
  for(basepos = 90,invpos=90 ; basepos<=150,invpos>=20;basepos++,invpos--){ //move base servo 1,3,5 forward
    baseServoFrontLeft.write(basepos);
    invbaseservoright.write(invpos);
    delay(15);
  }

  for(pos =150;pos>=90;pos--){ //down side servo 1,3,5
    servoFrontLeft.write(pos);
    delay(15);
  }

  for(basepos = 150,invpos=20,sideposright=90 ; basepos>=90,invpos<=90, sideposright<=150;basepos--,invpos++,sideposright++){ //move base servo 1,3,5 back(sweep), lift side servo 2,4,6
    baseServoFrontLeft.write(basepos);
    invbaseservoright.write(invpos);
    servoFrontRight.write(sideposright);
    delay(15);
  }

  for(baseposright=90,invRightBase=90;baseposright<=150,invRightBase>=20;baseposright++,invRightBase--){ //move base servo 2,4,6 forward
    baseServoRight.write(baseposright);
    invBaseServoLeft.write(invRightBase);
  }

  for(sideposright==150;sideposright>=90;sideposright--){ //down side servo 2,4,6
    
    servoFrontRight.write(sideposright);
  }

  for(baseposright=150,invRightBase=20;baseposright>=90,invRightBase<=90;baseposright--,invRightBase++){ //move base servo 2,4,6 back(sweep)
    baseServoRight.write(baseposright);
    invBaseServoLeft.write(invRightBase);
  }
}


void bck(){
  for(pos =90;pos<=150;pos++){
    servoFrontLeft.write(pos);
    delay(15);
  }
  for(basepos = 90,invpos=90 ; basepos>=20,invpos<=150;basepos--,invpos++){
    baseServoFrontLeft.write(basepos);
    invbaseservoright.write(invpos);
    delay(15);
  }

  for(pos =150;pos>=90;pos--){
    servoFrontLeft.write(pos);
    delay(15);
  }

  for(basepos = 20,invpos=150 ; basepos<=90,invpos>=90;basepos++,invpos--){
    baseServoFrontLeft.write(basepos);
    invbaseservoright.write(invpos);
    delay(15);
  }
}
