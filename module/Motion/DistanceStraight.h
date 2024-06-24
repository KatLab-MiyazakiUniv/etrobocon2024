/**
 * @file   DistanceStraight.h
 * @brief  目標距離まで直進するクラス
 * @author bizyutyu
 */

#ifndef DISTANCESTRAIGHT_H
#define DISTANCESTRAIGHT_H

#include "Straight.h"

class DistanceStraight : public Straight {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離
   * @param _speed       目標速度[mm/s]
   */
  DistanceStraight(double _targetDiatance, double _speed);

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
  double targetDistance;  // 目標距離
};

#endif
