# fabrika-project
Проект бионического протеза руки, изготавливаемого на 3D принтере.

Конструкция основана на OpenSource проектке InMoov: https://inmoov.fr/hand-and-forarm/

![f4628cbf-dfa9-4a33-b8b8-3e07ea2fa36e](https://github.com/TortAlert/fabrika-project/assets/60708873/365b5484-5046-45a8-8a98-1266f54f3d8c)
![c23b15fd-8851-486e-9534-be891021dc72](https://github.com/TortAlert/fabrika-project/assets/60708873/56c11458-3672-4bd5-8e98-a5b1ae149f43)


Необходимые элементы:
- x2 батарейка типа Крона,
- Arduino Leonardo/Amperka Iskra Neo,
- x2 button,
- x7 servo 180,
- EMG sensor "Muscle Sensor v3"

Подключение EMG датчика:

![Безымянный](https://github.com/TortAlert/fabrika-project/assets/60708873/dd609c29-ca07-4c04-97d9-880454c6f481)



Код контроллера:
``` c++
#include <Servo.h>


const int EMGpin = A0;
const int bPin_grip = 8;
const int bPin_fuck = 9;
const int bPin_rotate = 10;

int EMGstate = 0;
bool flag = 0;
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

  if (EMGstate > 100)
    flag = ~flag;

  bState_grip = digitalRead(bPin_grip);
  bState_fuck = digitalRead(bPin_fuck);
  bState_rotate = digitalRead(bPin_rotate);

  if (flag) {
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
    rotServoRwrite(180);
  else
    rotServoRwrite(0);

  Serial.println(EMGstate);
  delay(200);
}
```
