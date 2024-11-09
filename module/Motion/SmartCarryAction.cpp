/**
 * @file   DebrisRemovalAction.cpp
 * @brief  デブリリムーバルエリアにおける車体方向補正直進動作
 * @author CHIHAYATAKU takahashitom
 */

#include "SmartCarryAction.h"

using namespace std;

SmartCarryAction::SmartCarryAction(double _firstTargetSpeed, double _secondTargetSpeed,
                                   int _pwmForRotation)
  : firstTargetSpeed(_firstTargetSpeed),
    secondTargetSpeed(_secondTargetSpeed),
    pwmForRotation(_pwmForRotation) {};

void SmartCarryAction::run()
{
  if(!isMetPreCondition()) {
    return;
  }

  logRunning();

  CorrectingRotation correctingRotation(pwmForRotation, tolerance, targetColor);
  correctingRotation.run();

  correctedAngle = correctingRotation.getCorrectionAngle();

  if(correctedAngle >= 0) {
    runToLowwerCourse();
  } else {
    if(correctedAngle >= 0) runToUpperCourse();
  }
}

/**
 * @brief 動作を行う際の事前条件判定をする
 */
bool SmartCarryAction::isMetPreCondition()
{
  char buf[SMALL_BUF_SIZE];

  if(firstTargetSpeed <= 0.0) {
    logger.logWarning("The firstTargetSpeed value passed to ColorStraight is 0 or less");
    return false;
  }

  if(secondTargetSpeed <= 0) {
    logger.logWarning("The secondTargetSpeed value passed to ColorStraight is 0 or less");
    return false;
  }

  if(pwmForRotation <= 0.0) {
    logger.logWarning("The pwmForRotation passed to PwmRotation is 0 or less");
    return false;
  }

  return true;
}

void SmartCarryAction::runToUpperCourse()
{
  char buf[LARGE_BUF_SIZE];

  firstStraightDistance = baseLength / cos(abs(correctedAngle) * 2 * M_PI / 180);
  secondStraightDistance = sin(abs(correctedAngle) * 2 * M_PI / 180) * firstStraightDistance;

  DistanceStraight firstDistanceStraight(firstStraightDistance, firstTargetSpeed);

  firstDistanceStraight.run();
  Sleeping sleeping(200);
  sleeping.run();

  sleeping.run();

  secondRotationAngle = int(90 + abs(correctedAngle)) * rotationBias;
  PwmRotation pwmRotation(secondRotationAngle, pwmForRotation, isClockwise);
  pwmRotation.run();

  DistanceStraight secondDistanceStraight(secondStraightDistance, secondTargetSpeed);

  snprintf(buf, LARGE_BUF_SIZE,
           "{firstStraightDistance : %f, secondStraightDistance : %f, secondホゲータ : %d}",
           firstDistanceStraight, secondStraightDistance,
           int((90 - abs(correctedAngle)) * rotationBias));
  logger.log(buf);
}

void SmartCarryAction::runToLowwerCourse()
{
  char buf[LARGE_BUF_SIZE];

  firstStraightDistance = baseLength / cos(abs(correctedAngle) * 2 * M_PI / 180);
  secondStraightDistance
      = secondStraightDistance - sin(abs(correctedAngle) * 2 * M_PI / 180) * firstStraightDistance;

  DistanceStraight firstDistanceStraight(firstStraightDistance, 150);

  firstDistanceStraight.run();
  Sleeping sleeping(200);
  sleeping.run();

  sleeping.run();

  secondRotationAngle = int((90 - abs(correctedAngle)) * rotationBias);
  PwmRotation pwmRotation(secondRotationAngle, pwmForRotation, isClockwise);
  pwmRotation.run();

  DistanceStraight secondDistanceStraight(secondStraightDistance, 150);

  snprintf(buf, LARGE_BUF_SIZE,
           "{firstStraightDistance : %f, secondStraightDistance : %f, secondホゲータ : %d}",
           firstDistanceStraight, secondStraightDistance, secondRotationAngle);
  logger.log(buf);
}

/**
 * @brief 実行のログを取る
 */
void SmartCarryAction::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* isClockwiseStr = isClockwise ? "true" : "false";
  snprintf(buf, LARGE_BUF_SIZE,
           "{firstTargetSpeed : %f, secondStraightDistance : %f, pwmForRotation : %d}",
           firstTargetSpeed, secondStraightDistance, pwmForRotation);
  logger.log(buf);
}