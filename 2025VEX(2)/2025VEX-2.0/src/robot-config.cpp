#include "robot-config.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;
// VEXcode device constructors
controller Controller1 = controller(primary);

motor Motor_BaseLF = motor(PORT11, ratio6_1, true);
motor Motor_BaseLM = motor(PORT12, ratio6_1, true);
motor Motor_BaseLB = motor(PORT13, ratio6_1, true);
motor Motor_BaseRF = motor(PORT1, ratio6_1, false);
motor Motor_BaseRM = motor(PORT2, ratio6_1, false);
motor Motor_BaseRB = motor(PORT3, ratio6_1, false);
motor Motor_Intaker1 = motor(PORT9, ratio18_1, true);
motor Motor_Intaker2 = motor(PORT19, ratio6_1, false);
motor Motor_Change = motor(PORT10, ratio18_1, false);
pneumatics Piston_Up = pneumatics(Brain.ThreeWirePort.B);
pneumatics Piston_Down = pneumatics(Brain.ThreeWirePort.A);
pneumatics Piston_Front = pneumatics(Brain.ThreeWirePort.F);
inertial IMU = inertial(PORT6);
optical Color_Sensor = optical(PORT16);
distance Switch_Sensor = distance(PORT14);




// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

void vexcodeInit(void) {
  Controller1.Screen.setCursor(5, 1);
  Controller1.Screen.print("%19s", "IMU Calibrating...");
  Color_Sensor.setLightPower(100);
  Color_Sensor.integrationTime(20);
  IMU.startCalibration();
  while (IMU.isCalibrating()) {
    this_thread::sleep_for(5);
  }
  Controller1.Screen.setCursor(5, 1);
  Controller1.Screen.print("%19s", "IMU Ready!");
}