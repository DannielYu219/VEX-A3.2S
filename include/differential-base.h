#ifndef DIFFERENTIAL_BASE_H_
#define DIFFERENTIAL_BASE_H_

float getLeftPos();
float getRightPos();
float getForwardPos();
void resetLeftPos();
void resetRightPos();
void resetForwardPos();
float getHeading();

void moveLeft(float);
void moveLeftVel(float);
void lockLeft(void);
void unlockLeft(void);
void moveRight(float);
void moveRightVel(float);
void lockRight(void);
void unlockRight(void);
void moveForward(float);
void moveClockwise(float);
void lockBase(void);
void unlockBase(void);

void softStartTimerForward(float _power_init, float _power_final,
                           int _duration);
void timerForward(float _power, int _duration);
void timerForward(float _power, int _duration, float _heading);
void timerForward(float _power, int _duration, float _heading, float _distance);
void posForwardRel(float _power, float _target);
void posForwardAbs(float _power, float _target);
void pidForwardRel(float _target);
void pidForwardAbs(float _target);
void pidForwardAbs(float _target, float _heading);
void pidForwardAbs(float _target, float _kp, float _ki, float _kd);

void softStartTimerRotate(float _power_init, float _power_final, int _duration);
void timerRotate(float _power, int _duration);
void angleRotateRel(float _power, float _target);
void angleRotateAbs(float _power, float _target);
void pidRotateRel(float _target);
void pidRotateAbs(float _target);
void pidRotateAbs(float _target, float _error_tolerance);
void pidRotateAbs(float _target, float _kp, float _ki, float _kd);

void timerCurve(float _left_power, float _right_power, float _duration,
                bool _mirror_flag = 1);
void PIDPosCurveRel(float left_target, float right_target, float tolerance = 2);
void PIDPosCurveAbs(float left_target, float right_target, float tolerance = 2);

/**
 @brief 将目标毫米(mm)转换为电机指令单位(cc)
 @param V 运行速度 (20-40区间)
 @param target_mm 想要移动的物理距离
 @return int 对应的cc指令值
 */
int convert(float V, float target_mm);

#endif