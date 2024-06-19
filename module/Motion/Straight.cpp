/**
 * @file   Straight.cpp
 * @brief  直進動作の抽象クラス
 * @author bizyutyu
 */

#include "Straight.h"
using namespace std;

Straight::Straight(double _targetSpeed) : targetSpeed(_targetSpeed) {}

void Straight::run()
{
  // 事前条件判定が真でないときは終了する
  if(isRunPreconditionJudgement() == false) {
    return;
  }
  Measurer measurer;
  // 直進前の走行距離
  initialRightMotorCount = measurer.getRightCount();
  initialLeftMotorCount = measurer.getLeftCount();
  initialRightDistance = Mileage::calculateWheelMileage(initialRightMotorCount);
  initialLeftDistance = Mileage::calculateWheelMileage(initialLeftMotorCount);

  // 直進中の走行距離
  currentRightMotorCount = initialRightMotorCount;
  currentLeftMotorCount = initialLeftMotorCount;
  currentRightDistance = initialRightDistance;
  currentLeftDistance = initialLeftDistance;

  // SpeedCalculatorのオブジェクトを生成
  SpeedCalculator speedCalculator(targetSpeed);

  double currentLeftPwm = 0.0;   // 現在の左タイヤpwd値
  double currentRightPwm = 0.0;  // 現在の右タイヤpwd値
  Controller controller; // Controllerクラスのオブジェクトを生成

  // 走行距離が目標値に到達するまで繰り返す
  while(true) {
    // 終了条件が満たされたときループから抜ける オーバーライド必須
    if(isRunPostconditionJudgement() == true) {
      break;
    }

    // PWM値を目標速度値に合わせる
    currentLeftPwm = speedCalculator.calculateLeftMotorPwmFromTargetSpeed();
    currentRightPwm = speedCalculator.calculateRightMotorPwmFromTargetSpeed();
    
    // モータにPWM値をセット
    controller.setLeftMotorPwm(currentLeftPwm);
    controller.setRightMotorPwm(currentRightPwm);

    // 10ミリ秒待機
    timer.sleep(10);
  }
  // モータの停止
  controller.stopWheelsMotor();
}

bool Straight::isRunPreconditionJudgement()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];
  // \"target\"をオーバーライド必須
  // 目標速度値が0の場合は終了する
  if(targetSpeed == 0) {
    logger.logWarning("The speed value passed to \"target\" Straight is 0");
    return false;
  }
  // \"target\"をオーバーライド必須
  // rightPwmとleftPwmの絶対値がMIN_PWMより小さい場合はwarningを出す
  SpeedCalculator speedCalculator(targetSpeed);
  double rightPwm = speedCalculator.calculateRightMotorPwmFromTargetSpeed();
  double leftPwm = speedCalculator.calculateLeftMotorPwmFromTargetSpeed();
  if(abs(rightPwm) < MIN_PWM || abs(leftPwm) < MIN_PWM) {
    snprintf(buf, BUF_SIZE,
             "The pwm value passed to \"target\" Straight is rightPwm = %f and leftPwm = %f",
             rightPwm, leftPwm);
    logger.logWarning(buf);
  }
  // \"target\"に応じたエラー処理が必須
  // オーバーライド必須
  if(false) {
    return false;
  }

  return true;
}

void Straight::logRunning()
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  // targetValueと%~のオーバーライド必須
  snprintf(buf, BUF_SIZE, "Run \"targetValue\"Straight (\"targetValue\": , targetSpeed: %f)",
           targetSpeed);
  logger.log(buf);
}