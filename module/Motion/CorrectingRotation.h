/**
 * @file   CorrectingRotation.h
 * @brief  プラレール・背景撮影のための角度補正回頭動作
 * @author bizyutyu CHIHAYATAKU
 */

#ifndef CORRECTINGROTATION_H
#define CORRECTINGROTATION_H

#include "CompositeMotion.h"
#include "PwmRotation.h"
#include "Sleeping.h"

class CorrectingRotation : public CompositeMotion {
 public:
  /**
   * コンストラクタ
   * @param _pwm 角度補正回頭時のPWM値
   * @param _color 検出する矩形の色（"yellow" or "red"）
   */
  CorrectingRotation(int _pwm = 50, const char* _color = "yellow");

  /**
   * @brief プラレール・背景撮影のための角度補正回頭動作を行う
   */
  void run() override;

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  int pwm;              // 指定PWM値 0~100
  int correctionAngle;  // 補正角度 0~360
  const char* color;    // 検出する矩形の色
};
#endif
