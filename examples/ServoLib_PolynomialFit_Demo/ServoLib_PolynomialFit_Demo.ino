/*
This example uses the Servo library "Servo.h".

This demo will drive 2 servos, one after the other
on the pins 9 and 10 of your Arduino.

Written by Stefan Grimm, 2018.
Released into the public domain.
*/
 
#include <Servo.h>
#include "prfServo.h"

class prfImplServoLib :  public prfServoImplBase<uint8_t> {
  public:
  void begin() {
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
  }

  void put(float** params) {
    Serial.print("Servo 0: ");
    Serial.print(params[0][0]);
    Serial.print(" + ");
    Serial.print(params[0][1]);
    Serial.print("x + ");
    Serial.print(params[0][2]);
    Serial.println("x^2");
    Serial.print("Servo 1: ");
    Serial.print(params[1][0]);
    Serial.print(" + ");
    Serial.print(params[1][1]);
    Serial.print("x + ");
    Serial.print(params[1][2]);
    Serial.println("x^2");
  }

  void write(uint8_t num, uint8_t servoVal) {
    // Serial.print(num); Serial.print(" "); Serial.println(servoVal);
    if (num == 0) {
      servo.attach(9);
    } else {
      servo.attach(10);
    }    
    servo.write(servoVal);
    delay(15);
  }
  
  private:
  Servo servo;
};
prfImplServoLib impl;

prfServo<uint8_t, uint16_t, uint8_t> servoAtPin9and10(&impl, 0x0F); // 0x0F = 2 times '11'; 3st order; a + b*x + c*x^2

const uint16_t x[2][5] = { { 0, 64, 128, 192, 256 }, { 0, 64, 128, 192, 256 } }; 
const uint8_t y[2][5] = { { 90, 170, 90, 10, 90 }, { 90, 170, 90, 10, 90 } };
 
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Polynom Regression Fitted (prf) Servo test y = sin(x)!");

  uint8_t val = 0x0F;
  Serial.println((uint8_t)(val << 6), BIN);
  
  servoAtPin9and10.begin();
  servoAtPin9and10.calcParams(0, 5, x[0], y[0]);
  servoAtPin9and10.calcParams(1, 5, x[1], y[1]);

  servoAtPin9and10.put();
}

// the loop function runs over and over again forever
void loop() {

  for (int num = 0; num < 2 ; num++) {
    for (uint8_t i = 0; i < 255; i++) {
      servoAtPin9and10.write(num, i);
      delay(10);
    }
    delay(500);
  }
  
}

