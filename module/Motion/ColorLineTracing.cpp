/**
 * @file   ColorLineTracing.cpp
 * @brief  指定色ライントレース動作
 * @author CHIHAYATAKU
 */

#include "ColorLineTracing.h"

using namespace std;

ColorLineTracing::ColorLineTracing(COLOR _targetColor, double _targetSpeed, int _targetBrightness,
                                   const PidGain& _pidGain, bool& _isLeftEdge)
  : LineTracing(_targetSpeed, _targetBrightness, _pidGain, _isLeftEdge),
    targetColor(_targetColor) {};

ColorLineTracing::ColorLineTracing(COLOR _targetColor, double _targetSpeed, int _targetBrightness,
                                   const PidGain& _pidGain, bool& _isLeftEdge,
                                   bool _isRecoveryEnabled)
  : LineTracing(_targetSpeed, _targetBrightness, _pidGain, _isLeftEdge, _isRecoveryEnabled),
    targetColor(_targetColor) {};

bool ColorLineTracing::isMetPreCondition(double targetSpeed)
{
  char buf[SMALL_BUF_SIZE];

  // 目標の色がNoneかつtargetSpeed値が0のときwarningを出して終了する
  if(targetColor == COLOR::NONE && targetSpeed == 0.0) {
    snprintf(buf, SMALL_BUF_SIZE,
             "The targetColor passed to ColorLineTracing is NONE, and the targetSpeed value passed "
             "to ColorLineTracing is 0");
    logger.logWarning(buf);
    return false;
  }

  // targetSpeed値が0の場合はwarningを出して終了する
  if(targetSpeed == 0.0) {
    snprintf(buf, SMALL_BUF_SIZE, "The targetSpeed value passed to ColorLineTracing is 0");
    logger.logWarning(buf);
    return false;
  }

  // 目標の色がNoneのときwarningを出して終了する
  if(targetColor == COLOR::NONE) {
    snprintf(buf, SMALL_BUF_SIZE, "The targetColor passed to ColorLineTracing is NONE");
    logger.logWarning(buf);
    return false;
  }

  return true;
}

bool ColorLineTracing::isMetContinuationCondition()
{
  if(ColorJudge::getColor(measurer.getRawColor()) == targetColor) {
    colorCount++;
  } else {
    colorCount = 0;
  }
  // 指定された色をJUDGE_COUNT回連続で取得したときモータが止まる
  if(colorCount >= JUDGE_COUNT) return false;

  return true;
}

void ColorLineTracing::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* strWhetherIsLeftEdge = isLeftEdge ? "true" : "false";
  const char* strIsRecoveryEnabled = isRecoveryEnabled ? "true" : "false";

  snprintf(buf, LARGE_BUF_SIZE,
           "Run ColorLineTracing (targetColor: %s, targetSpeed: %.2f, targetBrightness: %d, "
           "gain: (%.2f,%.2f,%.2f), isLeftEdge: %s, isRecoveryEnabled: %s)",
           ColorJudge::colorToString(targetColor), targetSpeed, targetBrightness, pidGain.kp,
           pidGain.ki, pidGain.kd, strWhetherIsLeftEdge, strIsRecoveryEnabled);
  logger.log(buf);
}