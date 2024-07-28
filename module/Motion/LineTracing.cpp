/**
 * @file   LineTracing.cpp
 * @brief  ライントレース動作の中間クラス
 * @author CHIHAYATAKU
 */

#include "LineTracing.h"
using namespace std;

LineTracing::LineTracing(double _targetSpeed, int _targetBrightness, const PidGain& _pidGain,
                         bool& _isLeftEdge)
  : targetSpeed(_targetSpeed),
    targetBrightness(_targetBrightness),
    pidGain(_pidGain),
    isLeftEdge(_isLeftEdge)
{
}

void LineTracing::run()
{
  Pid pid(pidGain.kp, pidGain.ki, pidGain.kd, targetBrightness);

  // 初期値を代入
  initDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());

  // 事前条件を判定する
  if(!isMetPreCondition(targetSpeed)) {
    return;
  }

  // 左右で符号を変える
  int edgeSign = isLeftEdge ? -1 : 1;

  // 呼び出し時の走行距離
  initLeftMileage = Mileage::calculateWheelMileage(measurer.getLeftCount());
  initRightMileage = Mileage::calculateWheelMileage(measurer.getRightCount());

  SpeedCalculator speedCalculator(targetSpeed);

  // 継続条件を満たしている間ループ
  while(isMetContinuationCondition()) {
    // 初期pwm値を計算
    double baseRightPwm = speedCalculator.calculateRightMotorPwmFromTargetSpeed();
    double baseLeftPwm = speedCalculator.calculateLeftMotorPwmFromTargetSpeed();

    // PIDで旋回値を計算
    double turningPwm = pid.calculatePid(measurer.getBrightness()) * edgeSign;

    // モータのPWM値をセット（前進の時0を下回らないように，後進の時0を上回らないようにセット）
    double rightPwm = baseRightPwm > 0.0 ? max(baseRightPwm - turningPwm, 0.0)
                                         : min(baseRightPwm + turningPwm, 0.0);
    double leftPwm = baseLeftPwm > 0.0 ? max(baseLeftPwm + turningPwm, 0.0)
                                       : min(baseLeftPwm - turningPwm, 0.0);
    controller.setRightMotorPwm(rightPwm);
    controller.setLeftMotorPwm(leftPwm);

    // 10ミリ秒待機
    timer.sleep(10);
  }
}

void LineTracing::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* strWhetherIsLeftEdge = isLeftEdge ? "true" : "false";

  // targetValueと%~のオーバーライド必須
  snprintf(buf, LARGE_BUF_SIZE,
           "Run \"targetValue\" LineTracing (\"targetValue\": , targetSpeed: %.2f, "
           "targetBrightness: %d, Gain: (%.2f,%.2f,%.2f), isLeftEdge: %s)",
           targetSpeed, targetBrightness, pidGain.kp, pidGain.ki, pidGain.kd, strWhetherIsLeftEdge);
  logger.log(buf);
}