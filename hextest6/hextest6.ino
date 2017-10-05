#include<Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); //TX, RX respetively

Servo servo;//right base
Servo servo1;//right side
Servo servo2;//left middle base

Servo servo3;// left side free
Servo servo4;//left base
Servo servo5;//right middle base
void setup() {
  // put your setup code here, to run once:
servo.attach(9);
servo1.attach(10);
servo2.attach(6);
servo3.attach(5);
servo4.attach(3);
servo5.attach(11);
Serial.begin(9600);
BT.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


  String response;
  while (BT.available())
    {
      char c = BT.read();
      response += c;
      
    }
  if(response.length()>0){
    Serial.println(response);
  
    if(response == "s"){
      Start();
      response ="";
    }
    else if( response == "w"){
      fwd();
    }
    else if(response == "S"){
      Stop();
      response ="";
    }
    else if(response == "r"){
      rev();
    }
    else if(response == "a"){
      right();
    }
    
  
   
  delay(1000);
    
  
  }
}


void fwd(){
  servo1.write(130);
delay(300);
servo.write(50);
servo2.write(130);
delay(300);
servo1.write(90);
delay(300);
servo.write(90);
servo2.write(90);
delay(300);


servo3.write(50);
delay(300);
servo4.write(130);
servo5.write(50);
delay(300);
servo3.write(90);
delay(300);
servo4.write(90);
servo5.write(90);
delay(300);
}

void Stop(){
  servo.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
  delay(300);
  servo1.write(170);
  servo3.write(10);
  delay(250);
}

void Start(){
  servo.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
}

void rev(){
  servo3.write(50);
delay(300);
servo4.write(50);
servo5.write(130);
delay(300);
servo3.write(90);
delay(300);
servo1.write(130);
servo4.write(90);
servo5.write(90);
delay(500);                                                                                                                   
servo1.write(90);
delay(500);  
  
  servo1.write(130);
delay(300);
servo.write(130);
servo2.write(50);
delay(300);
servo1.write(90);
delay(300);
servo.write(90);
servo2.write(90);
delay(300);



}

void right(){
  servo1.write(130);
delay(300);
servo.write(50);
servo2.write(130);
delay(300);
servo1.write(90);
delay(300);
servo3.write(50);
delay(300);
servo4.write(130);
servo5.write(50);
delay(300);
servo3.write(90);
delay(300);
servo4.write(90);
servo5.write(90);
servo.write(90);
servo2.write(90);
delay(300);

}

