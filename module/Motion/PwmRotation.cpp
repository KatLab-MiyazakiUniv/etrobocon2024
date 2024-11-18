/**
 * @file   PwmRotation.cpp
 * @brief  Pwm指定回頭動作
 * @author takahashitom
 */

#include "PwmRotation.h"

using namespace std;

PwmRotation::PwmRotation(int _targetAngle, int _pwm, bool _isClockwise)
  : Rotation(_targetAngle, _pwm, _isClockwise)
{
}

bool PwmRotation::isMetPreCondition()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域

  // pwm値が0以下の場合はwarningを出して終了する
  if(pwm <= 0) {
    snprintf(buf, SMALL_BUF_SIZE, "The pwm value passed to PwmRotation is %d", pwm);
    logger.logWarning(buf);
    return false;
  }

  // targetAngleが0以下の場合はwarningを出して終了する
  if(targetAngle <= 0 || targetAngle >= 360) {
    snprintf(buf, SMALL_BUF_SIZE, "The angle value passed to PwmRotation is %d", targetAngle);
    logger.logWarning(buf);
    return false;
  }

  return true;
}

bool PwmRotation::isMetContCondition(double targetLeftDistance, double targetRightDistance,
                                     int leftSign, int rightSign)
{
  // 残りの移動距離を算出
  double diffLeftDistance
      = (targetLeftDistance - Mileage::calculateWheelMileage(measurer->getLeftCount())) * leftSign;
  double diffRightDistance
      = (targetRightDistance - Mileage::calculateWheelMileage(measurer->getRightCount()))
        * rightSign;

  // 目標距離に到達した場合
  if(diffLeftDistance <= 0 && diffRightDistance <= 0) {
    return false;
  }
  return true;
}

void PwmRotation::logRunning()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* str = isClockwise ? "true" : "false";

  snprintf(buf, SMALL_BUF_SIZE, "Run PwmRotation (angle: %d, pwm: %d, isClockwise: %s)",
           targetAngle, pwm, str);
  logger.log(buf);
}