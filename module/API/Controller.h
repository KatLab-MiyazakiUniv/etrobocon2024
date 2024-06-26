/**
 * @file Controller.h
 * @brief モーター制御に用いる関数をまとめたラッパークラス
 * @author takahashitom CHIHAYATAKU
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ev3api.h"
#include "Motor.h"

class Controller {
 public:
  /** PWM値の上限 */
  static constexpr double MOTOR_PWM_MAX = 100.0;

  /** PWM値の下限 */
  static constexpr double MOTOR_PWM_MIN = -100.0;

  /**
   * コンストラクタ
   */
  Controller();

  /**
   * @brief タイヤのモータにPWM値をセット
   * @param pwm PWM値
   */
  void setRightMotorPwm(const double pwm);
  void setLeftMotorPwm(const double pwm);

  /**
   * @brief タイヤのモータのPWM値をリセット
   */
  void resetRightMotorPwm();
  void resetLeftMotorPwm();
  void resetWheelsMotorPwm();

  /**
   * @brief タイヤのモータを停止する
   */
  void stopWheelsMotor();

  /**
   * @brief アームのモータにPWM値をセット
   * @param pwm PWM値
   */
  void setArmMotorPwm(const double pwm);

  /**
   * @brief アームのモータのPWM値をリセット
   */
  void resetArmMotorPwm();

  /**
   * @brief アームのモータを停止する
   */
  void stopArmMotor();

  /**
   * @brief 右タイヤのPWMを取得する
   * @return 右タイヤのPWM
   */
  static double getRightMotorPwm();

  /**
   * @brief 左タイヤのPWMを取得する
   * @return 左タイヤのPWM
   */
  static double getLeftMotorPwm();

 private:
  ev3api::Motor rightWheel;
  ev3api::Motor leftWheel;
  ev3api::Motor armMotor;
  static double pwmOfRightWheel;  // 右タイヤPWM
  static double pwmOfLeftWheel;   // 左タイヤPWM
  static double pwmOfArm;         // アームPWM

  /**
   * @brief モータに設定するPWM値の制限
   * @param inputPwm 入力されたPWM値
   * @return 制限されたPWM値
   */
  double limitPwmValue(const double inputPwm);
};

#endif