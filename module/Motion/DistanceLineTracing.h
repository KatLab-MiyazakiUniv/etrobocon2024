/**
 * @file   DistanceLineTracing.h
 * @brief  指定距離ライントレース動作
 * @author CHIHAYATAKU
 */

#ifndef DISTANCE_LINE_TRACING_H
#define DISTANCE_LINE_TRACING_H

#include "LineTracing.h"
#include "Timer.h"

class DistanceLineTracing : public LineTracing {
 public:
  /**
   * コンストラクタ（引数が5つの場合）
   * @param _targetDistance 目標距離 0~
   * @param _targetSpeed 目標速度 0~
   * @param _targetBrightness 目標輝度 0~
   * @param _pidGain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  DistanceLineTracing(double _targetDistance, double _targetSpeed, int _targetBrightness,
                      const PidGain& _pidGain, bool& _isLeftEdge);

  /**
   * コンストラクタ（引数が6つの場合）
   * @param _targetDistance 目標距離 0~
   * @param _targetSpeed 目標速度 0~
   * @param _targetBrightness 目標輝度 0~
   * @param _pidGain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   * @param _isRecoveryEnabled 復帰動作を行うかの判定(true:行う, false:行わない)
   */
  DistanceLineTracing(double _targetDistance, double _targetSpeed, int _targetBrightness,
                      const PidGain& _pidGain, bool& _isLeftEdge, bool _isRecoveryEnabled);

  /**
   * @brief 指定距離だけライントレースする
   */
  using LineTracing::run;

 protected:
  /**
   * @brief 指定距離ライントレースする際の事前条件判定をする
   * @param targetSpeed 目標速度
   * @note オーバーライド必須
   */

  bool isMetPreCondition(double targetSpeed) override;

  /**
   * @brief 指定距離ライントレースする際の継続条件判定をする　返り値がfalseでモーターが止まる
   * @note オーバーライド必須
   */
  bool isMetContinuationCondition() override;

  /**
   * @brief 実行のログを取る
   * @note オーバーライド必須
   */
  void logRunning() override;

  /**
   * @brief 走行体がコースを外れたときに復帰動作をする
   */
  using LineTracing::recover;

  /**
   * @brief 走行体がコースを脱線しているかを判定をする　返り値がtrueで復帰動作開始
   */
  using LineTracing::isErrorState;

  /**
   * @brief 復帰動作実行のログを取る
   */
  using LineTracing::logRunningRecovering;

 private:
  double targetDistance;  // 目標距離 0~
};

#endif