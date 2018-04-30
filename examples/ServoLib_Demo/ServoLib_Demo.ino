/*
This example uses the Servo library "Servo.h".

This demo will drive 2 servos, one after the other
on the pins 9 and 10 of your Arduino.

Written by Stefan Grimm, 2018.
Released into the public domain.
*/

#include <Servo.h>
#include "prfServo.h"

// The template prfDemoImplServoShield is for demonstration purposes. You going to write your own implemention for your project.
prfDemoImplServoLib<Servo> impl;
prfServo<uint32_t, float, uint8_t> servoAtPin9and10(&impl, 0x05); // 2 times '01'; 1st order; a + b*x

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Polynom Regression Fitted (prf) Servo test!");
  
  servoAtPin9and10.begin();
}

// the loop function runs over and over again forever
void loop() {

  for (int num = 0; num < 2; num++) {
    for (float f = 0; f < 1.0; f += 0.01) {
      servoAtPin9and10.write(num, f);
    }

    delay(500);
  
    for (float f = 1.0; f > 0.0; f -= 0.01) {
      servoAtPin9and10.write(num, f);
    }

    delay(500);
  }
}

