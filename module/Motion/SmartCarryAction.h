/**
 * @file   DebrisRemovalAction.h
 * @brief  デブリリムーバルエリアにおける車体方向補正直進動作
 * @author CHIHAYATAKU takahashitom
 */

#ifndef SMARTCARRYACTION_H
#define SMARTCARRYACTION_H

#include "CompositeMotion.h"
#include "PwmRotation.h"
#include "CorrectingRotation.h"
#include "DistanceStraight.h"
#include "Sleeping.h"
#include <cmath>

class SmartCarryAction : public CompositeMotion {
 public:
  /**
   * コンストラクタ
   * @param _targetSpeed 直進時の速度
   * @param _pwmForRotation 回頭時のPWM
   * @param _rotationBias 回頭角度のバイアス
   */
  SmartCarryAction(double _firstTargetSpeed, double _secondTargetSpeed, int _pwmForRotation);

  /**
   * @brief 直進と黒線に直角になるように車体の補正動作を行う
   */
  void run() override;

  /**
   * @brief 動作を行う際の事前条件判定をする
   */
  bool isMetPreCondition();

  /**
   * @brief コース上方向に回頭した場合の動作を実行する
   */
  void runToUpperCourse();

  /**
   * @brief コース下方向に回頭した場合の動作を実行する
   */
  void runToLowwerCourse();

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  double firstTargetSpeed;   // 直進時の速度
  double secondTargetSpeed;  // 直進時の速度
  int pwmForRotation;        // 回頭時のPWM
  int correctedAngle;
  double rotationBias = 0.7;            // 初期距離
  double secondRotationBias = 0.75;
  bool isClockwise = true;              // 回頭方向
  double firstStraightDistance;         // ボトルを持つための最初の直進
  double secondStraightDistance;  // ボトルを置くまでの直進
  int secondRotationAngle;
  COLOR targetColor = COLOR::RED;  // 色指定距離の目標色
  int tolerance = 2;
  Logger logger;

  const double baseLength = 640.0;  // デブリ最後の黒線からスマートキャリーの一番奥の青端までの距離
};
#endif