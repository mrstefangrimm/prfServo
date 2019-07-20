/*
This is a demonstration program for one LnR-Actuator. 
This example uses the Adafruit 16-channel PWM & Servo Shield
-> http://www.adafruit.com/products/815It

The program demonstrates sub-millimeter accuracy of the LnR-Actuator
-> https://www.instructables.com/id/Linear-and-Rotation-Actuator/

Written by Stefan Grimm, 2019.
Released into the public domain.
*/

#include <Servo.h>
#include "prfServo2.h"

class ServoPolyFit : public prfServo2ImplBase<uint16_t, float> {
public:
  void begin() {
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    _servo0.attach(8);
    _servo1.attach(9);
  }

  void get(float** params, float** offsets) const {
    // LnR-Actuator, measured values (lng)
    // params
    // 0  2180
    // 10 1750
    // 20 1460
    // 30 1225
    // 40  970
    // offsets
    // 0   0
    // 10  0
    // 20  0
    // 30  5
    // 40 10
    // Calculated polynomial parameters on: https://arachnoid.com/polysolve/
    params[0][0] = 2.1798571428571426e+003;
    params[0][1] = -5.2488095238095240e+001;
    params[0][2] = 1.0892857142857144e+000;
    params[0][3] = -1.3333333333333334e-002;
    offsets[0][0] = 1.4285714285714280e-001;
    offsets[0][1] = -1.7857142857142860e-001;
    offsets[0][2] = 1.0714285714285714e-002;

    // transformation for the rotation is f(x) = x
    params[1][0] = 1880;
    params[1][1] = -4;
    offsets[1][0] = 0;    
  }

  void write(uint8_t num, uint16_t servoVal) {
    switch (num) {
      default: break;
      case 0: _servo0.write(servoVal); break;
      case 1: _servo1.write(servoVal); break;
    }
  }

private:
  Servo _servo0, _servo1;
};

ServoPolyFit impl;
// forward polynomial: 0b00000011 => order of three for longitudinal, order one for rotary motion
// backward offset polynomial: 0b00000010 => order of two for longitudinal, order zero for rotary motion
prfServo2<uint8_t, float, uint16_t, float> servoLib(&impl, 0b00000111, 0b00000010);

void setup() {
  Serial.begin(9600);
  Serial.println("Polynomial Regression Fit (prf) Servo test!");

  servoLib.begin();
}

void loop() {
  servoLib.write(1, 200);
  servoLib.write(0, 0.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);

  servoLib.write(1, 200);
  servoLib.write(0, 10.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);
  
  servoLib.write(1, 200);
  servoLib.write(0, 20.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);

  servoLib.write(1, 200);
  servoLib.write(0, 30.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);

  servoLib.write(1, 200);
  servoLib.write(0, 40.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);
 
  servoLib.write(1, 200);
  servoLib.write(0, 30.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);

  servoLib.write(1, 200);
  servoLib.write(0, 20.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);

  servoLib.write(1, 200);
  servoLib.write(0, 10.0);
  delay(1000);
  servoLib.write(1, 372);
  delay(1000);

  for (int n = 0; n < 10; n++) {
    servoLib.write(1, 372);
    delay(500);
    for (float n = 10.0; n < 20.0; n += 0.2) {
      servoLib.write(0, n);
      delay(10);
    }
    delay(500);
    servoLib.write(1, 200);
    for (float n = 20.0; n > 10.0; n -= 0.2) {
      servoLib.write(0, n);
      delay(10);
    }
    delay(500);
  }
  delay(500);  
}
