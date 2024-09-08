/**
 * @file   AreaBCaptureAction.h
 * @brief  配置エリアBの撮影動作
 * @author keiya121
 */

#ifndef AREABCAPTUREACTION_H
#define AREABCAPTUREACTION_H

#include "CompositeMotion.h"
#include "PwmRotation.h"
#include "CorrectingRotation.h"
#include "ResetWheelsMotorPwm.h"
#include "Sleeping.h"
#include "CameraAction.h"


class AreaBCaptureAction : public CompositeMotion {
 public:
  /**
   * コンストラクタ
   * @param _milliSec1  1回目のスリープ時間(ミリ秒)
   * @param _targetAngle1 1回目の目標回転角度(deg) 0~360
   * @param _pwm1　1回目の回頭PWM値 0~100
   * @param _isClockwise1 1回目の回頭方向 true:時計回り, false:反時計回り
   * @param _pwmXr 角度補正回頭用のPWM値 0~100
   * @param _milliSec2 2回目のスリープ時間(ミリ秒)
   * @param _targetAngle2 2回目の目標回転角度(deg) 0~360
   * @param _pwm2 2回目の回頭PWM値 0~100
   * @param _isClockwise2　2回目の回頭方向 true:時計回り, false:反時計回り
   */
  AreaBCaptureAction(int _milliSec1, int _targetAngle1, int _pwm1, bool _isClockwise1, int _pwmXr,
                     int _milliSec2, int _targetAngle2, int _pwm2, bool _isClockwise2);

  /**
   * @brief 配置エリアBでのカメラ撮影動作を行う
   */
  void run() override;

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  int milliSec1;//1回目のスリープ時間(ミリ秒)
  int targetAngle1;//1回目の目標回転角度(deg)
  int pwm1;//1回目のPWM値
  bool isClockwise1;//1回目のPWM値
  int pwmXr;//角度補正回頭用のPWM値
  int milliSec2;//2回目のスリープ時間(ミリ秒)
  int targetAngle2;//2回目の目標回転角度(deg)
  int pwm2;//2回目の回頭PWM値
  bool isClockwise2;//2回目の回頭方向
};

#endif