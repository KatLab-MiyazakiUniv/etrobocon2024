/**
 * @file   DebrisRemovalAction.h
 * @brief  デブリリムーバルエリアにおける車体方向補正直進動作
 * @author CHIHAYATAKU takahashitom
 */

#ifndef DEBRISREMOVALACTION_H
#define DEBRISREMOVALACTION_H

#include "CompositeMotion.h"
#include "PwmRotation.h"
#include "ColorStraight.h"
#include "Sleeping.h"
#include <cmath>

class DebrisRemovalAction : public CompositeMotion {
 public:
  /**
   * コンストラクタ
   * @param _targetSpeed 直進時の速度
   * @param _pwmForRotation 回頭時のPWM
   * @param _rotationBias 回頭角度のバイアス
   */
  DebrisRemovalAction(double _targetSpeed, int _pwmForRotation, double _rotationBias);

  /**
   * @brief 直進と黒線に直角になるように車体の補正動作を行う
   */
  void run() override;

  /**
   * @brief 動作を行う際の事前条件判定をする
   */
  bool isMetPreCondition();

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  double targetSpeed;   // 直進時の速度
  int pwmForRotation;   // 回頭時のPWM
  double rotationBias;  // 回頭角度のバイアス
  int correctionAngle;  // 補正角度
  int preLeftCount;
  int preRightCount;
  double preDistance;                // 初期距離
  bool isClockwise;                  // 回頭方向
  COLOR targetColor = COLOR::BLACK;  // 色指定距離の目標色
  Measurer measurer;
  Logger logger;

  const double sideLength = 355.0;  // デブリのひと区画の一辺の長さ
};
#endif