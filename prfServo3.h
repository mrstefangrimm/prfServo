/* prfServo3.h - polynomial regression fit Servo (prfServo) Arduino Library 
 * Copyright (C) 2019 by Stefan Grimm
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

#ifndef _PRFSERVO3_H
#define _PRFSERVO3_H

#include "Arduino.h"

template<typename TOUT = uint16_t, typename TMATH = float>
class prfServo3ImplBase {
  public:
  prfServo3ImplBase() {}
  virtual void begin() = 0;
  virtual void end() {};
  virtual void write(uint8_t num, TOUT servoVal) = 0;
  virtual void get(TMATH** params, TMATH** dirOffsets, TMATH** disOffsets) const {}
  private:
  prfServo3ImplBase(const prfServo3ImplBase& s);
  prfServo3ImplBase& operator=(const prfServo3ImplBase& s);
};

template<typename TORD = uint32_t, typename TIN = float, typename TOUT = uint16_t, typename TMATH = float>
class prfServo3 {
  
  public:
  prfServo3(prfServo3ImplBase<TOUT, TMATH>* impl, TORD orderDesc, TORD orderDescOffsetDirection, TORD orderDescOffsetTravelDistance)
    : _pImpl(impl), _orderDesc(orderDesc), _orderDescOffDir(orderDescOffsetDirection), _orderDescOffDis(orderDescOffsetTravelDistance) {
    memset(_currentPosIn, 0, N * sizeof(TIN));
  }
  ~prfServo3() {
    _dispose();
  }
  
  void begin() {
    _params = new TMATH*[N] ();
    for(int i = 0; i < N; i++) {
      int ord = _order(i);
      _params[i] = new TMATH[ord + 1] ();
    }
    _dirOffsets = new TMATH*[N]();
    for (int i = 0; i < N; i++) {
      int ord = _orderOffsetDirection(i);
      _dirOffsets[i] = new TMATH[ord + 1]();
    }
    _disOffsets = new TMATH*[N]();
    for (int i = 0; i < N; i++) {
      int ord = _orderOffsetTravelDistance(i);
      _disOffsets[i] = new TMATH[ord + 1]();
    }
    _pImpl->begin();
    _pImpl->get(_params, _dirOffsets, _disOffsets);
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
    TIN travelDistance = pos - _currentPosIn[num];
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
      switch (_orderOffsetDirection(num)) {
        default: return;
        case 0:
          servoVal += _dirOffsets[num][0];
          break;
        case 1:
          servoVal += _dirOffsets[num][0] + _dirOffsets[num][1] * pos;
          break;
        case 2:
          servoVal += _dirOffsets[num][0] + _dirOffsets[num][1] * pos + _dirOffsets[num][2] * pow(pos, 2);
          break;
        case 3:
          servoVal += _dirOffsets[num][0] + _dirOffsets[num][1] * pos + _dirOffsets[num][2] * pow(pos, 2) + _dirOffsets[num][3] * pow(pos, 3);
          break;
      }
    }
    switch (_orderOffsetTravelDistance(num)) {
      default: return;
      case 0:
      servoVal += _disOffsets[num][0];
      break;
      case 1:
      servoVal += _disOffsets[num][0] + _disOffsets[num][1] * pos;
      break;
      case 2:
      servoVal += _disOffsets[num][0] + _disOffsets[num][1] * pos + _disOffsets[num][2] * pow(pos, 2);
      break;
      case 3:
      servoVal += _disOffsets[num][0] + _disOffsets[num][1] * pos + _disOffsets[num][2] * pow(pos, 2) + _disOffsets[num][3] * pow(pos, 3);
      break;
    }
    _currentPosIn[num] = pos;
    _pImpl->write(num, (TOUT)round(servoVal));
  }
  
  private:  
  prfServo3(const prfServo3& s);
  prfServo3& operator=(const prfServo3& s);
  void _dispose() {
    if (_params != 0) {
      for (int i = 0; i < N; ++i) {
        delete(_params[i]);
      }
      delete(_params);
      _params = 0;
    }
    if (_dirOffsets != 0) {
      for (int i = 0; i < N; ++i) {
        delete(_dirOffsets[i]);
      }
      delete(_dirOffsets);
      _dirOffsets = 0;
    }
    if (_disOffsets != 0) {
      for (int i = 0; i < N; ++i) {
        delete(_disOffsets[i]);
      }
      delete(_disOffsets);
      _disOffsets = 0;
    }
  }
  bool _isDisposed() const { return _params == 0; }
  int _order(int num) const { return ( (TORD)(_orderDesc << (2 * (N-1 - num)))) >> (2 * (N-1)); }
  int _orderOffsetDirection(int num) const { return ((TORD)(_orderDescOffDir << (2 * (N - 1 - num)))) >> (2 * (N - 1)); }
  int _orderOffsetTravelDistance(int num) const { return ((TORD)(_orderDescOffDis << (2 * (N - 1 - num)))) >> (2 * (N - 1)); }
  prfServo3ImplBase<TOUT, TMATH>* _pImpl;
  TMATH** _params;
  TMATH** _dirOffsets;
  TMATH** _disOffsets;
  const TORD _orderDesc;
  const TORD _orderDescOffDir;
  const TORD _orderDescOffDis;
  static const uint8_t N = sizeof(TORD) * 4;
  TIN _currentPosIn[N];
};

#endif
