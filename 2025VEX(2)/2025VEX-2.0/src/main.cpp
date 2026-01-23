/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       chifeng                                                   */
/*    Created:      11/15/2024, 9:47:08 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "change-1DOF.h"
#include "basic-functions.h"
#include "controller.h"
#include "differential-base.h"
#include "math-tools.h"
#include "my-timer.h"
#include "parameters.h"
#include "robot-config.h"
#include "adjusment.h"
#include "autonomous.h"
using namespace vex;

competition Competition;

static int auton_strategy = 0;

void auto1(void) {
  switch (auton_strategy) {
    case 0:
      auton_left();
      break;
    case 1:
      auton_right();
      break;
    
   
  }
}

void usercontrol(void) {
  int intake_offset = 0;
  int change_state = 0; //滚球状态
  int piston_up_state = 0; //气缸状态 1伸出 0缩回
  while (true) {
    /*-------------Base Movement Control-------------*/
    A3 = std::abs(A3) < JOYSTICK_DEADZONE ? 0 : A3;
    A1 = std::abs(A1) < JOYSTICK_DEADZONE ? 0 : A1;
    if (std::abs(A3 + A1) > MOVEMENT_LOWER_LIMIT && !LEFT)
      moveLeft((1*A3 + 0.6*A1));   //0.6  取值0-1
    else
      unlockLeft();
    if (std::abs(A3 - A1) > MOVEMENT_LOWER_LIMIT && !LEFT)
      moveRight((1*A3 - 0.6*A1)); //0.6  取值0-1
    else
      unlockRight();
    /*-------------Intake Control-------------*/
    intake_offset += 6;
    intake_offset = intake_offset % 360;
    if (R1) {
      // 收集
      spinIntaker1(100);
      spinIntaker2(100);
      
    } else if (R2) {//吐，做下层
      spinIntaker1(-100);
      spinIntaker2(-100);
     
    }else if (L1) {//上层
      
      spinIntaker1(100);
      spinIntaker2(-100);
      spinChange(100);
     
    }else if (L2) {//中层
      spinIntaker1(100);
      spinIntaker2(-100);
      spinChange(-100);
     
    } else{
      
        spinIntaker1(0);
        spinIntaker2(0);
        spinChange(0);
        
    }
    
   
    /*-------------Mobile Goal UP Control-------------*/
    if (A && !last_A  && !LEFT) {
      setPistonFront(false);
    }
    if (B && !last_B && !LEFT) {
      setPistonFront(true);
    }
    /*-------------Thread Sleep Time-------------*/
    if (LEFT && RIGHT) {
      // auton_alliance();
      auto1();
      // auton_plus(0);
      // auton_minus(1);
      // auton_plus_a(0);
    }
    // fastTuningRotatePD();
    // fastTuningRotateI();
    // fastTuningChangePD();
    if(piston_up_state%2==0&&!LEFT){
      setPistonUp(false);
    }
    else if(piston_up_state%2==1&&!LEFT){
      setPistonUp(true);
    }
    
    
    if (X && !last_X  && !LEFT) {
      piston_up_state++;
      this_thread::sleep_for(100);
     
    }

   
    
   
    if (LEFT && A){
      IMU.startCalibration();
      while (IMU.isCalibrating()) {
        this_thread::sleep_for(5);
      }
      Controller1.Screen.setCursor(5, 1);
      Controller1.Screen.print("%19s", "IMU Ready!");

    }
        // Set auton strategy
    if(LEFT && A1 > 80) {
      this_thread::sleep_for(300);
      auton_strategy++;
      auton_strategy = auton_strategy % 2;
      switch(auton_strategy) {
        case 0:
          Controller1.Screen.setCursor(5, 1);
          Controller1.Screen.print("%12s", "left");
          break;
        case 1:
          Controller1.Screen.setCursor(5, 1);
          Controller1.Screen.print("%12s", "right");
          break;
        
        
       
        
      }
    }
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("IMU: %4f, POS: %4f", getHeading(), getForwardPos());
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("change-state: %2f", change_state);
    Brain.Screen.setCursor(10, 1);
    this_thread::sleep_for(10);
  }
}

int main() {
  Competition.autonomous(auto1);
  Competition.drivercontrol(usercontrol);
  vexcodeInit();

  thread ThreadController(defineController);
 
  

  while (true) {
    this_thread::sleep_for(100);
  }
}
