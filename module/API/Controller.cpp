/**
 * @file Controller.cpp
 * @brief モーター制御に用いる関数をまとめたラッパークラス
 * @author takahashitom CHIHAYATAKU
 */
#include "Controller.h"

Controller::Controller() : rightWheel(PORT_B), leftWheel(PORT_C), armMotor(PORT_A) {}

// PWMの初期化
double Controller::pwmOfRightWheel = 0.0;
double Controller::pwmOfLeftWheel = 0.0;
double Controller::pwmOfArm = 0.0;

// モータに設定するPWM値の制限
int Controller::limitPwmValue(const int value)
{
  if(value > MOTOR_PWM_MAX) {
    return MOTOR_PWM_MAX;
  } else if(value < MOTOR_PWM_MIN) {
    return MOTOR_PWM_MIN;
  }
  return value;
}

// 右モータにPWM値をセット
void Controller::setRightMotorPwm(const int pwm)
{
  pwmOfRightWheel = pwm;
  rightWheel.setPWM(limitPwmValue(pwm));
}

// 左モータにPWM値をセット
void Controller::setLeftMotorPwm(const int pwm)
{
  pwmOfLeftWheel = pwm;
  leftWheel.setPWM(limitPwmValue(pwm));
}

// 右モータのPWM値をリセット
void Controller::resetRightMotorPwm()
{
  pwmOfRightWheel = 0.0;
  rightWheel.reset();
}

// 左モータのPWM値をリセット
void Controller::resetLeftMotorPwm()
{
  pwmOfLeftWheel = 0.0;
  leftWheel.reset();
}

// タイヤのモータを停止する
void Controller::stopMotor()
{
  pwmOfRightWheel = 0.0;
  pwmOfLeftWheel = 0.0;
  leftWheel.stop();
  rightWheel.stop();
}

// アームのモータにPWM値をセット
void Controller::setArmMotorPwm(const int pwm)
{
  pwmOfArm = pwm;
  armMotor.setPWM(limitPwmValue(pwm));
}

// アームのモータのPWM値をリセット
void Controller::resetArmMotorPwm()
{
  pwmOfArm = 0;
  armMotor.reset();
}

// アームのモータを停止する
void Controller::stopArmMotor()
{
  pwmOfArm = 0;
  armMotor.stop();
}

// 右タイヤのPWMを取得する
double Controller::getRightPwm()
{
  return pwmOfRightWheel;
}

// 左タイヤのPWMを取得する
double Controller::getLeftPwm()
{
  return pwmOfLeftWheel;
}