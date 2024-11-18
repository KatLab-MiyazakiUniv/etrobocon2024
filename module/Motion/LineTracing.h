/**
 * @file   LineTracing.h
 * @brief  ライントレース動作
 * @author CHIHAYATAKU
 */

#ifndef LINE_TRACING_H
#define LINE_TRACING_H

#include "SpeedCalculator.h"
#include "Motion.h"
#include "Mileage.h"
#include "Timer.h"
#include "Pid.h"
#include "SystemInfo.h"

class LineTracing : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetSpeed 目標速度 0~
   * @param _targetBrightness 目標輝度 0~
   * @param _pidGain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  LineTracing(double _targetSpeed, int _targetBrightness, const PidGain& _pidGain,
              bool& _isLeftEdge);

  /**
   * @brief ライントレースする
   */
  void run();

 protected:
  /**
   * @brief ライントレースする際の事前条件判定をする
   * @param targetSpeed 目標速度
   * @note オーバーライド必須
   */
  virtual bool isMetPreCondition(double targetSpeed) = 0;

  /**
   * @brief ライントレースする際の継続条件判定をする　返り値がfalseでモーターが止まる
   * @note オーバーライド必須
   */
  virtual bool isMetContinuationCondition() = 0;

  /**
   * @brief 実行のログを取る
   */
  virtual void logRunning();

 protected:
  double targetSpeed;    // 目標速度 0~
  int targetBrightness;  // 目標輝度 0~
  PidGain pidGain;       // PIDゲイン

  bool& isLeftEdge;         // エッジの左右判定(true:左エッジ, false:右エッジ)
  double initLeftMileage;   // クラス呼び出し時の左車輪の走行距離
  double initRightMileage;  // クラス呼び出し時の右車輪の走行距離
  double initDistance;      // 実行前の走行距離
  Timer timer;
  // Measurer measurer;
  // Controller controller;
};

#endif