/**
 * @file   AreaACameraAction.cpp
 * @brief  配置エリアAにおけるミニフィグ撮影動作
 * @author takahashitom
 */

#include "AreaACameraAction.h"

using namespace std;

AreaACameraAction::AreaACameraAction(int _position, bool _isClockwise, int _preTargetAngle,
                                     int _postTargetAngle, int _rotationPwm, double _targetDistance,
                                     double _speed)
  : isClockwise(_isClockwise),
    preTargetAngle(_preTargetAngle),
    postTargetAngle(_postTargetAngle),
    rotationPwm(_rotationPwm),
    targetDistance(_targetDistance),
    targetSpeed(_speed)
{
  // ミニフィグの物体検出のラベル付けが（正面：0, 背面：1, 右向き：2, 左向き：3）となっているため、
  // ポジション１からの撮影時はフラグが２だった場合に撮影を行う。同様に、ポジション２からの撮影はフラグが１だった場合に行われる。
  if(_position == 1) {
    flag = 2;
  } else if(_position == 2) {
    flag = 1;
  } else {
    flag = _position;
  }
};

void AreaACameraAction::run()
{
  // 事前条件を判定する
  if(!isMetPreCondition()) {
    return;
  }

  PwmRotation prePR(preTargetAngle, rotationPwm, isClockwise);
  PwmRotation postPR(postTargetAngle, rotationPwm, !isClockwise);
  Sleeping sl(200);  // 回頭前用のsleep

  // 撮影のための回頭をする
  if(preTargetAngle != 0) {
    sl.run();
    prePR.run();
  }

  // 前進でフィグに近づく
  DistanceStraight dsToFig(targetDistance, targetSpeed);
  dsToFig.run();

  // フロントカメラで画像を取得する
  CameraAction cameraAction(subject);
  cameraAction.run();

  // 後退で黒線へ復帰
  DistanceStraight dsToLine(targetDistance, -1.0 * targetSpeed);
  dsToLine.run();

  // 黒線復帰のための回頭をする
  if(postTargetAngle != 0) {
    sl.run();
    postPR.run();
  }
}

bool AreaACameraAction::isMetPreCondition()
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

  // フラグファイルの存在確認
  char SKIP_FLAG_PATH[LARGE_BUF_SIZE];
  snprintf(SKIP_FLAG_PATH, LARGE_BUF_SIZE, "%s%d_skip_camera_action.flag", ETROBO_PATH, flag);
  FILE* fp = fopen(SKIP_FLAG_PATH, "r");

  // フラグファイルが存在する場合、撮影を行う
  if(fp != NULL) {
    fclose(fp);
    return true;
  }

  // フラグファイルが存在しない場合
  for(int i = -1; i < 4; i++) {
    if(i == flag) continue;
    char FLAG_PATH[LARGE_BUF_SIZE];
    snprintf(FLAG_PATH, LARGE_BUF_SIZE, "%s%d_skip_camera_action.flag", ETROBO_PATH, i);
    FILE* fp2 = fopen(FLAG_PATH, "r");
    // 他の位置のフラグファイルが存在する場合撮影をスキップする
    if(fp2 != NULL) {
      snprintf(buf, LARGE_BUF_SIZE, "Skip shooting because flag is %d.", i);
      logger.logHighlight(buf);
      fclose(fp2);
      return false;
    }
  }

  return true;
}

void AreaACameraAction::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* isClockwiseStr = isClockwise ? "true" : "false";

  snprintf(buf, LARGE_BUF_SIZE,
           "Run AreaACameraAction (flag: %d, isClockwise: %s, preTargetAngle: %d, postTargetAngle: "
           "%d, rotationPwm: %d, targetDistance: %f, speed:%f)",
           flag, isClockwiseStr, preTargetAngle, postTargetAngle, rotationPwm, targetDistance,
           targetSpeed);
  logger.log(buf);
}