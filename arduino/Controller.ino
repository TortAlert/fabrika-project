#include <Servo.h>


const int EMGpin = A0;
const int bPin_grip = 10;
const int bPin_fuck = 9;
const int bPin_rotate = 8;

int EMGstate = 0;
int flag1 = 0;
bool flag2 = 0;
int bState_grip = 0;
int bState_fuck = 0;
int bState_rotate = 0;


Servo rotServo1;
Servo rotServo2;
Servo rotServo3;
Servo rotServo4;
Servo rotServo5;
Servo rotServoR;

void setup() {
  // put your setup code here, to run once:
  delay( 3000 );
  Serial.begin(9600);
  
  rotServo1.attach(2);
  rotServo2.attach(3);
  rotServo3.attach(4);
  rotServo4.attach(5);
  rotServo5.attach(6);
  rotServoR.attach(7);

  pinMode(bPin_grip, INPUT_PULLUP);
  pinMode(bPin_fuck, INPUT_PULLUP);
  pinMode(bPin_rotate, INPUT_PULLUP);

  pinMode(EMGpin, INPUT);
}

void loop() {
  EMGstate = analogRead(EMGpin);

  if (EMGstate > 150) 
    if (flag1 < 10)
      ++flag1;
    else {
      flag1 = 0;
      if (flag2)
        flag2 = 0;
      else
        flag2 = 1;
    }
  

  bState_grip = digitalRead(bPin_grip);
  bState_fuck = digitalRead(bPin_fuck);
  bState_rotate = digitalRead(bPin_rotate);

  if (flag2) {
    rotServo1.write(180);
    rotServo2.write(180);
    rotServo3.write(180);
    rotServo4.write(180);
    rotServo5.write(180);
  }
  else {
    rotServo1.write(0);
    rotServo2.write(0);
    rotServo3.write(0);
    rotServo4.write(0);
    rotServo5.write(0);
  }

  if (bState_fuck) {
    rotServo1.write(180);
    rotServo2.write(180);
    rotServo3.write(0);
    rotServo4.write(180);
    rotServo5.write(180);
  }
  else {
    rotServo1.write(0);
    rotServo2.write(0);
    rotServo3.write(0);
    rotServo4.write(0);
    rotServo5.write(0);
  }

  if (bState_rotate)
    rotServoR.write(180);
  else
    rotServoR.write(0);

  Serial.println(EMGstate);
  Serial.println(flag1);
  Serial.println(flag2);
  delay(100);
}
