/**
 * @file   AreaBCameraAction.cpp
 * @brief  配置エリアBにおけるプラレール・背景撮影動作
 * @author keiya121 CHIHAYATAKU
 */

#include "AreaBCameraAction.h"

using namespace std;

AreaBCameraAction::AreaBCameraAction(int _preTargetAngle, int _prePwm, bool _isClockwise,
                                     int _pwmXr, int _postTargetAngle, int _postPwm)

  : preTargetAngle(_preTargetAngle),
    prePwm(_prePwm),
    isClockwise(_isClockwise),
    pwmXr(_pwmXr),
    postTargetAngle(_postTargetAngle),
    postPwm(_postPwm) {};

void AreaBCameraAction::run()
{
  // 事前条件を判定する
  if(!isMetPreCondition()) {
    return;
  }

  // 撮影に必要な動作をインスタンス化する
  Sleeping sl(200);
  ResetWheelsMotorPwm rm;
  PwmRotation prePR(preTargetAngle, prePwm, isClockwise);
  PwmRotation postPR(postTargetAngle, postPwm, !isClockwise);
  CorrectingRotation xr(pwmXr, colorXr);
  CameraAction ca(CameraAction::Subject::PLARAIL);

  // 撮影のための回頭をする
  if(preTargetAngle != 0) {
    sl.run();
    prePR.run();
    rm.run();
  }

  // 角度補正回頭をする
  sl.run();
  xr.run();
  rm.run();

  // 撮影動作を行う
  ca.run();

  // 黒線復帰のための回頭をする
  if(postTargetAngle != 0) {
    sl.run();
    postPR.run();
    rm.run();
  }
}

bool AreaBCameraAction::isMetPreCondition()
{
  char buf[LARGE_BUF_SIZE];

  // preTargetAngleが0未満または360以上の場合はwarningを出して終了する
  if(preTargetAngle < 0 || preTargetAngle >= 360) {
    snprintf(buf, LARGE_BUF_SIZE, "The preTargetAngle value passed to preRotation is %d",
             preTargetAngle);
    logger.logWarning(buf);
    return false;
  } else if(preTargetAngle == 0) {
    snprintf(buf, LARGE_BUF_SIZE, "The preTargetAngle value passed to preRotation is %d",
             preTargetAngle);
    logger.logHighlight(buf);
  }

  // postTargetAngleが0未満または360以上の場合はwarningを出して終了する
  if(postTargetAngle < 0 || postTargetAngle >= 360) {
    snprintf(buf, LARGE_BUF_SIZE, "The postTargetAngle value passed to postRotation is %d",
             postTargetAngle);
    logger.logWarning(buf);
    return false;
  } else if(postTargetAngle == 0) {
    snprintf(buf, LARGE_BUF_SIZE, "The postTargetAngle value passed to postRotation is %d",
             postTargetAngle);
    logger.logHighlight(buf);
  }

  return true;
}

void AreaBCameraAction::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* isClockwiseStr = isClockwise ? "true" : "false";
  snprintf(buf, LARGE_BUF_SIZE,
           "Run AreaBCameraAction (preTargetAngle: %d, prePwm: %d"
           "isClockwise: %d, pwmXr: %d "
           "postTargetAngle: %d, postPwm: %d)",
           preTargetAngle, prePwm, isClockwise, pwmXr, postTargetAngle, postPwm);
  logger.log(buf);
}