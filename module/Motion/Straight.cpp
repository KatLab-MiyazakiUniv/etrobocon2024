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
  if(!isMetPreCondition()) {
    return;
  }
  // 呼び出し時の走行距離
  initialRightDistance = Mileage::calculateWheelMileage(measurer.getRightCount());
  initialLeftDistance = Mileage::calculateWheelMileage(measurer.getLeftCount());

  // SpeedCalculatorのオブジェクトを生成
  SpeedCalculator speedCalculator(targetSpeed);
  Controller controller;  // Controllerクラスのオブジェクトを生成

  // 継続条件を満たしている間繰り返す
  while(isMetContinuationCondition()) {
    // PWM値を計算
    double currentLeftPwm = speedCalculator.calculateLeftMotorPwmFromTargetSpeed();
    double currentRightPwm = speedCalculator.calculateRightMotorPwmFromTargetSpeed();

    // モータにPWM値をセット
    controller.setLeftMotorPwm(currentLeftPwm);
    controller.setRightMotorPwm(currentRightPwm);

    // 10ミリ秒待機
    timer.sleep(10);
  }
  // モータの停止
  controller.stopWheelsMotor();
}

bool Straight::isMetPreCondition()
{
  // デフォルトの実装
  // \"target\"の部分を子クラスにて変更する
  // 目標速度値が0の場合は終了する
  if(targetSpeed == 0) {
    logger.logWarning("The speed value passed to \"target\" Straight is 0");
    return false;
  }
  // \"target\"に応じたエラー処理も子クラスにて記述する

  return true;
}

void Straight::logRunning()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域

  // \"targetValue\"部分を子クラスにて変更する
  snprintf(buf, SMALL_BUF_SIZE, "Run \"targetValue\"Straight (\"targetValue\": , targetSpeed: %f)",
           targetSpeed);
  logger.log(buf);
}