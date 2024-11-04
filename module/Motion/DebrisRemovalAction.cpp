/**
 * @file   DebrisRemovalAction.cpp
 * @brief  デブリリムーバルエリアにおける車体方向補正直進動作
 * @author CHIHAYATAKU takahashitom
 */

#include "DebrisRemovalAction.h"

using namespace std;

DebrisRemovalAction::DebrisRemovalAction(double _targetSpeed, int _pwmForRotation,
                                         double _rotationBias)
  : targetSpeed(_targetSpeed), pwmForRotation(_pwmForRotation), rotationBias(_rotationBias)
{
  preLeftCount = measurer.getLeftCount();
  preRightCount = measurer.getRightCount();
  preDistance = Mileage::calculateMileage(preRightCount, preLeftCount);
};

void DebrisRemovalAction::run()
{
  char buf[LARGE_BUF_SIZE];

  if(!isMetPreCondition()) {
    return;
  }
  ColorStraight colorStraight(targetColor, targetSpeed);

  colorStraight.run();
  Sleeping sleeping(200);
  sleeping.run();

  int postLeftCount = measurer.getLeftCount();
  int postRightCount = measurer.getRightCount();

  double mileage = Mileage::calculateMileage(postRightCount, postLeftCount) - preDistance;

  sleeping.run();
  correctionAngle = int(acos(sideLength / mileage) * 180 / M_PI);
  isClockwise = (postRightCount - preRightCount) > (postLeftCount - preLeftCount);

  PwmRotation pwmRotation(correctionAngle * rotationBias, pwmForRotation, isClockwise);
  pwmRotation.run();

  snprintf(buf, LARGE_BUF_SIZE, "{correctionAngle : %d, mileage : %f}", correctionAngle, mileage);
  logger.logWarning(buf);
}

/**
 * @brief 動作を行う際の事前条件判定をする
 */
bool DebrisRemovalAction::isMetPreCondition()
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
void DebrisRemovalAction::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* isClockwiseStr = isClockwise ? "true" : "false";
  snprintf(buf, LARGE_BUF_SIZE,
           "Run DebrisRemovalAction (targetSpeed: %f, pwmForRotation: %d, rotationBias: %s)",
           targetSpeed, pwmForRotation, rotationBias);
  logger.log(buf);
}