/**
 * @file   ColorDistanceLineTracing.h
 * @brief  指定距離ライントレース動作
 * @author Negimarge
 */

#ifndef COLOR_DISTANCE_LINE_TRACING_H
#define COLOR_DISTANCE_LINE_TRACING_H

#include "LineTracing.h"
#include "Timer.h"
#include "ColorJudge.h"

class ColorDistanceLineTracing : public LineTracing {
 public:
  /**
   * コンストラクタ
   * @param _targetColor 指定色
   * @param _targetDistance 目標距離 0~
   * @param _targetSpeed 目標速度 0~
   * @param _targetBrightness 目標輝度 0~
   * @param _pidGain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  ColorDistanceLineTracing(COLOR _targetColor, double _targetDistance, double _targetSpeed,
                           int _targetBrightness, const PidGain& _pidGain, bool& _isLeftEdge);

  /**
   * @brief (指定距離まで||指定色認識する)までライントレースする
   */
  using LineTracing::run;

 protected:
  /**
   * @brief 色指定距離ライントレースする際の事前条件判定をする
   * @param targetSpeed 目標速度
   * @note オーバーライド
   */

  bool isMetPreCondition(double targetSpeed) override;

  /**
   * @brief 色指定距離ライントレースする際の継続条件判定をする　返り値がfalseでモーターが止まる
   * @note オーバーライド
   */
  bool isMetContinuationCondition() override;

  /**
   * @brief 実行のログを取る
   * @note オーバーライド
   */
  void logRunning() override;

 private:
  static constexpr int JUDGE_COUNT = 3;
  int colorCount = 0;
  COLOR targetColor;      // 指定色
  double targetDistance;  // 目標距離 0~
};

#endif