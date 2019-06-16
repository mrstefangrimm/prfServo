# prfServo
A stateless wrapper to control Servo motors. A polynomial transformation up to order 3 separates the internal target position and the value written to the Servo. Up to 16 Servos can be controlled. This library is wrapper for existing Servo libraries such as *[Servo](https://www.arduino.cc/en/Reference/Servo)* or the *[Adafruit Servo Shield](https://www.adafruit.com/product/1411)*.

y = a + bx + cx^2 + dx^3

## prfServo2
Whereas prfServo uses a linear transformation prfServo2 is nonlinear and stateful. It compensates the mechanical play. If the direction changes, an offset polynomial is added.

 y' =  

- a + bx' + cx'^2 + dx'^3, if x' > x and y' > y
- a + bx' + cx'^2 + dx'^3 + e + fx' + gx'^2 +hx'^3, if x' < x and y' < y

## prfServo3
prfServo3 is nonlinear and stateful. It compensates the mechanical play.  If the direction changes, an offset polynomial is added. It compensates inaccuracy due to friction. A polynomial adds an offset based on the difference between the new and the old target value.

## Project History
prfServo was written in 2018 for the *[LnR Actuator](https://www.instructables.com/id/Linear-and-Rotation-Actuator/)* for which the *[map function](https://www.arduino.cc/reference/en/language/functions/math/map/)* is not sufficient for the transformation of the Servo's (rotational) motion to the shaft's linear motion.

In 2019, prfServo2 and prfServo3 were added to not only support a correct transformation but also compensate the mechanical play (prfServo2) and in addition compensate friction or any other effect that has to do with the travel distance (prfServo3).

## Installation
1. Download the latest release from *[github](https://github.com/mrstefangrimm/prfServo/releases)*
2. Unzip to the Arduino/libraries folder

## Examples
Have a look at the examples folder for several examples. A 
[video on youtube](https://youtu.be/CnMcMh8CgUc)
 illustrates how the mechanical play is compensated.

### Memory Usage Examples
`prfServo<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD);`

Memory usage: 210 Bytes

`prfServo2<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD, 0x00000000);`

Memory usage: 340 Bytes

`prfServo3<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD, 0x00000000, 0x00000000);`

Memory usage: 470 Bytes

### Processing Time Examples
`prfServo<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD);`

Process time (10 writes): 2.53 ms

`prfServo2<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD, 0x00000000);`

Process time (10 writes): 2.75 ms

`prfServo3<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD, 0x00000000, 0x00000000);`

Process time: 3.09 ms

## Types
### Template parameters
`TORD` : Type of the attribute to store the polynomial order. Depends on how many Servos you use: `uint8_t` : 1 - 4, `uint16_t` : 1 - 8, `uint32_t` : 1 - 16

`TIN`: Type of the internally used (target) values. Choose `float` if your internal target position shall be e.g. 1.3 [mm/inch/...]. By choosing `uint8_t` you save memory and still have 256 points. 

`TOUT`: Type of the values that control the Servo. PWM values are in the range of an `uint16_t`. *[Servo](https://www.arduino.cc/en/Reference/Servo)* allows you to write degrees (0-180), but there is a mapping behind that you do not want to use anymore.

`TMATH`: Type for the polynomial fitting and the parameters. Has to be a floating-point number.

### Classes
`template<typename TOUT, typename TMATH> class prfServoImplBase` : 
Derive from this class an write your own implementation. Make sure `TOUT` and `TMATH` have the same data type as the ones used for `prfServo`.

`template<typename TORD, typename TIN, typename TOUT, typename TMATH> class prfServo` : 
Instantiate an object of this an use it as your Servo library.

`template<typename TOUT, typename TMATH> class prfServo2ImplBase` : 
Derive from this class an write your own implementation. Make sure `TOUT` and `TMATH` have the same data type as the ones used for `prfServo2`.

`template<typename TORD, typename TIN, typename TOUT, typename TMATH> class prfServo2` :
Instantiate an object of this an use it as your Servo library.

`template<typename TOUT, typename TMATH> class prfServo3ImplBase` : 
Derive from this class an write your own implementation. Make sure `TOUT` and `TMATH` have the same data type as the ones used for `prfServo3`.

`template<typename TORD, typename TIN, typename TOUT, typename TMATH> class prfServo3` :
Instantiate an object of this an use it as your Servo library.

## License
This Library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.


## Change History
### 0.0.1.1
- Update documentation and examples

### 0.0.1.0 
- Initial version
