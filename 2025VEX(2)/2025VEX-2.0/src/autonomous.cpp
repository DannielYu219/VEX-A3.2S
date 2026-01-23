#include "autonomous.h"

#include "Change-1DOF.h"
#include "basic-functions.h"
#include "differential-base.h"
#include "my-timer.h"
#include "robot-config.h"

static auto auton_timer = MyTimer();
void auton_init(void) {
  // init
  resetForwardPos();
  auton_timer.reset();
}
void auton_pre_usercontrol(void) {
  spinIntaker1(0);
  spinChange(0);
  setPistonUp(false);
  setPistonFront(false);
  setPistonDown(false);//下方活塞收回
  Brain.Screen.setCursor(8, 1);
  Brain.Screen.print("AutonTimer: %2.2fsec", auton_timer.getTime() / 1000.0);
}

void auton_skill(void) {
  auton_init();
  auton_pre_usercontrol();
}

void auton_left() {
 
  auton_init();
  this_thread::sleep_for(50);
  

  /*
*/
  auton_pre_usercontrol();
  return;
}

void auton_right() {
  auton_init();
  this_thread::sleep_for(50);
  
  
/**/
  auton_pre_usercontrol();
  return;
}


void auton_alliance() {
  /*----------score alliance stake-------------*/
  MyTimer timer;
  timer.reset();

}
