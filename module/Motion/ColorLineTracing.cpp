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
    targetColor(_targetColor){};

bool ColorLineTracing::isMetPrecondition(double targetSpeed)
{
  char buf[LARGE_BUF_SIZE];

  // targetSpeed値が0の場合はwarningを出して終了する
  if(targetSpeed == 0.0) {
    snprintf(buf, LARGE_BUF_SIZE, "The targetSpeed value passed to ColorLineTracing is 0");
    logger.logWarning(buf);
    return false;
  }

  // 目標の色がNoneのときwarningを出して終了する
  if(targetColor == COLOR::NONE) {
    logger.logWarning("The targetColor passed to ColorLineTracing is NONE");
    return false;
  }

  return true;
}

bool ColorLineTracing::isMetPostcondition()
{
  COLOR currentColor = COLOR::NONE;

  currentColor = ColorJudge::getColor(measurer.getRawColor());
  if(currentColor == targetColor) {
    colorCount++;
  } else {
    colorCount = 0;
  }
  // 指定された色をJUDGE_COUNT回連続で取得
  if(colorCount >= JUDGE_COUNT) return false;

  return true;
}

void ColorLineTracing::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* str = isLeftEdge ? "true" : "false";

  snprintf(buf, LARGE_BUF_SIZE,
           "Run ColorLineTracing (targetColor: %s, targetSpeed: %.2f, targetBrightness: %d, "
           "gain: (%.2f,%.2f,%.2f), isLeftEdge: %s)",
           ColorJudge::colorToString(targetColor), targetSpeed, targetBrightness, pidGain.kp,
           pidGain.ki, pidGain.kd, str);
  logger.log(buf);
}