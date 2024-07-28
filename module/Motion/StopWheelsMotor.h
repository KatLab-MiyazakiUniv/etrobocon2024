/**
 * @file   StopWheelsMotor.h
 * @brief  両輪モーター停止
 * @author Negimarge
 */

#ifndef STOP_WHEELS_MOTOR_H
#define STOP_WHEELS_MOTOR_H

#include "Motion.h"
#include "Controller.h"

class StopWheelsMotor : public Motion {
 public:
  /**
   * コンストラクタ
   */
  StopWheelsMotor();

  /**
   * @brief 両輪モーターを停止する
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
