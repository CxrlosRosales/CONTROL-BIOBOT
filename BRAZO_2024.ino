#include <Servo.h>
Servo gripper;
Servo giromuneca;
Servo verticalmuneca;
Servo codo;
Servo girohombro;
int pos = 90;
int a = 90;
void setup() {
  gripper.attach(11);
  gripper.write(90);
  giromuneca.attach(10);
  giromuneca.write(90);
  verticalmuneca.attach(9);
  verticalmuneca.write(90);
  codo.attach(6);
  codo.write(90);
  girohombro.attach(5);
  girohombro.write(90);
}
void loop() {
  for (pos = 90; pos >= 0; pos--) {
    gripper.write(pos);
    delay(5);
  }
  for (pos = 0; pos <= 90; pos++) {
    gripper.write(pos);
    delay(5);
  }
  for (pos = 90; pos >= 0; pos--) {
    gripper.write(pos);
    delay(5);
  }
  for (pos = 0; pos <= 90; pos++) {
    gripper.write(pos);
    delay(5);
  }
  for (pos = 90; pos >= 0; pos--) {
    gripper.write(pos);
    delay(5);
  }
  for (pos = 0; pos <= 90; pos++) {
    gripper.write(pos);
    delay(5);
  }
  delay(500);
  //ahora corregimos el siguiente movimiento
  for (pos = 90; pos <= 180; pos++) {
    giromuneca.write(pos);
    delay(5);
  }
  for (pos = 180; pos >= 0; pos--) {
    giromuneca.write(pos);
    delay(5);
  }
  for (pos = 0; pos <= 90; pos++) {
    giromuneca.write(pos);
    delay(5);
  }
  for (pos = 90; pos >= 0; pos--) {
    girohombro.write(pos);
    delay(10);
  }
  for (pos = 90; pos >= 0; pos--) {
    codo.write(pos);
    verticalmuneca.write(pos);
    delay(10);
  }
  for (pos = 0; pos <= 50; pos++) {
    verticalmuneca.write(pos);
    delay(10);
  }
  for (pos = 90; pos >= 0; pos--) {
    gripper.write(pos);
    delay(10);
  }
  for (pos = 0; pos <= 150; pos++) {
    codo.write(pos);
    verticalmuneca.write(50 + (2 * pos) / 3);
    delay(10);
  }
  for (pos = 0; pos <= 180; pos++) {
    girohombro.write(pos);
    giromuneca.write(90 + pos / 2);
    delay(10);
  }
  for (pos = 150; pos >= 0; pos--) {
    codo.write(pos);
    verticalmuneca.write(50 + (2 * pos / 3));
    giromuneca.write(90 + 3 * pos / 5);
    delay(10);
  }
  for (pos = 0; pos <= 90; pos++) {
    gripper.write(pos);
    delay(10);
  }
  for (pos = 0; pos <= 90; pos++) {
    codo.write(pos);
    verticalmuneca.write(50 + 4 * pos / 9);
    girohombro.write(180 - pos);
    delay(10);
  }
  delay(12000);
}