/*
The Arduino program for the Pencil Lead Drive.
The program demonstrates sub-millimeter accuracy of the LnR Actuator by using the prfServo library.
-> https://youtu.be/KJdUGMOCTKk
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
    // Longitudinal Right
    //  0 360
    //  5 388
    // 10 418
    // 15 444
    // 20 474
    // 25 504
    params[0][0] = 3.5982539682539806e+002;
    params[0][1] = 5.9137566137556290e+000;
    params[0][2] = -3.1746031745929215e-002;
    params[0][3] = 1.0370370370343846e-003;
    //  0 -6
    //  5 -4
    // 10 -2
    // 15 -4
    // 20 -4
    // 25  8
    offsets[0][0] = -6.5238095238093960e+000;
    offsets[0][1] = 1.6174603174602150e+000;
    offsets[0][2] = -1.8666666666665600e-001;
    offsets[0][3] = 5.7777777777775020e-003;

    // Rotary Right
    //   0 610
    //  45 498
    //  90 386
    // 135 296
    // 180 200
    params[1][0] = 6.1071428571428580e+002;
    params[1][1] = -2.7095238095238145e+000;
    params[1][2] = 3.3862433862434362e-003;
    params[1][3] = -5.4869684499315375e-006;
    //   0 4 
    //  45 3
    //  90 8
    // 135 6
    // 180 2
    offsets[1][0] = 3.7428571428571430e+000;
    offsets[1][1] = -4.7089947089947100e-002;
    offsets[1][2] = 1.5167548500881833e-003;
    offsets[1][3] = -7.3159579332418835e-006;
    
    // Longitudinal Left
    //  0 400
    //  5 362
    // 10 334
    // 15 308
    // 20 282
    // 25 256
    params[2][0] = 3.9969841269841225e+002;
    params[2][1] = -8.2693121693117920e+000;
    params[2][2] = 2.0412698412694500e-001;
    params[2][3] = -4.1481481481471360e-003;
    //  0 -4
    //  5  2
    // 10  2
    // 15  2
    // 20  4
    // 25  4
    offsets[2][0] = -3.6507936507935960e+000;
    offsets[2][1] = 1.3153439153438717e+000;
    offsets[2][2] = -8.7936507936503400e-002;
    offsets[2][3] = 1.9259259259258088e-003;

    // Rotary Left
    //   0 170
    //  45 266
    //  90 356
    // 135 444
    // 180 550
    params[3][0] = 1.6977142857142857e+002;
    params[3][1] = 2.3523809523809520e+000;
    params[3][2] = -5.2910052910052920e-003;
    params[3][3] = 2.1947873799725652e-005;
    //   0 -8
    //  45 -6
    //  90 -4
    // 135 -2
    // 180 -4
    offsets[3][0] = -7.9428571428571430e+000;
    offsets[3][1] = 1.3756613756613744e-002;
    offsets[3][2] = 7.0546737213403880e-004;
    offsets[3][3] = -3.6579789666209417e-006;
  }

  void write(uint8_t num, uint16_t servoVal) {
    _pwm.setPWM(num, 0, servoVal);
  }

private:
  Adafruit_PWMServoDriver _pwm;
};

ServoShieldPCA9685Linear impl;
prfServo2<uint8_t, float, uint16_t, float> servoLib(&impl, 0b11111111, 0b11111111);

enum ServoNum {
  RLNG = 0,
  RRTN,
  LLNG,
  LRTN
};

void setup() {
  Serial.begin(9600);
  Serial.println("Pencil Lead Drive!");
 
  servoLib.begin();

  servoLib.write(RRTN, 0);
  servoLib.write(LRTN, 0);
  delay(1000);
  servoLib.write(RLNG, 12);
  servoLib.write(LLNG, 12);
  delay(500);

  Serial.print("Send any character to start!");
  int ch = -1;
  do {
    ch = Serial.read();
    delay(100);
  } while (ch == -1 );
  delay(5000);
}

void loop() {
  for (int angleDeg = 0; angleDeg < 180; angleDeg += 1) {
    float angleRad = angleDeg / 180.0 * PI;
    float rightsideLngMM = 12 + (sin(angleRad) * 12); // Sin wave between 0 and 24 mm
    float leftsideLngMM = 12 - (sin(angleRad) * 12); // Sin wave between 0 and 24 mm
    servoLib.write(RLNG, rightsideLngMM);
    servoLib.write(LLNG, leftsideLngMM);
    servoLib.write(RRTN, angleDeg);
    servoLib.write(LRTN, angleDeg);
    delay(10);
  }
  for (int angleDeg = 180; angleDeg > 0; angleDeg -= 1) {
    float angleRad = angleDeg / 180.0 * PI;
    float lngR = 12 - (sin(angleRad) * 12);
    float lngL = 12 + (sin(angleRad) * 12);
    servoLib.write(RLNG, lngR);
    servoLib.write(LLNG, lngL);
    servoLib.write(RRTN, angleDeg);
    servoLib.write(LRTN, angleDeg);
    delay(10);
  }
}
