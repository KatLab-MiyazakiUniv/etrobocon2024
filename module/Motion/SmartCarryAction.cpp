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
    runToUpperCourse();
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

  firstStraightDistance = baseLength / cos(abs(correctedAngle* 2) * M_PI / 180);
  secondStraightDistance = sqrt(firstStraightDistance*firstStraightDistance - baseLength*baseLength) + 750.0;
  secondRotationAngle = int((90 + abs(correctedAngle*2)) * rotationBias);

  if (abs(correctedAngle) > 17) {
    firstStraightDistance = 650;
    secondStraightDistance = secondStraightDistance - 250;
  }
  DistanceStraight firstDistanceStraight(firstStraightDistance, firstTargetSpeed);
  firstDistanceStraight.run();
  Sleeping sleeping(200);
  sleeping.run();


  snprintf(buf, LARGE_BUF_SIZE,
           "{firstStraightDistance : %f, secondStraightDistance : %f, secondホゲータ : %d}",
           firstStraightDistance, secondStraightDistance,
           secondRotationAngle);
  logger.log(buf);
  PwmRotation pwmRotation(secondRotationAngle, 65, isClockwise);
  pwmRotation.run();

  DistanceStraight secondDistanceStraight(secondStraightDistance, secondTargetSpeed);
  secondDistanceStraight.run();

  snprintf(buf, LARGE_BUF_SIZE,
           "{firstStraightDistance : %f, secondStraightDistance : %f, secondホゲータ : %d}",
           firstStraightDistance, secondStraightDistance,
           secondRotationAngle);
  logger.log(buf);
}

void SmartCarryAction::runToLowwerCourse()
{
  char buf[LARGE_BUF_SIZE];

  firstStraightDistance = baseLength / cos(abs(correctedAngle* 2)  * M_PI / 180);
  secondStraightDistance = 750.0 - sqrt(firstStraightDistance*firstStraightDistance - baseLength*baseLength);

  DistanceStraight firstDistanceStraight(firstStraightDistance, firstTargetSpeed);

  firstDistanceStraight.run();
  Sleeping sleeping(200);
  sleeping.run();

  sleeping.run();

  secondRotationAngle = int((90 - abs(correctedAngle*2))*secondRotationBias);
  PwmRotation pwmRotation(secondRotationAngle, 65, isClockwise);
  pwmRotation.run();

  DistanceStraight secondDistanceStraight(secondStraightDistance, secondTargetSpeed);
  secondDistanceStraight.run();

  snprintf(buf, LARGE_BUF_SIZE,
           "{runToLowerCourse : firstStraightDistance : %f, secondStraightDistance : %f, secondホゲータ : %d}",
           firstStraightDistance, secondStraightDistance, secondRotationAngle);
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
           "{firstTargetSpeed : %f, secondTargetSpeed : %f, pwmForRotation : %d}",
           firstTargetSpeed, secondTargetSpeed, pwmForRotation);
  logger.log(buf);
}