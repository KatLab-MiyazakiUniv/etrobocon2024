/**
 * @file   PwmRotation.cpp
 * @brief  Pwm指定回頭動作
 * @author takahashitom
 */

#include "PwmRotation.h"

using namespace std;

PwmRotation::PwmRotation(int _targetAngle, int _pwm, bool _isClockwise)
  : Rotation(_pwm, _isClockwise), targetAngle(_targetAngle)
{
}

bool PwmRotation::isMetPrecondition()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  // pwm値が0以下の場合はwarningを出して終了する
  if(pwm <= 0) {
    snprintf(buf, BUF_SIZE, "The pwm value passed to PwmRotation is %d", pwm);
    // logger.logWarning(buf);
    return false;
  }

  // targetAngleが0以下の場合はwarningを出して終了する
  if(targetAngle <= 0 || targetAngle >= 360) {
    snprintf(buf, BUF_SIZE, "The targetAngle value passed to PwmRotation is %d", targetAngle);
    // logger.logWarning(buf);
    return false;
  }

  return true;
}

bool PwmRotation::isMetPostcondition(double initLeftMileage, double initRightMileage, int leftSign,
                                     int rightSign)
{
  // 指定した角度に対する目標の走行距離(弧の長さ)
  double targetDistance = M_PI * TREAD * targetAngle / 360;

  // 目標距離（呼び出し時の走行距離 ± 指定された回転量に必要な距離）
  double targetLeftDistance = initLeftMileage + targetDistance * leftSign;
  double targetRightDistance = initRightMileage + targetDistance * rightSign;

  // 残りの移動距離を算出
  double diffLeftDistance
      = (targetLeftDistance - Mileage::calculateWheelMileage(measurer.getLeftCount())) * leftSign;
  double diffRightDistance
      = (targetRightDistance - Mileage::calculateWheelMileage(measurer.getRightCount()))
        * rightSign;

  // 目標距離に到達した場合
  if(diffLeftDistance <= 0 && diffRightDistance <= 0) {
    return false;
  }
  return true;
}

void PwmRotation::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* str = isClockwise ? "true" : "false";

  snprintf(buf, BUF_SIZE, "Run PwmRotation (angle: %d, pwm: %d, isClockwise: %s)", targetAngle, pwm,
           str);
  //   logger.log(buf);
}