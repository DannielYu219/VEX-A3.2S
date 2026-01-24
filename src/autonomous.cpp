#include "autonomous.h"

#include "basic-functions.h"
#include "change-1DOF.h"
#include "differential-base.h"
#include "my-timer.h"
#include "robot-config.h"

static auto auton_timer = MyTimer();
/**
 @brief 将目标毫米(mm)转换为电机指令单位(cc)
 @param V 运行速度 (20-40区间)
 @param target_mm 想要移动的物理距离
 @return int 对应的cc指令值
 */

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
  setPistonDown(false); // 下方活塞收回
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
  //标定//#
  // posForwardAbs(30, convert(30, 600));
  // this_thread::sleep_for(500);
  //标定//#
  spinIntaker1(100);      // 进球滚轮开始转动
  //spinIntaker2(100);      // 导入桶滚轮开始转动
  posForwardAbs(35, 115); // 快速接近3q球

  pidRotateAbs(-45); // 转动车头指向50度方向

  posForwardAbs(35, 175);      // 慢速吸3球
  this_thread::sleep_for(175);
  spinIntaker1(100); // 等待0.2s,吸球
  setPistonFront(true);        // 前方活塞伸出，抱球
           // 导入桶滚轮开始转动
  this_thread::sleep_for(150); // 等待0.2s,吸球
 
  pidRotateAbs(-135); // 对准x 
 
  posForwardAbs(40, -320); // 后退到中桥         这个距离就是x到中桥的距离
  spinIntaker2(60);  
  timerForward(-10, 200); // 后退压到桥

  spinIntaker2(100);
  spinChange(-100);
  this_thread::sleep_for(700);

  spinIntaker2(-100);//反转回收球
  spinChange(100);//收集、
  pidRotateAbs(-135);//对准导入桶
  posForwardAbs(100, 605); // 后退到导入桶
  spinIntaker2(100);
  pidRotateAbs(-180);//对准导入桶
  posForwardAbs(40, 230); // 后退到导入桶
  timerForward(40, 1000); // 压到倒入桶
  
  spinIntaker2(-100);
  pidRotateAbs(-180);//对准导入桶
  posForwardAbs(45, -380); // 后退到高桥
  timerForward(-30, 200);
  setPistonUp(true);
  spinIntaker1(100);
  spinIntaker2(100);
  spinChange(100);
  this_thread::sleep_for(1100);

  posForwardAbs(40, 120);
  pidRotateAbs(-225);
  posForwardAbs(50, -120);
  pidRotateAbs(-180);
  posForwardAbs(50, -100);
  posForwardAbs(100, -90);

  this_thread::sleep_for(500);

  auton_pre_usercontrol();
  return;
}

void auton_right() {
  auton_init();
  this_thread::sleep_for(50);
  //标定//#
  // posForwardAbs(30, convert(30, 600));
  // this_thread::sleep_for(500);
  //标定//#
  spinChange(100);
  spinIntaker1(100);      // 进球滚轮开始转动
  //spinIntaker2(100);      // 导入桶滚轮开始转动
  posForwardAbs(38, 110); // 快速接近3q球

  pidRotateAbs(45); // 转动车头指向50度方向

  posForwardAbs(30, 200);      // 慢速吸3球
  setPistonFront(true);        // 前方活塞伸出，抱球
  this_thread::sleep_for(170);
  spinIntaker1(100); // 等待0.2s,吸球
  //setPistonFront(true);        // 前方活塞伸出，抱球
           // 导入桶滚轮开始转动
  this_thread::sleep_for(150); // 等待0.2s,吸球
           // 导入桶滚轮开始转动
 
  pidRotateAbs(-45); // 对准x 
  this_thread::sleep_for(100);

  setPistonFront(false);
  setPistonDown(true); // 下方活塞拉起，出球

  posForwardAbs(50, 280); // 前进到中桥//          这个距离就是x到中桥的距离
  //

  timerForward(25, 220); // 前进压到桥

  //spinIntaker2(0);
  
  spinIntaker1(-100);
 

  //spinIntaker2(-100);
  //spinChange(0);
  //setPistonFront(true); // 下方活塞压下
  this_thread::sleep_for(1000);

  setPistonDown(false);
  spinIntaker1(100);
  spinIntaker2(100);
  spinChange(100);//收集、

  pidRotateAbs(-45);//对准导入桶
  posForwardAbs(100, -460); // 后退到导入桶
  
  pidRotateAbs(-180);//对准导入桶
  setPistonFront(true);
  posForwardAbs(30, 90); // 后退到导入桶
  timerForward(40, 1000); // 压到倒入桶
  
  
  pidRotateAbs(-180);//对准导高桥
  posForwardAbs(50, -480); 
  timerForward(-10, 200);
  setPistonUp(true);
  spinChange(100);
  spinIntaker1(100);
  spinIntaker2(100);
  this_thread::sleep_for(1000);

  posForwardAbs(40, 120);
  pidRotateAbs(-225);
  posForwardAbs(40, -120);
  pidRotateAbs(-180);
  posForwardAbs(50, -100);
  posForwardAbs(100, -90);

  this_thread::sleep_for(500);

  auton_pre_usercontrol();
  return;
}

void auton_alliance() {
  /*----------score alliance stake-------------*/
  MyTimer timer;
  timer.reset();
}