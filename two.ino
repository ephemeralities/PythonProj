#include <Servo.h>

Servo a;
Servo b;
Servo c;
Servo d;

int angle;
int angle2;
int angle3;
int angle4;

void setup() {
    angle = 90;
    angle2 = 92;
    angle3 = 180;
    angle4 = 0;
    a.attach(D0);
    b.attach(D1);
    c.attach(D2);
    d.attach(D3);
}

void loop() {
    a.write((180 - angle) - 10);
    b.write(180 - angle2);
    c.write(180 - angle3);
    d.write(angle4);
}
