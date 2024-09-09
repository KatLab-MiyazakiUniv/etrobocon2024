/**
 * @file   AreaBCameraAction.h
 * @brief  配置エリアBにおけるプラレール・背景撮影動作
 * @author keiya121
 */

#ifndef AREABCAMERAACTION_H
#define AREABCAMERAACTION_H

#include "CompositeMotion.h"
#include "PwmRotation.h"
#include "CorrectingRotation.h"
#include "ResetWheelsMotorPwm.h"
#include "Sleeping.h"
#include "CameraAction.h"

class AreaBCameraAction : public CompositeMotion {
 public:
  /**
   * コンストラクタ
   * @param _preTargetAngle 1回目の回頭目標回転角度(deg) 0~360
   * @param _prePwm　1回目の回頭PWM値 0~100
   * @param _isClockwise 1回目の回頭方向 true:時計回り, false:反時計回り
   * @param _pwmXr 角度補正回頭用のPWM値 0~100
   * @param _postTargetAngle 2回目の回頭目標回転角度(deg) 0~360
   * @param _postPwm 2回目の回頭PWM値 0~100
   */
  AreaBCameraAction(int _preTargetAngle, int _prePwm, bool _isClockwise, int _pwmXr,
                    int _postTargetAngle, int _postPwm);

  /**
   * @brief 配置エリアBでのカメラ撮影動作を行う
   */
  void run() override;

  /**
   * @brief 撮影動作を行う際の事前条件判定をする
   */
  bool isMetPrecondition();

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  int preTargetAngle;   // 1回目の回頭目標回転角度(deg)
  int prePwm;           // 1回目の回頭PWM値
  bool isClockwise;     // 1回目の回頭方向
  int pwmXr;            // 角度補正回頭用のPWM値
  int postTargetAngle;  // 2回目の回頭目標回転角度(deg)
  int postPwm;          // 2回目の回頭PWM値
};

#endif