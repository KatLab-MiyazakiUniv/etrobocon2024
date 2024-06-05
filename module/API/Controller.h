/**
 * @file Controller.h
 * @brief モーター制御に用いる関数をまとめたラッパークラス
 * @author takahashitom
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ev3api.h"
#include "Motor.h"

class Controller {
 public:
  /** PWM値の上限 */
  static const int MOTOR_PWM_MAX = 100;

  /** PWM値の下限 */
  static const int MOTOR_PWM_MIN = -100;

  /**
   * コンストラクタ
   */
  Controller();

  /**
   * @brief タイヤのモータにPWM値をセット
   * @param pwm PWM値
   */
  void setRightMotorPwm(const int pwm);
  void setLeftMotorPwm(const int pwm);

  /**
   * @brief タイヤのモータのPWM値をリセット
   */
  void resetRightMotorPwm();
  void resetLeftMotorPwm();

  /**
   * @brief タイヤのモータを停止する
   */
  void stopMotor();

  /**
   * @brief アームのモータにPWM値をセット
   * @param pwm PWM値
   */
  void setArmMotorPwm(const int pwm);

  /**
   * @brief アームのモータのPWM値をリセット
   */
  void resetArmMotorPwm();

  /**
   * @brief アームのモータを停止する
   */
  void stopArmMotor();

 private:
  ev3api::Motor rightWheel;
  ev3api::Motor leftWheel;
  ev3api::Motor armMotor;

  /**
   * @brief モータに設定するPWM値の制限
   * @param value 入力されたPWM値
   * @return 制限されたPWM値
   */
  int limitPwmValue(const int value);
};

#endif