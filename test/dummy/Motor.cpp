/**
 * @file Motor.cpp
 * @brief モータクラスで用いる関数（ダミー）
 * @author keiya121
 */

#include "Motor.h"
using namespace ev3api;

// コンストラクタ
Motor::Motor(ePortM _port, bool brake, motor_type_t type) : port(_port) {}

// PORT_B　右モータ
// PORT_C　左モータ
// モータ角位置取得
int Motor::getCount()
{
  if(port == PORT_C) {
    return static_cast<int>(leftCount);
  } else if(port == PORT_B) {
    return static_cast<int>(rightCount);
  } else {
    return static_cast<int>(armCount);
  }
}

// pwm値設定
void Motor::setPWM(int pwm)
{
  if(port == PORT_C) {
    leftCount += pwm * 0.05;
  } else if(port == PORT_B) {
    rightCount += pwm * 0.05;
  } else {
    armCount += pwm * 0.05;
  }
}

void Motor::reset()
{
  if(port == PORT_C) {
    leftCount = 0;
  } else if(port == PORT_B) {
    rightCount = 0;
  } else {
    armCount = 0;
  }
}

double Motor::leftCount = 0.0;
double Motor::rightCount = 0.0;
double Motor::armCount = 0.0;