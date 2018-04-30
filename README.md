# prfServo
Arduino Servo library for non-linear movement of Servo motors. A polynonial transformation up to order 3 enables you to separate the target position and the value written to the Servo. Up to 16 Servos can be controlled. This library is wrapper for existingServo libraries such as "Servo.h" and the Adafruit Servo Shield.

## Project History
At some point in my project I found out the the shafts that I was moving back and forth with my Servo motors did not have the same stroke length and din not move not linearly.What I needed was a function between the target position and the value written to the Servo; a polynomial.

## Examples
Please have a look at the examples folder for several examples.

## Types
### Template parameter
TORD : Type of the attribute to store the polynonial order. Depends on how many Servos you use: uint8_t : 1 - 4, uint16_t 1 - 8, uint32_t : 1 - 16

TEXT : Type of the exernal (target) values. Choose float if your target position shall be e.g 1.3 [mm/inch/..]. By choosing uint8_t you will save memory and still have 256 points. 

TINT : Type of the internal (Servo) values. PWM values are in the range of an uint16_t. Servo.h allows you to write degrees (0-180), but there is a mapping behind that you do not want to use anymore.

TMATH: Type for the polynomial fitting and the parameters. Has to be a floating point number.

template<typename TINT, typename TMATH> class prfServoImplBase : Derive from this class an write your own implementation. Make sure TINT and TMATH are the same data types as used for prfServo.

template<typename TORD, typename TEXT, typename TINT, typename TMATH> class prfServo : Instantiate an object of this an use it as your Servo library.
