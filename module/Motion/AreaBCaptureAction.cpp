/**
 * @file   AreaBCaptureAction.cpp
 * @brief  配置エリアBの撮影動作
 * @author keiya121
 */

#include "AreaBCaptureAction.h"
using namespace std;

AreaBCaptureAction::AreaBCaptureAction(int _milliSec1, int _targetAngle1, int _pwm1,
                                       bool _isClockwise1, int _pwmXr, int _milliSec2, int _targetAngle2,
                                       int _pwm2, bool _isClockwise2)
  : milliSec1(_milliSec1),
    targetAngle1(_targetAngle1),
    pwm1(_pwm1),
    isClockwise1(_isClockwise1),
    pwmXr(_pwmXr),
    milliSec2(_milliSec2),
    targetAngle2(_targetAngle2),
    pwm2(_pwm2),
    isClockwise2(_isClockwise2)
{
}

void AreaBCaptureAction::run()
{
  // 配置エリアBで必要な動作をインスタンス化する
  Sleeping sl_1(milliSec1);
  PwmRotation pr_1(targetAngle1, pwm1, isClockwise1);
  CorrectingRotation xr(pwmXr);
  ResetWheelsMotorPwm rm;
  CameraAction ca(CameraAction::Subject::PLARAIL);
  Sleeping sl_2(milliSec2);
  PwmRotation pr_2(targetAngle2, pwm2, isClockwise2);

  // カメラ撮影動作の実行
  sl_1.run();
  pr_1.run();
  rm.run();
  xr.run();
  rm.run();
  ca.run();
  sl_2.run();
  pr_2.run();
}

void AreaBCaptureAction::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  snprintf(buf, LARGE_BUF_SIZE, "Run AreaBCaptureAction ()");
  logger.log(buf);
}