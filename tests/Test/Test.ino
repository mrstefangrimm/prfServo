/*
Unit tests for the prfServo Arduino library

Written by Stefan Grimm, 2019.
Released into the public domain.
*/

#line 9 "basic.ino"
#include <ArduinoUnit.h>

#include "prfServo.h"

class prfServoImplMockUnit16 : public prfServoImplBase<uint16_t, double>
{
public:

  void(*getStub)(double** params);
  void get(double** params) const override {
    getStub(params);
  }

  double** putStub;
  void put(double** params)  override {
    putStub = params;
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

class prfServoImplMockInt32 : public prfServoImplBase<int32_t>
{
public:

  void(*getStub)(float** params);
  void get(float** params) const override {
    getStub(params);
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

void getResults4Servo(double** params) {
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
}

void getResults8Servo(double** params) {
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
}

void getResults16Servo(double** params) {
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
}

void getResults4Servos_SignedOutcome(float** params) {
  params[0][0] = 100;
  params[0][1] = 1000;
  params[1][0] = 100;
  params[1][1] = 1000;
  params[1][2] = -10000;
  params[2][0] = 100;
  params[2][1] = 1000;
  params[2][2] = -10000;
  params[2][3] = 200000;
  params[3][0] = -100;
  params[3][1] = 10;
}

void getResults10Servo(double** params) {
  // LURTN
  params[0][0] = 1.2942268654268088e+002;
  params[0][1] = 1.6668375402407262e+000;
  // LULNG
  params[1][0] = 5.5452380952380930e+002;
  params[1][1] = -2.6484593837534930e+000;
  params[1][2] = 1.1929477673422232e-002;
  params[1][3] = -2.7138883234954693e-005;
  // LLRTN
  params[2][0] = 1.5442914556378040e+002;
  params[2][1] = 1.5882527835305206e+000;
  // LLLNG
  params[3][0] = 1.3666666666666668e+002;
  params[3][1] = 2.8253968253968250e+000;
  params[3][2] = -1.3016971494480146e-002;
  params[3][3] = 3.0757400999615536e-005;
  // RLLNG
  params[4][0] = 5.7880952380952260e+002;
  params[4][1] = -2.3641456582632174e+000;
  params[4][2] = 9.3590377327392710e-003;
  params[4][3] = -2.1711106587961670e-005;
  // RLRTN
  params[5][0] = 1.3774938998134064e+002;
  params[5][1] = 1.5490885603559636e+000;
  // RULNG
  params[6][0] = 1.8559523809523685e+002;
  params[6][1] = 2.1031746031746907e+000;
  params[6][2] = -7.4147305981224840e-003;
  params[6][3] = 1.8092588823305492e-005;
  // RURTN
  params[7][0] = 1.6024944124341286e+002;
  params[7][1] = 1.6079886813344540e+000;
  // GALNG
  params[8][0] = 5.3464285714285590e+002;
  params[8][1] = -2.8109243697478114e+000;
  params[8][2] = 1.3346515076618000e-002;
  params[8][3] = -3.2566659881943620e-005;
  // GARTN
  params[9][0] = 1.4526246180975622e+002;
  params[9][1] = 1.5686194098710244e+000;
}

test(test_4_Servos_polynomials_of_different_order) {

  prfServoImplMockUnit16 impl;
  // Servo 0: order 1, 100 + 10*x
  // Servo 1: order 2, 100 + 10*x + 5*x*x
  // Servo 2: order 3, 100 + 10*x + 5*x*x + 2*x*x*x
  // Servo 3: order 0, 80
  impl.getStub = &getResults4Servo;
  
  prfServo<uint8_t, uint8_t, uint16_t, double> fourServos(&impl, 0x39);

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

test(test_8_Servos_same_polynomial) {
  prfServoImplMockUnit16 impl;
  // Servo 0-7: order 1, 100 + 10*x
  impl.getStub = &getResults8Servo;

  prfServo<uint16_t, uint8_t, uint16_t, double> eightServos(&impl, 0x5555);

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

test(test_16_Servos_same_polynomial) {
  prfServoImplMockUnit16 impl;
  // Servo 0-15: order 1, 100 + 10*x
  impl.getStub = &getResults16Servo;

  prfServo<uint32_t, uint8_t, uint16_t, double> sixteenServos(&impl, 0x55555555);

  int freeMemBeforeHeapAlloc = freeMemory();
  sixteenServos.begin();

  for (int servo = 0; servo < 16; servo++)
  {
    for (int valIn = 0; valIn <= 255; valIn += 5) {
      impl.writeStubNum = 0;
      impl.writeStubVal = 0;
      sixteenServos.write(servo, valIn);
      assertEqual(servo, impl.writeStubNum);
      assertEqual(100 + 10 * valIn, impl.writeStubVal);
    }
  }

  sixteenServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

test(test_4_Servos_float_in_int32_out_float_math) {

  prfServoImplMockInt32 impl;
  // Servo 0: order 1, 100 + 1000*x
  // Servo 1: order 2, 100 + 1000*x - 10000*x*x
  // Servo 2: order 3, 100 + 1000*x - 10000*x*x + 200000*x*x*x
  // Servo 3: order 1, -100 + 10*x
  impl.getStub = &getResults4Servos_SignedOutcome;

  prfServo<uint8_t, float, int32_t> fourServos(&impl, 0x79);

  int freeMemBeforeHeapAlloc = freeMemory();
  fourServos.begin();

  // Servo 0
  for (float f = -1; f < 1; f += 0.05) {
    impl.writeStubVal = 0;
    fourServos.write(0, f);
    assertEqual((int32_t)(round(100 + 1000*f)), impl.writeStubVal);
  }

  // Servo 1
  for (float f = -1; f < 1; f += 0.05) {
    impl.writeStubVal = 0;
    fourServos.write(1, f);
    assertEqual((int32_t)(round(100 + 1000*f - 10000*f*f)), impl.writeStubVal);
  }

  // Servo 2
  for (float f = -1; f < 1; f += 0.05) {
    impl.writeStubVal = 0;
    fourServos.write(2, f);
    assertEqual((int32_t)(round(100 + 1000*f - 10000*f*f + 200000*f*f*f)), impl.writeStubVal);
  }

  // Servo 4
  for (float f = -1; f < 1; f += 0.05) {
    impl.writeStubVal = 0;
    fourServos.write(3, f);
    assertEqual((int32_t)(round(-100 + 10 * f)), impl.writeStubVal);
  }
 
  fourServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

test(test_4_Servos_calculate_polynomials_of_different_order) {

  prfServoImplMockUnit16 impl;

  // Servo 4: order 0 (not used; ignored)
  impl.getStub = &getResults4Servo;

  //https://arachnoid.com/polysolve/
  //    0 210
  //   25 245
  //   51 275
  //   76 305
  //  102 335
  //  127 355
  //  153 380
  //  178 395
  //  204 415
  //  229 440
  //  255 465
  const uint8_t posVals[11] = {0, 25, 51, 76, 102, 127, 153, 178, 204, 229, 255 };
  uint16_t servoVals[11] = { 210, 245, 275, 305, 335, 355, 380, 395, 415, 440, 465 };
    
  prfServo<uint8_t, uint8_t, uint16_t, double> fourServos(&impl, 0x39);

  int freeMemBeforeHeapAlloc = freeMemory();
  fourServos.begin();

  // Servo 0: order 1, 100 + 10*x
  impl.putStub = 0;
  fourServos.calcParams(0, 11, posVals, servoVals);
  fourServos.put();
  assertEqual((int32_t)(2.2476862266620912e+002 * 1000), (int32_t)(impl.putStub[0][0] * 1000));
  assertEqual((int32_t)(9.6253225047978540e-001 * 1000), (int32_t)(impl.putStub[0][1] * 1000));

  // Servo 1: order 2, 100 + 10*x + 5*x*x
  impl.putStub = 0;
  fourServos.calcParams(1, 11, posVals, servoVals);
  fourServos.put();
  assertEqual((int32_t)(2.1355799352017670e+002 * 1000), (int32_t)(impl.putStub[1][0] * 1000));
  assertEqual((int32_t)(1.2564787305597670e+000 * 1000), (int32_t)(impl.putStub[1][1] * 1000));
  assertEqual((int32_t)(-1.1541714448985531e-003 * 1000), (int32_t)(impl.putStub[1][2] * 1000));

  // Servo 3: order 3, 100 + 10*x + 5*x*x + 2*x*x*x
  impl.putStub = 0;
  fourServos.calcParams(2, 11, posVals, servoVals);
  fourServos.put();
  assertEqual((int32_t)(2.0865618530477138e+002 * 10), (int32_t)(impl.putStub[2][0] * 10));
  assertEqual((int32_t)(1.5628575572799290e+000 * 1000), (int32_t)(impl.putStub[2][1] * 1000));
  assertEqual((int32_t)(-4.3070790704413160e-003 * 1000), (int32_t)(impl.putStub[2][2] * 1000));
  assertEqual((int32_t)(8.2463387909067770e-006 * 1000), (int32_t)(impl.putStub[2][3] * 1000));

  fourServos.end();
  assertEqual(freeMemBeforeHeapAlloc, freeMemory());
}

test(test_10_Servos_process_time) {
  prfServoImplMockUnit16 impl;
  // Servo 0-15: order 1, 100 + 10*x
  impl.getStub = &getResults10Servo;

  //0x0777DD = 0000 01 11 01 11 11 01 11 01
  prfServo<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD);

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

  Serial.println("prfServo");
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
