# prfServo

A Arduino library to synchronously move multiple servo motors. A polynomial transformation up to a degree of 3 transforms the used target position to the value written to the servo. The prfServo library is a wrapper for existing servo libraries such as *[Servo](https://www.arduino.cc/en/Reference/Servo)* or the *[Adafruit Servo Shield](https://www.adafruit.com/product/1411)*.

## Motivation
Each servo motor you buy has its own characteristics. prfServo allows you to do a software calibration and accurately and synchronously move multiple servo motors.

The table below shows the measured pulse lengths of four servos I own:

| # | 0 &deg; | 180 &deg; |
| - | ------- | --------- |
| 0 | 575 µs  | 2467 µs   |
|  1  |  687 µs | 2489 µs |
| 2 | 617 µs | 2370 µs |
| 3 | 713 µs | 2538 µs |

The goal is to use 0&deg; to 180&deg; in the main loop, even though different pulse length values are written  to each servo.
```c++
void loop() {
  for (int angleDeg = 0; angleDeg < 180; angleDeg += 1) {
    servoLib.write(0, angleDeg); servoLib.write(1, angleDeg);
    servoLib.write(2, angleDeg); servoLib.write(3, angleDeg);
    delay(10);
  }
  for (int angleDeg = 180; angleDeg > 0; angleDeg -= 1) {
    servoLib.write(0, angleDeg); servoLib.write(1, angleDeg);
    servoLib.write(2, angleDeg); servoLib.write(3, angleDeg);
    delay(10);
  }
}
```

## Getting Started

This is the rest of the example from the section above. Copy the latest release to the Arduino library folder and follow the installation instructions.

Implement the **`get()`** method: The object `servoLib` has to be set up with the correct polynomial for each servo.
The polynomials are: y<sub>0</sub> = 575 + 10.5x<sub>0</sub>, y<sub>1</sub> = 687 + 10x<sub>1</sub>, y<sub>2</sub> = 617 + 9.74x<sub>2</sub>, y<sub>3</sub> = 713 + 10.1x<sub>3</sub>

Implement the **`begin()`** and **`write()`** methods: The example uses the Arduino Servo library. Each servo is directly attached to a pin on the Arduino.

```c++
#include <Servo.h>
#include "prfServo.h"

class ServoPolyFit : public prfServoImplBase<uint16_t> {
public:
  void get(float** params) const {   
    params[0][0] = 575; params[0][1] = 10.5;
    params[1][0] = 687; params[1][1] = 10;
    params[2][0] = 617; params[2][1] = 9.74;
    params[3][0] = 713; params[3][1] = 10.1;
  }
  void begin() {
    pinMode(7, OUTPUT); pinMode(8, OUTPUT);
    pinMode(9, OUTPUT); pinMode(10, OUTPUT);
    _servo0.attach(7); _servo1.attach(8);
    _servo2.attach(9); _servo3.attach(10);
  }  
  void write(uint8_t num, uint16_t servoVal) {
    switch (num) {
      default: break;
      case 0: _servo0.write(servoVal); break;
      case 1: _servo1.write(servoVal); break;
      case 2: _servo2.write(servoVal); break;
      case 3: _servo3.write(servoVal); break;    }
  }
private:
  Servo _servo0, _servo1, _servo2, _servo3;
};
```

`ServoPolyFit` is instantiated and the `servoLib` object is created.

To save memory, the template parameters are chosen with care. The first template parameter is an `uint8_t` which allows 4 servos. The second template parameter is an `uint8_t` because in the main loop, values between 0 and 180 are used. It would be possible to use a `float `and make smaller steps in the main loop, but this costs memory. The third template parameter is the type that is used to write the values to the Servo library. The values are between 575 and 2538 and therefore an `uint16_t` is required. 

The degree of each polynomial is given to the constructor as an argument. Each polynomial has 2 bits to define its degree: `0b01010101` => 4 times 1st degree => 4 times a + b*x

```c++
ServoPolyFit impl;
prfServo<uint8_t, uint8_t, uint16_t> servoLib(&impl, 0b01010101);

void setup() {
  servoLib.begin();
}
```

## Features

- Synchronicity
- Accuracy
- Memory efficiency

## Examples

1. Examples in the examples folder
1. [examples/ServoShield_LnRActuator_Demo](https://youtu.be/CnMcMh8CgUc) as video. Repeatability is not an issue. For longitudinal motion millimeters are used and for rotary motion degrees are used to position the pointer. The example instantiates the class `prfServo2`which uses two polynomials per servo and cancels the mechanical play
1. [examples/ServoShield_PencilLeadDrive](https://youtu.be/KJdUGMOCTKk) as video. 4 properly calibrated and adjusted servos move a pencil lead around that is fixed in between. The *pencil lead drive* demo project uses polynomials with a degree of 3, determined with a five point calibration. The example instantiates the class `prfServo2` which uses two polynomials per servo and cancels the mechanical play

## Installation
1. Download the source code archive from *[github](https://github.com/mrstefangrimm/prfServo/releases)*
1. Unzip it to your Arduino/libraries folder
1. Remove the version number from the folder name
1. Include either `prfServo.h` or `prfServo2.h` in your Arduino sketch
1. Inherit a class from `prfServoImplBase` resp. `prfServo2ImplBase`. This class wraps the existing servo library
1. Implement `get()`, `begin()` and `write()`. `get()` defines the polynomial parameters and `write()` writes the transformed values to the wrapped servo library
1. Instantiate an object of the type `prfServo` resp. `prfServo2`
1. Use your prfServo object to (indirectly) write values to the servo library

## API

###  prfServo and prfServo2

Whereas the class `prfServo` is stateless and uses a linear transformation, the class `prfServo2` is nonlinear and stateful. It lets you compensate the mechanical play. If direction changes, an offset polynomial is added.

**prfServo**

![equation](http://bit.ly/2GfOn43)



**prfServo2**

![equation](http://bit.ly/2Z0SWq7)



### Template parameters

`TORD` : Type of the attribute to store the polynomial order. Depends on how many Servos you use: ` uint8_t` : 1 - 4, `uint16_t` : 1 - 8, `uint32_t` : 1 - 16

`TIN`: Type of the used target values. Choose `float` if your target position shall be e.g. 1.3 [mm/inch/...]. By choosing `uint8_t` you save memory and still have 256 points. 

`TOUT`: Type of the values that control the Servo. The Arduino *[Servo](https://www.arduino.cc/en/Reference/Servo)* library allows you to write degrees (0-180), but there is a mapping behind that you do not want to use anymore. Values above 540 are the pulse length in µs.

`TMATH`: Type for the polynomial fitting and the parameters. Has to be a floating-point number.

### Classes
`template<typename TOUT, typename TMATH> class prfServoImplBase` : 
Derive from this class an write your own implementation. Make sure `TOUT` and `TMATH` have the same data type as the ones used for `prfServo`.

`template<typename TORD, typename TIN, typename TOUT, typename TMATH> class prfServo` : 
Instantiate an object of this an use it as your Servo library.

`template<typename TOUT, typename TMATH> class prfServo2ImplBase` : 
Derive from this class an write your own implementation. Make sure `TOUT` and `TMATH` have the same data type as the ones used for `prfServo`.

`template<typename TORD, typename TIN, typename TOUT, typename TMATH> class prfServo2` :
Instantiate an object of this an use it as your Servo library.

## Tests

### Unit Tests

The unit tests use the [ArduinoUnit](https://github.com/mmurdoch/arduinounit) framework.

### Memory Usage Test

`prfServo<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD);`

Memory usage: 210 Bytes

`prfServo2<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD, 0x00000000);`

Memory usage: 340 Bytes

### Processing Time Test

`prfServo<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD);`

Process time (10 writes): 2.53 ms

`prfServo2<uint32_t, uint8_t, uint16_t, double> tenServos(&impl, 0x0777DD, 0x00000000);`

Process time (10 writes): 2.75 ms

## License
This Library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

## Project History

prfServo was written in 2018 for the *[LnR Actuator](https://www.instructables.com/id/Linear-and-Rotation-Actuator/)* for which the *[map function](https://www.arduino.cc/reference/en/language/functions/math/map/)* is not sufficient for the transformation of the Servo's rotary motion to the shaft's linear motion.

In 2019, prfServo2 was added to not only support a correct transformation but also compensate the mechanical play.

## Change History

### 0.0.1.2
- Update documentation and examples

### 0.0.1.0 
- Initial Version
