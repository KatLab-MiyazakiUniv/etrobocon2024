/**
 * @file   CorrectingRotation.h
 * @brief  プラレール・背景撮影のための角度補正回頭動作
 * @author bizyutyu CHIHAYATAKU takahashitom
 */

#ifndef CORRECTINGROTATION_H
#define CORRECTINGROTATION_H

#include "CompositeMotion.h"
#include "PwmRotation.h"
#include "Sleeping.h"
#include "ColorJudge.h"

class CorrectingRotation : public CompositeMotion {
 public:
  /**
   * コンストラクタ
   * @param _pwm 角度補正回頭時のPWM値
   * @param _correctionTolerance  補正許容角度
   * @param _color 検出する矩形の色（"YELLOW" or "RED"）
   */
  CorrectingRotation(int _pwm = 50, int _correctionTolerance = 0, COLOR _color = COLOR::YELLOW);

  /**
   * @brief プラレール・背景撮影のための角度補正回頭動作を行う
   */
  void run() override;

  /**
   * @brief 補正角度を取得する
   */
  int getCorrectionAngle();

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  int pwm;                  // 指定PWM値 0~100
  int correctionAngle = 0;  // 補正角度 0~360
  COLOR color;              // 検出する矩形の色
  bool isClockwise;
  int correctionTolerance;  // 補正許容値
};
#endif
