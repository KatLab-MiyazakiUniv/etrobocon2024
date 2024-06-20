/**
 * @file   DistanceLineTracing.cpp
 * @brief  指定距離ライントレース動作
 * @author CHIHAYATAKU
 */

#include "DistanceLineTracing.h"
using namespace std;

DistanceLineTracing::DistanceLineTracing(double _targetDistance, double _targetSpeed,
                                         int _targetBrightness, const PidGain& _pidGain,
                                         bool& _isLeftEdge)
  : LineTracing(_targetSpeed, _targetBrightness, _pidGain, _isLeftEdge),
    targetDistance(_targetDistance){};

bool DistanceLineTracing::isMetPrecondition(double targetSpeed)
{
  char buf[LARGE_BUF_SIZE];

  // targetSpeed値が0の場合はwarningを出して終了する
  if(targetSpeed == 0.0) {
    snprintf(buf, LARGE_BUF_SIZE, "The targetSpeed value passed to DistanceLineTracing is 0");
    logger.logWarning(buf);
    return false;
  }

  // targetDistance値が0以下の場合はwarningを出して終了する
  if(targetDistance <= 0.0) {
    snprintf(buf, LARGE_BUF_SIZE, "The targetDistance value passed to DistanceLineTracing is %.2f",
             targetDistance);
    logger.logWarning(buf);
    return false;
  }

  return true;
}

bool DistanceLineTracing::isMetPostcondition()
{
  // 初期値を代入
  currentDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());

  // 走行距離が目標距離に到達
  if(abs(currentDistance - initialDistance) >= targetDistance) return false;

  return true;
}

void DistanceLineTracing::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* str = isLeftEdge ? "true" : "false";

  snprintf(buf, LARGE_BUF_SIZE,
           "Run DistanceLineTracing (targetDistance: %.2f, targetSpeed: %.2f, targetBrightness: "
           "%d, gain: (%.2f,%.2f,%.2f), isLeftEdge: %s)",
           targetDistance, targetSpeed, targetBrightness, pidGain.kp, pidGain.ki, pidGain.kd, str);
  logger.log(buf);
}