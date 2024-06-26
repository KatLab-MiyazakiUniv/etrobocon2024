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
double Controller::limitPwmValue(const double inputPwm)
{
  if(inputPwm > MOTOR_PWM_MAX) {
    return MOTOR_PWM_MAX;
  } else if(inputPwm < MOTOR_PWM_MIN) {
    return MOTOR_PWM_MIN;
  }
  return inputPwm;
}

// 右モータにPWM値をセット
void Controller::setRightMotorPwm(const double pwm)
{
  pwmOfRightWheel = limitPwmValue(pwm);
  rightWheel.setPWM(static_cast<int>(pwmOfRightWheel));
}

// 左モータにPWM値をセット
void Controller::setLeftMotorPwm(const double pwm)
{
  pwmOfLeftWheel = limitPwmValue(pwm);
  leftWheel.setPWM(static_cast<int>(pwmOfLeftWheel));
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

// 右左両モータの状態をリセット
void Controller::resetWheelsMotorPwm()
{
  pwmOfRightWheel = 0.0;
  pwmOfLeftWheel = 0.0;
  rightWheel.reset();
  leftWheel.reset();
}

// タイヤのモータを停止する
void Controller::stopWheelsMotor()
{
  pwmOfRightWheel = 0.0;
  pwmOfLeftWheel = 0.0;
  leftWheel.stop();
  rightWheel.stop();
}

// アームのモータにPWM値をセット
void Controller::setArmMotorPwm(const double pwm)
{
  pwmOfArm = pwm;
  armMotor.setPWM(int(limitPwmValue(pwm)));
}

// アームのモータのPWM値をリセット
void Controller::resetArmMotorPwm()
{
  pwmOfArm = 0.0;
  armMotor.reset();
}

// アームのモータを停止する
void Controller::stopArmMotor()
{
  pwmOfArm = 0.0;
  armMotor.stop();
}

// 右タイヤのPWMを取得する
double Controller::getRightMotorPwm()
{
  return pwmOfRightWheel;
}

// 左タイヤのPWMを取得する
double Controller::getLeftMotorPwm()
{
  return pwmOfLeftWheel;
}