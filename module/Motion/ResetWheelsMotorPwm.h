/**
 * @file   ResetWheelsMotorPwm.h
 * @brief  両輪モーターリセット&停止
 * @author Negimarge
 */

#ifndef RESET_WHEELS_MOTOR_PWM_H
#define RESET_WHEELS_MOTOR_PWM_H

#include "Motion.h"
#include "Controller.h"

class ResetWheelsMotorPwm : public Motion {
 public:
  /**
   * コンストラクタ
   */
  ResetWheelsMotorPwm();

  /**
   * @brief 両輪モーターをリセットする
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  Controller controller;
};

#endif
