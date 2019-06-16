/*
Unit tests for the prfServo3 Arduino library

Written by Stefan Grimm, 2019.
Released into the public domain.
*/

#line 9 "basic.ino"
#include <ArduinoUnit.h>

#include "prfServo3.h"

class prfServoImplMockUnit16 : public prfServo3ImplBase<uint16_t, double>
{
public:
  void(*getStub)(double** params, double** dirOffsets, double** disOffsets);
  void get(double** params, double** dirOffsets, double** disOffsets) const override {
    getStub(params, dirOffsets, disOffsets);
  }

  void begin() override {
  }

  uint8_t writeStubNum;
  uint16_t writeStubVal;
  void write(uint8_t num, uint16_t servoVal) override {
    writeStubNum = num;
    writeStubVal = servoVal;
  }

};

class prfServoImplMockInt32 : public prfServo3ImplBase<int32_t>
{
public:

void(*getStub)(float** params, float** dirOffsets, float** disOffsets);
  void get(float** params, float** dirOffsets, float** disOffsets) const override {
    getStub(params, dirOffsets, disOffsets);
  }
  
  void begin() override {
  }

  uint8_t writeStubNum;
  int32_t writeStubVal;
  void write(uint8_t num, int32_t servoVal) override {
    writeStubNum = num;
    writeStubVal = servoVal;
  }

};

void getResults4Servo(double** params, double** dirOffsets, double** disOffsets) {
  params[0][0] = 100;
  params[0][1] = 10;
  params[1][0] = 100;
  params[1][1] = 10;
  params[1][2] = 5;
  params[2][0] = 100;
  params[2][1] = 10;
  params[2][2] = 5;
  params[2][3] = 2;
  params[3][0] = 80;
  dirOffsets[0][0] = 40;
  dirOffsets[1][0] = 30;
  dirOffsets[2][0] = 20;
  dirOffsets[3][0] = 10;
  disOffsets[0][0] = 0;
  disOffsets[1][0] = 0;
  disOffsets[2][0] = 0;
  disOffsets[3][0] = 0;
}

void getResults4ServoInverse(double** params, double** dirOffsets, double** disOffsets) {
  params[0][0] = 400;
  params[1][0] = 300;
  params[2][0] = 200;
  params[3][0] = 100;
  dirOffsets[0][0] = -100;
  dirOffsets[0][1] = -10;
  dirOffsets[1][0] = -100;
  dirOffsets[1][1] = -10;
  dirOffsets[1][2] = -5;
  dirOffsets[2][0] = -100;
  dirOffsets[2][1] = -10;
  dirOffsets[2][2] = -5;
  dirOffsets[2][3] = -2;
  dirOffsets[3][0] = -80;
  disOffsets[0][0] = 0;
  disOffsets[1][0] = 0;
  disOffsets[2][0] = 0;
  disOffsets[3][0] = 0;
}

void getResults4ServoNegativeOffsets(double** params, double** dirOffsets, double** disOffsets) {
  params[0][0] = 100;
  params[0][1] = 10;
  params[1][0] = 100;
  params[1][1] = 10;
  params[2][0] = 100;
  params[2][1] = 10;
  params[3][0] = 100;
  params[3][1] = 10;
  dirOffsets[0][0] = -0;
  dirOffsets[1][0] = -10;
  dirOffsets[2][0] = -20;
  dirOffsets[3][0] = -30;
  disOffsets[0][0] = -4;
  disOffsets[1][0] = -3;
  disOffsets[2][0] = -2;
  disOffsets[3][0] = -1;
}

void getResults8Servo(double** params, double** dirOffsets, double** disOffsets) {
  params[0][0] = 100;
  params[0][1] = 10;
  params[1][0] = 100;
  params[1][1] = 10;
  params[2][0] = 100;
  params[2][1] = 10;
  params[3][0] = 100;
  params[3][1] = 10;
  params[4][0] = 100;
  params[4][1] = 10;
  params[5][0] = 100;
  params[5][1] = 10;
  params[6][0] = 100;
  params[6][1] = 10;
  params[7][0] = 100;
  params[7][1] = 10;
  dirOffsets[0][0] = 10;
  dirOffsets[1][0] = 10;
  dirOffsets[2][0] = 10;
  dirOffsets[3][0] = 10;
  dirOffsets[4][0] = 10;
  dirOffsets[5][0] = 10;
  dirOffsets[6][0] = 10;
  dirOffsets[7][0] = 10;
  disOffsets[0][0] = 0;
  disOffsets[1][0] = 0;
  disOffsets[2][0] = 0;
  disOffsets[3][0] = 0;
  disOffsets[4][0] = 0;
  disOffsets[5][0] = 0;
  disOffsets[6][0] = 0;
  disOffsets[7][0] = 0;
}

void getResults16Servo(double** params, double** dirOffsets, double** disOffsets) {
  params[0][0] = 100;
  params[0][1] = 10;
  params[1][0] = 100;
  params[1][1] = 10;
  params[2][0] = 100;
  params[2][1] = 10;
  params[3][0] = 100;
  params[3][1] = 10;
  params[4][0] = 100;
  params[4][1] = 10;
  params[5][0] = 100;
  params[5][1] = 10;
  params[6][0] = 100;
  params[6][1] = 10;
  params[7][0] = 100;
  params[7][1] = 10;
  params[8][0] = 100;
  params[8][1] = 10;
  params[9][0] = 100;
  params[9][1] = 10;
  params[10][0] = 100;
  params[10][1] = 10;
  params[11][0] = 100;
  params[11][1] = 10;
  params[12][0] = 100;
  params[12][1] = 10;
  params[13][0] = 100;
  params[13][1] = 10;
  params[14][0] = 100;
  params[14][1] = 10;
  params[15][0] = 100;
  params[15][1] = 10;
  dirOffsets[0][0] = 10;
  dirOffsets[1][0] = 10;
  dirOffsets[2][0] = 10;
  dirOffsets[3][0] = 10;
  dirOffsets[4][0] = 10;
  dirOffsets[5][0] = 10;
  dirOffsets[6][0] = 10;
  dirOffsets[7][0] = 10;
  dirOffsets[8][0] = 10;
  dirOffsets[9][0] = 10;
  dirOffsets[10][0] = 10;
  dirOffsets[11][0] = 10;
  dirOffsets[12][0] = 10;
  dirOffsets[13][0] = 10;
  dirOffsets[14][0] = 10;
  dirOffsets[15][0] = 10;
  disOffsets[0][0] = 3;
  disOffsets[1][0] = 3;
  disOffsets[2][0] = 3;
  disOffsets[3][0] = 3;
  disOffsets[4][0] = 3;
  disOffsets[5][0] = 3;
  disOffsets[6][0] = 3;
  disOffsets[7][0] = 3;
  disOffsets[8][0] = 3;
  disOffsets[9][0] = 3;
  disOffsets[10][0] = 3;
  disOffsets[11][0] = 3;
  disOffsets[12][0] = 3;
  disOffsets[13][0] = 3;
  disOffsets[14][0] = 3;
  disOffsets[15][0] = 3;
}

void getResults10Servo(double** params, double** offsets, double** disOffsets) {
  // LURTN
  params[0][0] = 1.2942268654268088e+002;
  params[0][1] = 1.6668375402407262e+000;
  offsets[0][0] = 10;
  // LULNG
  params[1][0] = 5.5452380952380930e+002;
  params[1][1] = -2.6484593837534930e+000;
  params[1][2] = 1.1929477673422232e-002;
  params[1][3] = -2.7138883234954693e-005;
  offsets[1][0] = 10;
  // LLRTN
  params[2][0] = 1.5442914556378040e+002;
  params[2][1] = 1.5882527835305206e+000;
  offsets[2][0] = 10;
  // LLLNG
  params[3][0] = 1.3666666666666668e+002;
  params[3][1] = 2.8253968253968250e+000;
  params[3][2] = -1.3016971494480146e-002;
  params[3][3] = 3.0757400999615536e-005;
  offsets[3][0] = 10;
  // RLLNG
  params[4][0] = 5.7880952380952260e+002;
  params[4][1] = -2.3641456582632174e+000;
  params[4][2] = 9.3590377327392710e-003;
  params[4][3] = -2.1711106587961670e-005;
  offsets[4][0] = 10;
  // RLRTN
  params[5][0] = 1.3774938998134064e+002;
  params[5][1] = 1.5490885603559636e+000;
  offsets[5][0] = 10;
  // RULNG
  params[6][0] = 1.8559523809523685e+002;
  params[6][1] = 2.1031746031746907e+000;
  params[6][2] = -7.4147305981224840e-003;
  params[6][3] = 1.8092588823305492e-005;
  offsets[6][0] = 10;
  // RURTN
  params[7][0] = 1.6024944124341286e+002;
  params[7][1] = 1.6079886813344540e+000;
  offsets[7][0] = 10;
  // GALNG
  params[8][0] = 5.3464285714285590e+002;
  params[8][1] = -2.8109243697478114e+000;
  params[8][2] = 1.3346515076618000e-002;
  params[8][3] = -3.2566659881943620e-005;
  offsets[8][0] = 10;
  // GARTN
  params[9][0] = 1.4526246180975622e+002;
  params[9][1] = 1.5686194098710244e+000;
  offsets[9][0] = 10;
}

void getResults4Servos_SignedOutcome(float** params, float** offsets, double** disOffsets) {
  // https://www.mathportal.org/calculators/polynomials-solvers/polynomial-graphing-calculator.php
  params[0][0] = 100;
  params[0][1] = 10;
  //  turning point of servo1: 5.125
  params[1][0] = 100;
  params[1][1] = 10;
  params[1][2] = -1;
  params[2][0] = 100;
  params[2][1] = 10;
  params[2][2] = -1;
  params[2][3] = 1;
  params[3][0] = -100;
  params[3][1] = 10;
  offsets[0][0] = 15;
  offsets[1][0] = 15;
  offsets[2][0] = 15;
  offsets[3][0] = 15;
}

test(test_4_Servos_polynomials_of_different_order_forwards) {

  prfServoImplMockUnit16 impl;
  // Servo 0: order 1, 100 + 10*x
  // Servo 1: order 2, 100 + 10*x + 5*x*x
  // Servo 2: order 3, 100 + 10*x + 5*x*x + 2*x*x*x
  // Servo 3: order 0, 80
  impl.getStub = &getResults4Servo;

  prfServo3<uint8_t, uint8_t, uint16_t, double> fourServos(&impl, 0x39, 0x00, 0x00);

  int freeMemBeforeHeapAlloc = freeMemory();
  fourServos.begin();

  impl.writeStubVal = 0;
  fourServos.write(0, 0);
  assertEqual(100, impl.writeStubVal);
  impl.writeStubVal = 0;
  fourServos.write(0, 255);
  assertEqual(2650, impl.writeStubVal);

  impl.writeStubVal = 0;
  fourServos.write(1, 2);
  assertEqual(140, impl.writeStubVal);

  impl.writeStubVal = 0;
  fourServos.write(2, 2);
  assertEqual(156, impl.writeStubVal);

  impl.writeStubVal = 0;
  fourServos.write(3, 10);
  assertEqual(80, impl.writeStubVal);

  fourServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

test(test_8_Servos_same_polynomial_forwards) {
  prfServoImplMockUnit16 impl;
  // Servo 0-7: order 1, 100 + 10*x
  impl.getStub = &getResults8Servo;

  prfServo3<uint16_t, uint8_t, uint16_t, double> eightServos(&impl, 0x5555, 0x0000, 0x0000);

  int freeMemBeforeHeapAlloc = freeMemory();
  eightServos.begin();

  for (int servo = 0; servo < 8; servo++)
  {
    for (int valIn = 0; valIn <= 255; valIn += 5) {
      impl.writeStubNum = 0;
      impl.writeStubVal = 0;
      eightServos.write(servo, valIn);
      assertEqual(servo, impl.writeStubNum);
      assertEqual(100 + 10 * valIn, impl.writeStubVal);
    }
  }

  eightServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

test(test_16_Servos_same_polynomial_forwards) {
  prfServoImplMockUnit16 impl;
  // Servo 0-15: order 1, 100 + 10*x, travel distance offset: +3, backwards offset: +10
  impl.getStub = &getResults16Servo;

  prfServo3<uint32_t, uint8_t, uint16_t, double> sixteenServos(&impl, 0x55555555, 0x00000000, 0x00000000);

  int freeMemBeforeHeapAlloc = freeMemory();
  sixteenServos.begin();

  for (int servo = 0; servo < 16; servo++)
  {
    for (int valIn = 0; valIn <= 255; valIn += 5) {
      impl.writeStubNum = 0;
      impl.writeStubVal = 0;
      sixteenServos.write(servo, valIn);
      assertEqual(servo, impl.writeStubNum);
      assertEqual((100 + 10 * valIn) + 3, impl.writeStubVal);
    }
  }

  sixteenServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

/*
test(test_4_Servos_polynomials_of_different_order_backwards_forwards) {

  prfServoImplMockUnit16 impl;
  // Servo 0: order 1 + order 0, (100 + 10*x), distance +3, backwards + 40
  // Servo 1: order 2 + order 0, (100 + 10*x + 5*x*x), distance +3, backwards + 30
  // Servo 2: order 3 + order 0, (100 + 10*x + 5*x*x + 2*x*x*x), distance +3, backwards + 20 
  // Servo 3: order 0 + order 0, 80, distance +3, backwards + 10
  impl.getStub = &getResults4Servo;
  
  prfServo2<uint8_t, uint8_t, uint16_t, double> fourServos(&impl, 0x39, 0x00);

  int freeMemBeforeHeapAlloc = freeMemory();
  fourServos.begin();

  // Servo 0
  // forward to 255
  impl.writeStubVal = 0;
  fourServos.write(0, 255);
  assertEqual(2650, impl.writeStubVal);

  // backward
  impl.writeStubVal = 0;
  fourServos.write(2680, 254);
  assertEqual(0, impl.writeStubVal);

  impl.writeStubVal = 0;
  fourServos.write(0, 250);
  assertEqual(2640, impl.writeStubVal);

  impl.writeStubVal = 0;
  fourServos.write(0, 0);
  assertEqual(140, impl.writeStubVal);

  // forward
  impl.writeStubVal = 0;
  fourServos.write(0, 1);
  assertEqual(110, impl.writeStubVal);

  impl.writeStubVal = 0;
  fourServos.write(0, 5);
  assertEqual(150, impl.writeStubVal);
  
  // Servo 1
  // forward to 5
  impl.writeStubVal = 0;
  fourServos.write(1, 5);
  assertEqual(275, impl.writeStubVal);
  // backward
  impl.writeStubVal = 0;
  fourServos.write(1, 2);
  assertEqual(170, impl.writeStubVal);

  // Servo 2
  // forward to 3
  impl.writeStubVal = 0;
  fourServos.write(2, 3);
  assertEqual(229, impl.writeStubVal);
  // backward
  impl.writeStubVal = 0;
  fourServos.write(2, 2);
  assertEqual(176, impl.writeStubVal);

  // Servo 3
  // forward to 255
  impl.writeStubVal = 0;
  fourServos.write(3, 255);
  assertEqual(80, impl.writeStubVal);
  // backward
  impl.writeStubVal = 0;
  fourServos.write(3, 3);
  assertEqual(90, impl.writeStubVal);
}

test(test_4_Servos_polynomials_of_different_order_backwards_forwards_inverse) {

  prfServoImplMockUnit16 impl;
  // Servo 0: order 0 + order 1, 400, backwards - (100 + 10*x)
  // Servo 1: order 0 + order 2, 300, backwards - (100 + 10*x + 5*x*x)
  // Servo 2: order 0 + order 3, 200, backwards - (100 + 10*x + 5*x*x + 2*x*x*x) 
  // Servo 3: order 0 + order 0, 100, backwards - 80
  impl.getStub = &getResults4ServoInverse;

  prfServo2<uint8_t, uint8_t, uint16_t, double> fourServos(&impl, 0x00, 0x39);

  int freeMemBeforeHeapAlloc = freeMemory();
  fourServos.begin();

  // Servo 0
  // forward to anything (the result will constant anyway)
  impl.writeStubVal = 0;
  fourServos.write(0, 41);
  assertEqual(400, impl.writeStubVal);
  // backward
  impl.writeStubVal = 0;
  fourServos.write(0, 29);
  assertEqual(10, impl.writeStubVal);

  // Servo 1
  // forward to anything (the result will constant anyway)
  impl.writeStubVal = 0;
  fourServos.write(1, 5);
  assertEqual(300, impl.writeStubVal);
  // backward
  impl.writeStubVal = 0;
  fourServos.write(1, 2);
  assertEqual(160, impl.writeStubVal);

  // Servo 2
  // forward to anything (the result will constant anyway)
  impl.writeStubVal = 0;
  fourServos.write(2, 3);
  assertEqual(200, impl.writeStubVal);
  // backward
  impl.writeStubVal = 0;
  fourServos.write(2, 2);
  assertEqual(44, impl.writeStubVal);

  // Servo 3
  // forward to anything (the result will constant anyway)
  impl.writeStubVal = 0;
  fourServos.write(3, 255);
  assertEqual(100, impl.writeStubVal);
  // backward
  impl.writeStubVal = 0;
  fourServos.write(3, 3);
  assertEqual(20, impl.writeStubVal);
}

test(test_4_Servos_negative_offsets_backwards) {
  prfServoImplMockUnit16 impl;
  // Servo 0-7: order 1, 100 + 10*x
  impl.getStub = &getResults4ServoNegativeoffsets;

  prfServo2<uint8_t, uint8_t, uint16_t, double> fourServos(&impl, 0x55, 0x00);

  int freeMemBeforeHeapAlloc = freeMemory();
  fourServos.begin();

  // forward
  for (int n = 0; n < 4; n++) {
    fourServos.write(n, 255);
  }

  // backward
  for (int servo = 0; servo < 4; servo++)
  {
    for (int valIn = 250; valIn >= 0; valIn -= 5) {
      impl.writeStubNum = 0;
      impl.writeStubVal = 0;
      fourServos.write(servo, valIn);
      assertEqual(servo, impl.writeStubNum);
      assertEqual((100 + 10 * valIn) - (10 * servo), impl.writeStubVal);
    }
  }

  fourServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

test(test_8_Servos_same_polynomial_backwards) {
  prfServoImplMockUnit16 impl;
  // Servo 0-7: order 1, 100 + 10*x
  impl.getStub = &getResults8Servo;

  prfServo2<uint16_t, uint8_t, uint16_t, double> eightServos(&impl, 0x5555, 0x0000);

  int freeMemBeforeHeapAlloc = freeMemory();
  eightServos.begin();

  // forward
  for (int n = 0; n < 8; n++) {
    eightServos.write(n, 255);
  }

  for (int servo = 0; servo < 8; servo++)
  {
    for (int valIn = 250; valIn >= 0; valIn -= 5) {
      impl.writeStubNum = 0;
      impl.writeStubVal = 0;
      eightServos.write(servo, valIn);
      assertEqual(servo, impl.writeStubNum);
      assertEqual((100 + 10 * valIn) + 10, impl.writeStubVal);
    }
  }
  
  eightServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}
*/

test(test_16_Servos_same_polynomial_backwards) {
  prfServoImplMockUnit16 impl;
  // Servo 0-15: order 1, 100 + 10*x, travel distance offset: +3
  impl.getStub = &getResults16Servo;

  prfServo3<uint32_t, uint8_t, uint16_t, double> sixteenServos(&impl, 0x55555555, 0x00000000, 0x00000000);

  int freeMemBeforeHeapAlloc = freeMemory();
  sixteenServos.begin();

  // forward
  for (int n = 0; n < 16; n++) {
    sixteenServos.write(n, 255);
  }

  for (int servo = 0; servo < 16; servo++)
  {
    for (int valIn = 250; valIn >= 0; valIn -= 5) {
      impl.writeStubNum = 0;
      impl.writeStubVal = 0;
      sixteenServos.write(servo, valIn);
      assertEqual(servo, impl.writeStubNum);
      assertEqual((100 + 10 * valIn) + 3 + 10, impl.writeStubVal);
    }
  }

  sixteenServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

/*
test(test_4_Servos_float_in_int32_out_float_math_forwards_backwards) {

  prfServoImplMockInt32 impl;
  // Servo 0: order 1, 100 + 10*x
  // Servo 1: order 2, 100 + 10*x - 1*x*x
  // Servo 2: order 3, 100 + 10*x - 1*x*x + 1*x*x*x
  // Servo 3: order 1, -100 + 10*x
  impl.getStub = &getResults4Servos_SignedOutcome;

  prfServo2<uint8_t, float, int32_t> fourServos(&impl, 0x79, 0x00);

  int freeMemBeforeHeapAlloc = freeMemory();
  fourServos.begin();

  // Set servos to a value below the tested range
  // It is going backwards (e.g. uses the offset) because the initial value is zero.
  for (int n = 0; n < 4; n++) {
    fourServos.write(n, -3);
  }

  // Servo 0
  for (float f = -1; f < 1; f += 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(0, f);
    assertEqual((int32_t)round(100 + 10*f), impl.writeStubVal);
  }

  // Servo 1
  for (float f = -1; f < 1; f += 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(1, f);
    assertEqual((int32_t)round(100 + 10*f - 1*f*f), impl.writeStubVal);
  }

  // Servo 2
  for (float f = -1; f < 1; f += 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(2, f);
    assertEqual((int32_t)round(100 + 10*f - 1*f*f + 1*f*f*f), impl.writeStubVal);
  }

  // Servo 4
  for (float f = -1; f < 1; f += 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(3, f);
    assertEqual((int32_t)round(-100 + 10 * f), impl.writeStubVal);
  }

  // Servo 0
  for (float f = 1; f < -1; f -= 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(0, f);
    assertEqual((int32_t)round(100 + 10 * f + 15), impl.writeStubVal);
  }

  // Servo 1
  for (float f = 1; f < -1; f -= 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(1, f);
    assertEqual((int32_t)round(100 + 10 * f - 1 * f*f + 15), impl.writeStubVal);
  }

  // Servo 2
  for (float f = 1; f < -1; f -= 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(2, f);
    assertEqual((int32_t)round(100 + 10 * f - 1 * f*f + 1 * f*f*f + 15), impl.writeStubVal);
  }

  // Servo 4
  for (float f = 1; f < -1; f -= 0.1) {
    impl.writeStubVal = 0;
    fourServos.write(3, f);
    assertEqual((int32_t)round(-100 + 10 * f + 15), impl.writeStubVal);
  }
 
  fourServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}
*/

test(test_10_Servos_process_time) {
  prfServoImplMockUnit16 impl;
  // Servo 0-15: order 1, 100 + 10*x
  impl.getStub = &getResults10Servo;

  //0x0777DD = 0000 01 11 01 11 11 01 11 01
  prfServo3<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD, 0x00000000, 0x00000000);

  int freeMemBeforeHeapAlloc = freeMemory();
  tenServos.begin();

  unsigned long begin = micros();

  // forward
  for (int servo = 0; servo < 10; servo++)
  {
    tenServos.write(servo, 200);
  }

  // backward
  for (int servo = 0; servo < 10; servo++)
  {
    tenServos.write(servo, 180);
  }

  unsigned long end = micros();
  int memoryFootprint = freeMemBeforeHeapAlloc - freeMemory();

  tenServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());

  Serial.println("prfServo3");
  Serial.println("---");

  Serial.print("Process time: ");
  Serial.print((end - begin) / 2000.0);
  Serial.println(" ms");

  Serial.print("Memory usage: ");
  Serial.print(memoryFootprint);
  Serial.println(" Bytes");
  Serial.println("---");
}

void setup()
{
  Serial.begin(9600);
  while(!Serial) {}
}

void loop()
{
  Test::run();
}
