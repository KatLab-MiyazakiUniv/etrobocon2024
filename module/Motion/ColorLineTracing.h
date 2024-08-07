/**
 * @file   ColorLineTracing.h
 * @brief  指定色ライントレース動作
 * @author CHIHAYATAKU
 */

#ifndef COLOR_LINE_TRACING_H
#define COLOR_LINE_TRACING_H

#include "ColorJudge.h"
#include "LineTracing.h"

class ColorLineTracing : public LineTracing {
 public:
  /**
   * コンストラクタ（引数が5つの場合）
   * @param _targetColor 指定色
   * @param _targetSpeed 目標速度
   * @param _targetBrightness 目標輝度 0~
   * @param _gain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  ColorLineTracing(COLOR _targetColor, double _targetSpeed, int _targetBrightness,
                   const PidGain& _gain, bool& _isLeftEdge);

  /**
   * コンストラクタ（引数が6つの場合）
   * @param _targetColor 指定色
   * @param _targetSpeed 目標速度
   * @param _targetBrightness 目標輝度 0~
   * @param _gain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   * @param _isRecoveryEnabled 復帰動作を行うかの判定(true:行う, false:行わない)
   */
  ColorLineTracing(COLOR _targetColor, double _targetSpeed, int _targetBrightness,
                   const PidGain& _gain, bool& _isLeftEdge, bool _isRecoveryEnabled);

  /**
   * @brief 指定色までライントレースする
   */
  using LineTracing::run;

 protected:
  /**
   * @brief 指定色ライントレースする際の事前条件判定をする
   * @param targetSpeed 目標速度
   * @note オーバーライド必須
   */
  bool isMetPreCondition(double targetSpeed) override;

  /**
   * @brief 指定色ライントレースする際の継続条件判定をする　返り値がfalseでモーターが止まる
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
  static constexpr int JUDGE_COUNT = 3;
  int colorCount = 0;
  COLOR targetColor;  // 指定色
};

#endif