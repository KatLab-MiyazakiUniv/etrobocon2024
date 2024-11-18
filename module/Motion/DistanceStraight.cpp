/**
 * @file   DistanceStraight.cpp
 * @brief  目標距離まで直進するクラス
 * @author bizyutyu
 */

#include "DistanceStraight.h"
using namespace std;

DistanceStraight::DistanceStraight(double _targetDistance, double _targetSpeed)
  : Straight(_targetSpeed), targetDistance(_targetDistance)
{
}

bool DistanceStraight::isMetPreCondition()
{
  char buf[LARGE_BUF_SIZE];
  // 目標速度値が0の場合は終了する
  if(targetSpeed == 0) {
    logger.logWarning("The targetSpeed value passed to DistanceStraight is 0");
    return false;
  }
  // 目標距離の値が0以下の場合はwarningを出して終了する
  if(targetDistance <= 0) {
    snprintf(buf, LARGE_BUF_SIZE, "The targetDistance value passed to DistanceStraight is %.2f",
             targetDistance);
    logger.logWarning(buf);
    return false;
  }

  return true;
}

bool DistanceStraight::isMetContinuationCondition()
{
  // 現在の走行距離を取得する
  double currentRightMotorCount = measurer->getRightCount();
  double currentLeftMotorCount = measurer->getLeftCount();
  double currentDistance = Mileage::calculateMileage(currentRightMotorCount, currentLeftMotorCount);

  // 現在の走行距離が目標走行距離に達した場合falseを返す
  // ここでは、左右どちらとも達したかどうかで判断する
  if((fabs(currentDistance - initialDistance) >= targetDistance)) {
    return false;
  }

  // 現在の走行距離が目標走行距離に達していなければtrueを返す
  return true;
}

void DistanceStraight::logRunning()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, SMALL_BUF_SIZE, "Run DistanceStraight (Distance: %f, targetSpeed: %f)",
           targetDistance, targetSpeed);
  logger.log(buf);
}
