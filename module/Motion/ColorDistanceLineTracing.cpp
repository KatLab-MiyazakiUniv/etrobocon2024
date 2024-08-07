/**
 * @file   ColorDistanceLineTracing.cpp
 * @brief  色指定距離ライントレース動作
 * @author Negimarge
 */

#include "ColorDistanceLineTracing.h"
using namespace std;

ColorDistanceLineTracing::ColorDistanceLineTracing(COLOR _targetColor, double _targetDistance,
                                                   double _targetSpeed, int _targetBrightness,
                                                   const PidGain& _pidGain, bool& _isLeftEdge)
  : LineTracing(_targetSpeed, _targetBrightness, _pidGain, _isLeftEdge),
    targetColor(_targetColor),
    targetDistance(_targetDistance) {};

bool ColorDistanceLineTracing::isMetPreCondition(double targetSpeed)
{
  char buf[SMALL_BUF_SIZE];

  // targetDistance値が0以下かつtargetSpeed値が0のときwarningを出して終了する
  if(targetDistance <= 0.0 && targetSpeed == 0.0) {
    snprintf(buf, SMALL_BUF_SIZE,
             "The targetDistance value passed to DistanceLineTracing is %.2f, and the targetSpeed "
             "value passed "
             "to ColorLineTracing is 0",
             targetDistance);
    logger.logWarning(buf);
    return false;
  }

  // 目標の色がNoneのときwarningを出して終了する
  if(targetColor == COLOR::NONE) {
    logger.logWarning("The targetColor passed to ColorStraight is NONE");
    return false;
  }

  // targetSpeed値が0の場合はwarningを出して終了する
  if(targetSpeed == 0.0) {
    snprintf(buf, SMALL_BUF_SIZE, "The targetSpeed value passed to DistanceLineTracing is 0");
    logger.logWarning(buf);
    return false;
  }

  // targetDistance値が0以下の場合はwarningを出して終了する
  if(targetDistance <= 0.0) {
    snprintf(buf, SMALL_BUF_SIZE, "The targetDistance value passed to DistanceLineTracing is %.2f",
             targetDistance);
    logger.logWarning(buf);
    return false;
  }

  return true;
}

bool ColorDistanceLineTracing::isMetContinuationCondition()
{
  if(ColorJudge::getColor(measurer.getRawColor()) == targetColor) {
    colorCount++;
  } else {
    colorCount = 0;
  }

  // (走行距離が目標距離に到達)||(指定された色をJUDGE_COUNT回連続で取得したとき)モータが止まる
  if((fabs(Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount())
           - initDistance)
      >= targetDistance)
     || (colorCount >= JUDGE_COUNT))
    return false;

  return true;
}

void ColorDistanceLineTracing::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* strWhetherIsLeftEdge = isLeftEdge ? "true" : "false";

  snprintf(buf, LARGE_BUF_SIZE,
           "Run ColorDistanceLineTracing (targetColor: %s, targetDistance: %.2f, targetSpeed: "
           "%.2f, targetBrightness: "
           "%d, gain: (%.2f,%.2f,%.2f), isLeftEdge: %s)",
           ColorJudge::colorToString(targetColor), targetDistance, targetSpeed, targetBrightness,
           pidGain.kp, pidGain.ki, pidGain.kd, strWhetherIsLeftEdge);
  logger.log(buf);
}