#include<Servo.h>
Servo servoFrontLeft;
Servo baseServoFrontLeft;
int pos = 90;
int basepos=90;

void setup() {
  // put your setup code here, to run once:
servoFrontLeft.attach(9);
baseServoFrontLeft.attach(10);
servoFrontLeft.write(pos);
baseServoFrontLeft.write(pos);
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
  for(basepos = 90 ; basepos<=150;basepos++){
    baseServoFrontLeft.write(basepos);
    delay(15);
  }

  for(pos =150;pos>=90;pos--){
    servoFrontLeft.write(pos);
    delay(15);
  }

  for(basepos = 150 ; basepos>=90;basepos--){
    baseServoFrontLeft.write(basepos);
    delay(15);
  }
}


void bck(){
  for(pos =90;pos<=150;pos++){
    servoFrontLeft.write(pos);
    delay(15);
  }
  for(basepos = 90 ; basepos>=20;basepos--){
    baseServoFrontLeft.write(basepos);
    delay(15);
  }

  for(pos =150;pos>=90;pos--){
    servoFrontLeft.write(pos);
    delay(15);
  }

  for(basepos = 20 ; basepos<=90;basepos++){
    baseServoFrontLeft.write(basepos);
    delay(15);
  }
}
