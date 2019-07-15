/*
This is a demonstration program for one LnR-Actuator.
The program demonstrates sub-millimeter accuracy of the LnR Actuator
-> https://youtu.be/CnMcMh8CgUc
-> https://www.instructables.com/id/Linear-and-Rotation-Actuator/

This example uses the Adafruit 16-channel PWM & Servo Shield
-> https://www.adafruit.com/product/1411

Written by Stefan Grimm, 2019.
Released into the public domain.
*/

#include <Adafruit_PWMServoDriver.h>
#include "prfServo2.h"

class ServoShieldPCA9685Linear : public prfServo2ImplBase<uint16_t, float> {
public:
  void begin() {
    _pwm.begin();
    _pwm.setPWMFreq(60);
  }

  void get(float** params, float** offsets) const {
    // LnR-Actuator, measured values (lng)
    // params
    // 0  493
    // 10 394
    // 20 333
    // 30 275
    // 40 224
    // offsets
    // 0  7
    // 10 4
    // 20 5
    // 30 4
    // 40 5
    // Calculated polynomial parameters on: https://arachnoid.com/polysolve/
    params[0][0] = 4.9244285714285723e+002;
    params[0][1] = -1.1620238095238097e+001;
    params[0][2] = 2.2571428571428570e-001;
    params[0][3] = -2.5833333333333333e-003;
    offsets[0][0] = 6.8571428571428570e+000;
    offsets[0][1] = -3.5476190476190480e-001;
    offsets[0][2] = 1.4285714285714287e-002;
    offsets[0][3] = -1.6666666666666666e-004;

    // transformation for the rotation is f(x) = x
    params[1][0] = 0;
    params[1][1] = 1;
    offsets[1][0] = 0;    
  }

  void write(uint8_t num, uint16_t servoVal) {
    _pwm.setPWM(num, 0, servoVal);
  }

private:
  Adafruit_PWMServoDriver _pwm;
};

ServoShieldPCA9685Linear impl;
// forward polynomial: 0b00000011 => order of three for longitudinal, order one for rotary motion
// backward offset polynomial: 0b00000011 => order of three for longitudinal, order zero for rotary motion
prfServo2<uint8_t, float, uint16_t, float> servoLib(&impl, 0b00000111, 0b00000011);

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
