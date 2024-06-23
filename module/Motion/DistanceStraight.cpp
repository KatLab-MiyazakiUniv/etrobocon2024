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

bool DistanceStraight::isRunPostConditionJudgement()
{
  Measurer measurer;
  // 現在の距離を取得する
  currentRightMotorCount = measurer.getRightCount();
  currentLeftMotorCount = measurer.getLeftCount();
  currentRightDistance = Mileage::calculateWheelMileage(currentRightMotorCount);
  currentLeftDistance = Mileage::calculateWheelMileage(currentLeftMotorCount);

  // 現在の距離が目標距離に到達したらループを終了する
  if((abs(currentRightDistance - initialRightDistance) >= targetDistance)
     && (abs(currentLeftDistance - initialLeftDistance) >= targetDistance)) {
    return true;
  }

  return false;
}

bool DistanceStraight::isRunPreConditionJudgement()
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

void DistanceStraight::logRunning()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, SMALL_BUF_SIZE, "Run DistanceStraight (Distance: %f, targetSpeed: %f)",
           targetDistance, targetSpeed);
  logger.log(buf);
}