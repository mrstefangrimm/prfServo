/*
This is a demonstration program for one LnR-Actuator. It uses the Arduino
Servo library 'Servo.h'.

The program demonstrates sub-millimeter accuracy despite a mechanical play.

https://www.instructables.com/id/Linear-and-Rotation-Actuator/

Written by Stefan Grimm, 2019.
Released into the public domain.
*/

#include <Adafruit_PWMServoDriver.h>
#include "prfServo2.h"

class ServoShieldPCA9685Linear : public prfServo2ImplBase<uint16_t, float> {
public:
  ServoShieldPCA9685Linear(Adafruit_PWMServoDriver& pwm) : _pwm(pwm) {
  }

  void begin() {
    _pwm.begin();
    _pwm.setPWMFreq(60);
  }

  void get(float** params, float** offsets) const {

    params[0][0] = 4.6005714285714290e+002;
    params[0][1] = -1.4799107142857226e+000;
    params[0][2] = 4.0108816964286640e-003;
    params[0][3] = -7.6293945312502400e-006;
    offsets[0][0] = 1.9828571428571430e+001;
    offsets[0][1] = -3.5267857142857140e-002;
    offsets[0][2] = 1.7438616071428572e-004;

     //Mechanical play of 8 millimeters
    //params[0][0] = 4.3188571428571470e+002;
    //params[0][1] = -1.3058035714286138e+000;
    //params[0][2] = 3.4528459821433193e-003;
    //params[0][3] = -7.6293945312512040e-006;
    //offsets[0][0] = 1.1577142857142857e+002;
    //offsets[0][1] = -7.0535714285714290e-001;
    //offsets[0][2] = 2.0228794642857144e-003;
  }

  void write(uint8_t num, uint16_t servoVal) {
    _pwm.setPWM(num, 0, servoVal);
  }

private:
  Adafruit_PWMServoDriver& _pwm;
};

Adafruit_PWMServoDriver pwm;
ServoShieldPCA9685Linear impl(pwm);
// forward polynomial: 0b00000011 => order of three
// backward offset polynomial: 0b00000010 => order of two
prfServo2<uint8_t, uint8_t, uint16_t, float> servoLib(&impl, 0b00000011, 0b00000010);

int begin = 0;
int end = 64;
int direction = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("Polynomial Regression Fit (prf) Servo test!");

  servoLib.begin();
}

void moveItF(int begin, int end, bool twoWay);
void moveItB(int begin, int end, bool twoWay);

void loop() {
  moveItF(0,  64, true);
  moveItF(0, 128, true);
  moveItF(0, 192, true);
  moveItF(0, 255, false);
  
  moveItB(255, 191, true);
  moveItB(255, 127, true);
  moveItB(255,  64, true);
  moveItB(255,   0, false);
}

void moveItF(int begin, int end, bool twoWay) {
  for (int n = begin; n < end; n++) {
    servoLib.write(0, n);
    delay(50);
  }
  if (twoWay) {
    for (int n = end; n > begin; n--) {
      servoLib.write(0, n);
      delay(50);
    }
  }
}

void moveItB(int begin, int end, bool twoWay) {
  for (int n = begin; n > end; n--) {
    servoLib.write(0, n);
    delay(50);
  }
  if (twoWay) {
    for (int n = end; n < begin; n++) {
      servoLib.write(0, n);
      delay(50);
    }
  }
}
