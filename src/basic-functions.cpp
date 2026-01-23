#include "basic-functions.h"
#include "math-tools.h"
#include "my-timer.h"
#include "parameters.h"
#include "queue"
#include "robot-config.h"

/**
 * powers the motor on intake with duty cycle _input%
 * @param _input ranges from -100 : 100
 */
void spinIntaker1(float _input) {
  _input = fabs(_input) > 100 ? sign(_input) * 100 : _input;
  if (!_input) {
    Motor_Intaker1.stop(coast);
  } else {
    Motor_Intaker1.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
  }
}

void spinIntaker2(float _input) {
  _input = fabs(_input) > 100 ? sign(_input) * 100 : _input;
  if (!_input) {
    Motor_Intaker2.stop(coast);
  } else {
    Motor_Intaker2.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
  }
}
/**
 * set up
 * @param _input true or false
 */
void setPistonUp(bool _input) {
  if (_input)
    Piston_Up.open();
  else
    Piston_Up.close();
}

/**
 * set down
 * @param _input true or false
 */
void setPistonDown(bool _input) {
  if (_input)
    Piston_Down.open();
  else
    Piston_Down.close();
}

/**
 * set front
 * @param _input true or false
 */
void setPistonFront(bool _input) {
  if (_input)
    Piston_Front.open();
  else
    Piston_Front.close();
}


/**
 * set front
 * @param _input true or false
 */
void setPistonHook(bool _input) {
  if (_input)
    Piston_Hook.open();
  else
    Piston_Hook.close();
}