/**
 * @file   ColorStraight.cpp
 * @brief  色まで直進するクラス
 * @author bizyutyu
 */

#ifndef COLORSTRAIGHT_H
#define COLORSTRAIGHT_H

#include "Straight.h"
#include "ColorJudge.h"

class ColorStraight : public Straight {
 public:
  /**
   * コンストラクタ
   * @param _targetColor 目標色
   * @param _speed       目標速度[mm/s]
   */
  ColorStraight(COLOR _targetColor, double _speed);

 protected:
  /**
   * @brief 直進する際の事前条件判定をする
   */
  virtual bool isMetPreCondition() override;

  /**
   * @brief 直進する際の動作継続条件判定をする　返り値がtrueの間モーターが回転
   */
  virtual bool isMetContinuationCondition() override;

  /**
   * @brief 実行のログを取る
   */
  virtual void logRunning() override;

 private:
  static constexpr int JUDGE_COUNT = 3;
  int colorCount = 0;
  COLOR targetColor;  // 目標色
};

#endif
