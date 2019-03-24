# prfServo
Arduino Servo library for non-linear movement of Servo motors. A polynomial transformation up to order 3 enables you to separate the target position and the value written to the Servo. Up to 16 Servos can be controlled. This library is wrapper for existing Servo libraries such as "Servo.h" and the Adafruit Servo Shield.

## Project History
At some point in my project I found out the the shafts that I was moving back and forth with my Servo motors did not have the same stroke length and din not move not linearly. What I needed was a function between the target position and the value written to the Servo; a polynomial.

## Examples
Please have a look at the examples folder for several examples.

## Types
### Template parameters
TORD : Type of the attribute to store the polynomial order. Depends on how many Servos you use: uint8_t : 1 - 4, uint16_t : 1 - 8, uint32_t : 1 - 16

TIN: Type of the internally used (target) values. Choose float if your target position shall be e.g. 1.3 [mm/inch/..]. By choosing uint8_t you will save memory and still have 256 points. 

TOUT: Type of the values that control the Servo. PWM values are in the range of an uint16_t. Servo.h allows you to write degrees (0-180), but there is a mapping behind that you do not want to use anymore.

TMATH: Type for the polynomial fitting and the parameters. Has to be a floating-point number.

### Classes
template<typename TOUT, typename TMATH> class prfServoImplBase : Derive from this class an write your own implementation. Make sure TOUT and TMATH are the same data types as used for prfServo.

template<typename TORD, typename TIN, typename TOUT, typename TMATH> class prfServo : Instantiate an object of this an use it as your Servo library.
