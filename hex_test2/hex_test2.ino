#include<Servo.h>
Servo servoFrontLeft;
Servo baseServoFrontLeft;
Servo invbaseservoright;
int pos = 90;
int basepos=90;
int invpos=90;
int Servopins[6]={3,5,6,9,10,11};

void setup() {
  // put your setup code here, to run once:
  int i;
servoFrontLeft.attach(Servopins[5]);
baseServoFrontLeft.attach(Servopins[0]);//base
servoFrontLeft.write(pos);
baseServoFrontLeft.write(pos);
invbaseservoright.attach(Servopins[1]);
invbaseservoright.write(invpos);
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
  for(pos =90;pos<=150;pos++){
    servoFrontLeft.write(pos);
    delay(15);
  }
  for(basepos = 90,invpos=90 ; basepos<=150,invpos>=20;basepos++,invpos--){
    baseServoFrontLeft.write(basepos);
    invbaseservoright.write(invpos);
    delay(15);
  }

  for(pos =150;pos>=90;pos--){
    servoFrontLeft.write(pos);
    delay(15);
  }

  for(basepos = 150,invpos=20 ; basepos>=90,invpos<=90;basepos--,invpos++){
    baseServoFrontLeft.write(basepos);
    invbaseservoright.write(invpos);
    delay(15);
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
