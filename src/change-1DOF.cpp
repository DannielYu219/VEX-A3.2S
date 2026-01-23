#include "change-1DOF.h"

#include "PID.h"
#include "math-tools.h"
#include "parameters.h"
#include "robot-config.h"


/**
 * powers the motor on Change with duty cycle _input%
 * @param _input ranges from -100 : 100
 */
void spinChange(float _input) {
  _input = fabs(_input) > 100 ? sign(_input) * 100 : _input;
  if (!_input) {
    Motor_Change.stop(coast);
  } else {
    Motor_Change.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
  }
}





