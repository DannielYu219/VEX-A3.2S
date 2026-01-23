#include "robot-config.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;
// VEXcode device constructors
controller Controller1 = controller(primary);

motor Motor_BaseLF = motor(PORT11, ratio6_1, true);
motor Motor_BaseLM = motor(PORT12, ratio6_1, false);
motor Motor_BaseLB = motor(PORT13, ratio6_1, true);
motor Motor_BaseRF = motor(PORT14, ratio6_1, false);
motor Motor_BaseRM = motor(PORT15, ratio6_1, true);
motor Motor_BaseRB = motor(PORT16, ratio6_1, false);
motor Motor_Intaker1 = motor(PORT17, ratio6_1, true);
motor Motor_Intaker2 = motor(PORT18, ratio6_1, true);
motor Motor_Change = motor(PORT19, ratio6_1, false);
pneumatics Piston_Up = pneumatics(Brain.ThreeWirePort.G);
pneumatics Piston_Down = pneumatics(Brain.ThreeWirePort.C);
pneumatics Piston_Front = pneumatics(Brain.ThreeWirePort.F);
pneumatics Piston_Hook = pneumatics(Brain.ThreeWirePort.H);
inertial IMU = inertial(PORT21);
optical Color_Sensor = optical(PORT6);
distance Switch_Sensor = distance(PORT4);




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