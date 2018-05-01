/* prfServo.h - polynomial regression fit Servo (prfServo) Arduino Library 
 * Copyright (C) 2018 by Stefan Grimm
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with the prfServo Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _PRFSERVO_H
#define _PRFSERVO_H

#include "Arduino.h"
#include "PolynomialRegression.h"

template<typename TINT = uint16_t, typename TMATH = float>
class prfServoImplBase {
  public:
  prfServoImplBase() {}
  virtual void begin() = 0;
  virtual void end() {};
  virtual void write(uint8_t num, TINT servoVal) = 0;
  virtual void get(TMATH** params) const {}
  virtual void put(TMATH** params) {}
  private:
  prfServoImplBase(const prfServoImplBase& s);
  prfServoImplBase& operator=(const prfServoImplBase& s);
};

template<typename TORD = uint32_t, typename TEXT = float, typename TINT = uint16_t, typename TMATH = float>
class prfServo {
  
  public:
  prfServo(prfServoImplBase<TINT>* impl, TORD orderDesc) : _pImpl(impl), _orderDesc(orderDesc) {
  }
  ~prfServo() {
    _dispose();
  }
  
  void begin() {
    _params = new TMATH*[N] ();
    for(int i = 0; i < N; i++) {
      int ord = _order(i);
      _params[i] = new TMATH[ord + 1] ();
    }
    _pImpl->begin();
    _pImpl->get(_params);
  }
  
  void end() {
    if (!_isDisposed()) {
      _pImpl->put(_params);
      _pImpl->end();
     _dispose();
    }
  }
  
  void calcParams(uint8_t num, int numSamples, const TEXT* positionValues, const TINT* servoValues) {
    
    // can be omitted with explicit template instantiation if values are float already.
    float x[numSamples];
    float y[numSamples];
    for (int n=0; n<numSamples; n++) {
      x[n] = positionValues[n];
      y[n] = servoValues[n];
    }
    int ord = _order(num);
    if (ord > 0) {
      float coffs[ord + 1] = {0};
      PolynomialRegression::fitIt(numSamples, x, y, ord, coffs);
      
      for (int n=0; n<=ord; n++) {
        _params[num][n] = coffs[n];
      }
    }
  }
  
  void put() {
    _pImpl->put(_params);
  }
  
  void get() {
    _pImpl->get(_params);
  }
  
  void write(uint8_t num, TEXT pos) {
    
    int ord = _order(num);
    switch (ord) {
      default:
      case 0: break;
      case 1: {
        TINT servoVal = (TINT)(_params[num][0] + _params[num][1] * pos);
        _pImpl->write(num, servoVal);
        break;
      }        
      case 2: {
        TINT servoVal = (TINT)(_params[num][0] + _params[num][1] * pos + _params[num][2] * pow(pos, 2));
        _pImpl->write(num, servoVal);
        break;
      }      
      case 3: {
        TINT servoVal = (TINT)(_params[num][0] + _params[num][1] * pos + _params[num][2] * pow(pos, 2) + _params[num][3] * pow(pos, 3));
        _pImpl->write(num, servoVal);
        break;
      }      
    }
  }
  
  private:  
  prfServo(const prfServo& s);
  prfServo& operator=(const prfServo& s);
  void _dispose() {
    if (_params != 0) {
      for(int i = 0; i < N; ++i) {
        delete[] (_params[i]);
      }
      delete[] _params;
    }
  }  
  bool _isDisposed() const { return _params == 0; }
  int _order(int num) const { return ( (TORD)(_orderDesc << (2 * (N-1 - num)))) >> (2 * (N-1)); }
  prfServoImplBase<TINT>* _pImpl;
  TMATH** _params;
  const TORD _orderDesc;
  static const uint8_t N = sizeof(TORD) * 4;
  
};

template<typename T>
class prfDemoImplServoShield :  public prfServoImplBase<> {
  public:
  void begin() {
    pwm.begin();
    pwm.setPWMFreq(60);
  }

  void get(float** params) const {
    for (int n=0; n<16; n++) {
      params[n][0] = 150;
      params[n][1] = 450;
    }
  }
  
  void write(uint8_t num, uint16_t servoVal) {
    pwm.setPWM(num, 0, servoVal);
  }
  
  private:
  T pwm;
};

template<typename T>
class prfDemoImplServoLib :  public prfServoImplBase<uint8_t> {
  public:
  void begin() {
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
  }

  void get(float** params) const {
    params[0][0] = 0;
    params[0][1] = 180;
    params[1][0] = 0;
    params[1][1] = 180;
  }
  
  void write(uint8_t num, uint8_t servoVal) {
    if (num == 0) {
      servo.attach(9);
    } else {
      servo.attach(10);
    }    
    servo.write(servoVal);
    delay(15);
  }
  
  private:
  T servo;
};

#endif

