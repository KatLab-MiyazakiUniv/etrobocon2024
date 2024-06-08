/**
 * @file   PwmRotation.h
 * @brief  Pwm指定回頭動作
 * @author takahashitom
 */

#ifndef PWMROTATION_H
#define PWMROTATION_H

#include "Rotation.h"

class PwmRotation : public Rotation {
 public:
  /**
   * コンストラクタ
   * @param _targetAngle 目標回転角度(deg) 0~360
   * @param _pwm PWM値 0~100
   * @param _isClockwise 回頭方向 ture:時計回り, false:反時計回り
   */
  PwmRotation(int _targetAngle, int _pwm, bool _isClockwise);

  /**
   * @brief 回頭する
   */
  using Rotation::run;

  /**
   * @brief 回頭する際の事前条件判定をする
   */
  bool isMetPrecondition() override;

  /**
   * @brief 回頭する際の継続条件判定をする　返り値がfalseでモーターが止まる
   * @param leftSign 左車輪の回転方向
   * @param rightSign 右車輪の回転方向
   */
  bool isMetPostcondition(double initLeftMileage, double initRightMileage, int leftSign,
                          int rightSign) override;

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  int targetAngle;  // 目標回転角度(deg) 0~360
};

#endif