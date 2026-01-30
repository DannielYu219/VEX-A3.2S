/**
 * @file PID.cpp
 * @brief Implementation of PID controller class
 * 
 * This file implements a PID (Proportional-Integral-Derivative) controller
 * with anti-windup and target arrival detection features.
 */

#include "PID.h"

#include "math-tools.h"

PID::PID()
    : firstTime(true), arrived(false), IMax(20), IRange(50), jumpTime(50) {
  myTimer.reset();
}

void PID::setFirstTime() { firstTime = true; }

void PID::setCoefficient(float _kp, float _ki, float _kd) {
  kp = _kp;
  ki = _ki;
  kd = _kd;
}
void PID::setTarget(float _target) { target = _target; }
void PID::setIMax(float _IMax) { IMax = _IMax; }
void PID::setIRange(float _IRange) { IRange = _IRange; }
void PID::setErrorTolerance(float _errorTol) { errorTol = _errorTol; }
void PID::setDTolerance(float _DTol) { DTol = _DTol; }
void PID::setJumpTime(float _jumpTime) { jumpTime = _jumpTime; }
bool PID::targetArrived() { return arrived; }
float PID::getOutput() { return output; }

void PID::update(float input) {
  errorCrt = target - input;
  P = kp * errorCrt;
  if (firstTime) {
    firstTime = false;
    errorPrev = errorCrt;
    errorInt = 0;
  }
  errorDev = errorCrt - errorPrev;
  errorPrev = errorCrt;
  D = kd * errorDev;
  if (fabs(P) >= IRange) {
    errorInt *= 0.95;
  } else {
    errorInt += errorCrt;
    if (fabs(errorInt) * ki > IMax)
      errorInt = sign(errorInt) * IMax / ki;
  }
  if (sign(errorInt) != sign(errorCrt) && fabs(errorInt) > fabs(errorCrt))
    errorInt = 0;
  I = ki * errorInt;
  if (fabs(errorCrt) <= errorTol &&
      fabs(D) <= DTol) {
    if (myTimer.getTime() >= jumpTime) arrived = true;
  } else {
    myTimer.reset();
  }
  output = P + I + D;
  if (output > 100) output = 100;
  if (output < -100) output = -100;
}