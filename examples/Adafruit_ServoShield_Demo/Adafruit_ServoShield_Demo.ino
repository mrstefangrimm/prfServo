/*
This example uses the Adafruit 16-channel PWM & Servo Shield
-> http://www.adafruit.com/products/815

This demo will drive 8 servos, one after the other
on the first 8 pins of the PCA9685.

This file is a modification of the servo example distributed with the product mentioned above:
" This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution "

Written by Stefan Grimm, 2018.
Released into the public domain.
*/
 
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "prfServo.h"

// The template prfDemoImplServoShield is for demonstration purposes. You going to write your own implemention for your project.
prfDemoImplServoShield<Adafruit_PWMServoDriver> impl;
// defaut template arguments: uint32_t, float, uint16_t, float
prfServo<> servo(&impl, 0x55555555); // 16 times '01'; 1st order polynom; a + b*x

uint8_t servonum = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Polynom Regression Fitted (prf) Servo test!");
  
  servo.begin();
}

// the loop function runs over and over again forever
void loop() {
 
  Serial.println(servonum);
  for (float f = 0; f < 1.0; f += 0.01) {
    servo.write(servonum, f);
    delay(1);
  }

  delay(500);
  
  for (float f = 1.0; f > 0.0; f -= 0.01) {
    servo.write(servonum, f);
    delay(1);
  }

  delay(500);

  servonum++;
  if (servonum > 7) servonum = 0;
}

