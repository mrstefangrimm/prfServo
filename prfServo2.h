/* prfServo2.h - polynomial regression fit Servo (prfServo) Arduino Library 
 * Copyright (C) 2019 - 2021 by Stefan Grimm
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the prfServo Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _PRFSERVO2_H
#define _PRFSERVO2_H

#include "Arduino.h"

template<typename TOUT = uint16_t, typename TMATH = float>
class prfServo2ImplBase {
  public:
  prfServo2ImplBase() {}
  virtual void begin() = 0;
  virtual void end() {};
  virtual void write(uint8_t num, TOUT servoVal) = 0;
  virtual void get(TMATH** params, TMATH** backlashs) const {}
  private:
  prfServo2ImplBase(const prfServo2ImplBase& s);
  prfServo2ImplBase& operator=(const prfServo2ImplBase& s);
};

template<typename TORD = uint32_t, typename TIN = float, typename TOUT = uint16_t, typename TMATH = float>
class prfServo2 {
  
  public:
  prfServo2(prfServo2ImplBase<TOUT, TMATH>* impl, TORD orderDesc, TORD orderDescBacklash)
    : _pImpl(impl), _orderDesc(orderDesc), _orderDescBacklash(orderDescBacklash) {
    memset(_currentPosIn, 0, N * sizeof(TIN));
  }
  ~prfServo2() {
    _dispose();
  }
  
  void begin() {
    _params = new TMATH*[N] ();
    for(int i = 0; i < N; i++) {
      int ord = _order(i);
      _params[i] = new TMATH[ord + 1] ();
    }
    _backlashes = new TMATH*[N]();
    for (int i = 0; i < N; i++) {
      int ord2 = _orderBacklash(i);
      _backlashes[i] = new TMATH[ord2 + 1]();
    }
    _pImpl->begin();
    _pImpl->get(_params, _backlashes);
  }
  
  void end() {
    if (!_isDisposed()) {
      _pImpl->end();
     _dispose();
    }
  }
    
  void get() {
    _pImpl->get(_params);
  }
  
  void write(uint8_t num, TIN pos) {

    bool movesBack = pos < _currentPosIn[num];

    TMATH servoVal = _params[num][0];
    switch (_order(num)) {
      default: return;
      case 0: break;
      case 1:
        servoVal = _params[num][0] + _params[num][1] * pos;
        break;
      case 2:
        servoVal = _params[num][0] + _params[num][1] * pos + _params[num][2] * pow(pos, 2);
        break;
      case 3:
        servoVal = _params[num][0] + _params[num][1] * pos + _params[num][2] * pow(pos, 2) + _params[num][3] * pow(pos, 3);
        break;
    }

    if (movesBack)
    {
      switch (_orderBacklash(num)) {
        default: return;
        case 0:
          servoVal += _backlashes[num][0];
          break;
        case 1:
          servoVal += _backlashes[num][0] + _backlashes[num][1] * pos;
          break;
        case 2:
          servoVal += _backlashes[num][0] + _backlashes[num][1] * pos + _backlashes[num][2] * pow(pos, 2);
          break;
        case 3:
          servoVal += _backlashes[num][0] + _backlashes[num][1] * pos + _backlashes[num][2] * pow(pos, 2) + _backlashes[num][3] * pow(pos, 3);
          break;
      }
    }

    _currentPosIn[num] = pos;
    _pImpl->write(num, (TOUT)round(servoVal));
  }
  
  private:  
  prfServo2(const prfServo2& s);
  prfServo2& operator=(const prfServo2& s);
  void _dispose() {
    if (_params != 0) {
      for (int i = 0; i < N; ++i) {
        delete(_params[i]);
      }
      delete(_params);
      _params = 0;
    }
    if (_backlashes != 0) {
      for (int i = 0; i < N; ++i) {
        delete(_backlashes[i]);
      }
      delete(_backlashes);
      _backlashes = 0;
    }
  }
  bool _isDisposed() const { return _params == 0; }
  int _order(int num) const { return ( (TORD)(_orderDesc << (2 * (N-1 - num)))) >> (2 * (N-1)); }
  int _orderBacklash(int num) const { return ((TORD)(_orderDescBacklash << (2 * (N - 1 - num)))) >> (2 * (N - 1)); }
  prfServo2ImplBase<TOUT, TMATH>* _pImpl;
  TMATH** _params;
  TMATH** _backlashes;
  const TORD _orderDesc;
  const TORD _orderDescBacklash;
  static const uint8_t N = sizeof(TORD) * 4;
  TIN _currentPosIn[N];
};

#endif

