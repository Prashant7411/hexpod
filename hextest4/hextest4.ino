#include<Servo.h>
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
servo.write(90);
servo1.write(90);
servo2.write(90);
servo3.write(90);
servo4.write(90);
servo5.write(90);
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

servo1.write(130);
delay(250);
servo.write(50);
servo2.write(130);
delay(150);
servo1.write(70);
delay(250);
servo.write(90);
servo2.write(90);
delay(250);


servo3.write(50);
delay(250);
servo4.write(130);
servo5.write(50);
delay(250);
servo3.write(90);
delay(250);
servo4.write(90);
servo5.write(90);
delay(250);
}
