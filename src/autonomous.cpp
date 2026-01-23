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
  posForwardAbs(30, convert(30, 600));
  this_thread::sleep_for(500);
  //标定//#
  // spinIntaker1(100);      // 进球滚轮开始转动
  // //spinIntaker2(100);      // 导入桶滚轮开始转动
  // posForwardAbs(40, 115); // 快速接近3q球

  // pidRotateAbs(-45); // 转动车头指向45度方向

  // posForwardAbs(28, 235);      // 慢速吸3球
  // this_thread::sleep_for(200);
  // spinIntaker1(60); // 等待0.2s,吸球
  // setPistonFront(true);        // 前方活塞伸出，抱球
  // spinIntaker2(150);           // 导入桶滚轮开始转动
  // this_thread::sleep_for(150); // 等待0.2s,吸球
  // // spinIntaker1(0);//进球滚轮停止转动

  // pidRotateAbs(-135); // 对准导入桶
  // posForwardAbs(40, -320); // 后退到中桥         这个距离就是x到中桥的距离
  // timerForward(-10, 200); // 后退压到桥

  // spinChange(-100);
  // spinIntaker2(100);
  // setPistonUp(true);
  // this_thread::sleep_for(200);
  // pidRotateAbs(-135);//对准导入桶
  // posForwardAbs(40, 200); // 后退到导入桶
  // this_thread::sleep_for(500);
///////////////////////////////////////////////////////////
  
  // spinChange(0);
  // spinIntaker2(0);

  // spinIntaker1(100);//进球滚轮开始转动
  // pidRotateAbs(-130);//对准导入桶

  // posForwardAbs(40, 870);//前进到导入桶          这个距离就是x到导入桶的距离
  // pidRotateAbs(-180);//对准导入桶

  // posForwardAbs(40, -300);//后退到高桥
  // timerForward(-30,400);
  // spinIntaker1(100);
  // spinIntaker2(100);
  // setPistonUp(true);
  // spinChange(100);
  // this_thread::sleep_for(1500);

  // //抢4
  // posForwardAbs(30, 150);
  // pidRotateAbs(-225);
  // posForwardAbs(30, -175);
  // pidRotateAbs(-180);
  // posForwardAbs(30, -200);
  // posForwardAbs(100, -100);

  auton_pre_usercontrol();
  return;
}

void auton_right() {
  auton_init();
  this_thread::sleep_for(50);

  spinIntaker1(100);      // 进球滚轮开始转动
  posForwardAbs(40, 100); // 快速接近3q球

  pidRotateAbs(45); // 转动车头指向45度方向

  posForwardAbs(30, 260);      // 慢速吸3球
  this_thread::sleep_for(200); // 等待0.2s,吸球
  setPistonFront(true);        // 前方活塞伸出，抱球
  this_thread::sleep_for(150); // 等待0.2s,吸球

  pidRotateAbs(130); // 对准导入桶

  // softStartTimerForward(0, 40, 150 );//软起动0-40，
  posForwardAbs(40, 490); // 前进到导入桶          这个距离就是x到导入桶的距离
  pidRotateAbs(180); // 对准导入桶
  // posForwardAbs(40, 60);
  // timerForward(40,1400);

  // posForwardAbs(40, -300);//后退到高桥
  posForwardAbs(40, -300); // 后退到高桥
  timerForward(-30, 400);
  spinIntaker1(100);
  spinIntaker2(100);
  spinChange(100);
  this_thread::sleep_for(1500);

  // 抢4
  posForwardAbs(30, 150);
  pidRotateAbs(-225);
  posForwardAbs(30, -190);
  pidRotateAbs(-180);
  posForwardAbs(30, -200);
  posForwardAbs(100, -90);
  /**/
  auton_pre_usercontrol();
  return;
}

void auton_alliance() {
  /*----------score alliance stake-------------*/
  MyTimer timer;
  timer.reset();
}