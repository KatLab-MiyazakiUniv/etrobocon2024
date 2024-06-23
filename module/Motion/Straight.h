/**
 * @file   Straight.h
 * @brief  直進動作の抽象クラス
 * @author bizyutyu
 */

#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "Motion.h"
#include "Pid.h"
#include "Mileage.h"
#include "SpeedCalculator.h"
#include "Timer.h"
#include "SystemInfo.h"

class Straight : public Motion {
 public:
  /**
   * @brief コンストラクタ
   * @param _speed       目標速度[mm/s]
   */
  Straight(double _speed);

  /**
   * @brief 直進する
   */
  void run();

 protected:
  /**
   * @brief 直進する際の事前条件判定をする
   */
  virtual bool isMetPreCondition();

  /**
   * @brief 直進する際の動作継続条件判定をする　返り値がtrueの間モーターが回転
   * @note オーバーライド必須
   */
  virtual bool isMetContinuationCondition() = 0;

  /**
   * @brief 実行のログを取る
   */
  virtual void logRunning();

 protected:
  // 目標値は継承後に追加する
  static constexpr double MIN_PWM = 40.0;  // 静止時から走行体がモーターを動かせないPWM値
  double targetSpeed;                      // 目標速度[mm/s]
  double initialRightDistance;             // 初期右輪距離
  double initialLeftDistance;              // 初期左輪距離
  int currentRightMotorCount;              // 現在右モーター角位置
  int currentLeftMotorCount;               // 現在左モーター角位置
  double currentRightDistance;             // 現在右輪距離
  double currentLeftDistance;              // 現在左輪距離
  Timer timer;
  Measurer measurer;
};

#endif