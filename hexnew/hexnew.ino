#include <Servo.h>

Servo lservo;
Servo rservo;
Servo cservo;

void setup(){
  lservo.attach(9);
  lservo.write(90);
  rservo.attach(10);
  rservo.write(90);
  cservo.attach(11);
  cservo.write(90);
}

void loop(){
 cservo.write(60);
  delay(200);
  lservo.write(40);
  delay(200);
  cservo.write(90);
  delay(200);
  lservo.write(90);
  delay(200);

    cservo.write(120);
  delay(200);
  rservo.write(140);
  delay(200);
  cservo.write(90);
  delay(200);
  rservo.write(90);
  delay(200);
}

