/**
 * @file   DebrisRemovalFirst.cpp
 * @brief  デブリリムーバルエリアにおける車体方向補正直進動作前半
 * @author CHIHAYATAKU takahashitom
 */

#include "DebrisRemovalFirst.h"

using namespace std;

DebrisRemovalFirst::DebrisRemovalFirst(double _targetSpeed, int _pwmForRotation,
                                       double _rotationBias, bool _isClockwise)
  : targetSpeed(_targetSpeed),
    pwmForRotation(_pwmForRotation),
    rotationBias(_rotationBias),
    isClockwise(_isClockwise) {};

void DebrisRemovalFirst::run()
{
  char buf[LARGE_BUF_SIZE];
  Sleeping sleeping(200);

  if(!isMetPreCondition()) {
    return;
  }

  double preRotationLeftDistance = Mileage::calculateWheelMileage(measurer.getLeftCount());
  double preRotationRightDistance = Mileage::calculateWheelMileage(measurer.getRightCount());

  PwmRotation firstPwmRotation(25, pwmForRotation, isClockwise);
  sleeping.run();
  firstPwmRotation.run();

  double postRotationLeftDistance = Mileage::calculateWheelMileage(measurer.getLeftCount());
  double postRotationRightDistance = Mileage::calculateWheelMileage(measurer.getRightCount());

  double firstRotationDistance = (abs(postRotationLeftDistance - preRotationLeftDistance)
                                  + abs(postRotationRightDistance - preRotationRightDistance))
                                 / 2;

  ColorStraight colorStraight(targetColor, 200);
  colorStraight.run();

  preRotationLeftDistance = Mileage::calculateWheelMileage(measurer.getLeftCount());
  preRotationRightDistance = Mileage::calculateWheelMileage(measurer.getRightCount());

  PwmRotation secondPwmRotation(25, pwmForRotation, !isClockwise);
  sleeping.run();
  secondPwmRotation.run();

  postRotationLeftDistance = Mileage::calculateWheelMileage(measurer.getLeftCount());
  postRotationRightDistance = Mileage::calculateWheelMileage(measurer.getRightCount());

  double secondRotationDistance = (abs(postRotationLeftDistance - preRotationLeftDistance)
                                   + abs(postRotationRightDistance - preRotationRightDistance))
                                  / 2;

  double rotationDistanceDiff = secondRotationDistance - firstRotationDistance;

  // 2回目の回頭終了時の走行体の向きフラグ
  // 0: 黒線に対して垂直, -1: 黒線に対して回頭不足,
  // 1: 黒線に対して回頭しすぎ
  int directionFlag = 0;
  if(-10 <= rotationDistanceDiff && rotationDistanceDiff <= 10) {
    directionFlag = 0;
  } else if(rotationDistanceDiff < -10) {
    directionFlag = -1;
  } else if(10 < rotationDistanceDiff) {
    directionFlag = 1;
  }

  snprintf(buf, LARGE_BUF_SIZE,
           "{firstRotationDistance : %f, secondRotationDistance : %f, directionFlag: %d}",
           firstRotationDistance, secondRotationDistance, directionFlag);
  logger.log(buf);

  preLeftCount = measurer.getLeftCount();
  preRightCount = measurer.getRightCount();
  preDistance = Mileage::calculateMileage(preRightCount, preLeftCount);

  DistanceStraight distanceStraight(600, targetSpeed);
  distanceStraight.run();
  colorStraight.run();
  sleeping.run();

  int postLeftCount = measurer.getLeftCount();
  int postRightCount = measurer.getRightCount();

  double mileage = Mileage::calculateMileage(postRightCount, postLeftCount) - preDistance;

  int leftCountDiff = postLeftCount - preLeftCount;
  int rightCountDiff = postRightCount - preRightCount;

  correctionAngle = (int(acos(sideLength / mileage) * 180 / M_PI) * rotationBias) <= 2
                        ? 0
                        : (int(acos(sideLength / mileage) * 180 / M_PI) * rotationBias);

  if(abs(rightCountDiff - leftCountDiff) <= 10) {
    if(directionFlag = 0) {
      correctionAngle = 0;
    } else if(directionFlag = -1) {
      isClockwise = !isClockwise;
    }
  } else {
    isClockwise = (rightCountDiff) > (leftCountDiff);
  }

  PwmRotation pwmRotation(correctionAngle, pwmForRotation, isClockwise);
  sleeping.run();
  pwmRotation.run();

  snprintf(buf, LARGE_BUF_SIZE, "{correctionAngle : %d, mileage : %f, preD: %f, LC: %d, RC: %d}",
           correctionAngle, mileage, preDistance, postLeftCount - preLeftCount,
           postRightCount - preRightCount);
  logger.log(buf);
}

/**
 * @brief 動作を行う際の事前条件判定をする
 */
bool DebrisRemovalFirst::isMetPreCondition()
{
  char buf[SMALL_BUF_SIZE];

  if(targetSpeed <= 0.0) {
    logger.logWarning("The targetSpeed value passed to ColorStraight is 0 or less");
    return false;
  }

  if(pwmForRotation <= 0) {
    logger.logWarning("The pwm passed to PwmRotation is 0 or less");
    return false;
  }

  if(rotationBias <= 0.0) {
    logger.logWarning("The bias passed to PwmRotation is 0 or less");
    return false;
  }

  return true;
}

/**
 * @brief 実行のログを取る
 */
void DebrisRemovalFirst::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* isClockwiseStr = isClockwise ? "true" : "false";
  snprintf(buf, LARGE_BUF_SIZE,
           "Run DebrisRemovalFirst (targetSpeed: %f, pwmForRotation: %d, rotationBias: %f)",
           targetSpeed, pwmForRotation, rotationBias);
  logger.log(buf);
}