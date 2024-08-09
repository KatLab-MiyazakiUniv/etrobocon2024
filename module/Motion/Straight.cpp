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
  // 呼び出し時の走行距離を取得する
  double initialRightMotorCount = measurer.getRightCount();
  double initialLeftMotorCount = measurer.getLeftCount();
  initialDistance = Mileage::calculateMileage(initialRightMotorCount, initialLeftMotorCount);

  // SpeedCalculatorのオブジェクトを生成
  SpeedCalculator speedCalculator(targetSpeed);
  Controller controller;  // Controllerクラスのオブジェクトを生成
  RunLogger runLogger;

  // 継続条件を満たしている間繰り返す
  while(isMetContinuationCondition()) {
    // PWM値を計算
    double currentLeftPwm = speedCalculator.calculateLeftMotorPwmFromTargetSpeed();
    double currentRightPwm = speedCalculator.calculateRightMotorPwmFromTargetSpeed();

    // モータにPWM値をセット
    controller.setLeftMotorPwm(currentLeftPwm);
    controller.setRightMotorPwm(currentRightPwm);

    // 現在の輝度値を取得
    int currentBrightness = measurer.getBrightness();

    // 現在のRGB値を取得
    rgb_raw_t currentRgb = measurer.getRawColor();

    // RunLoggerにデータを追加
    runLogger.addTolog(currentBrightness, static_cast<int>(currentRightPwm),
                       static_cast<int>(currentLeftPwm), currentRgb);

    // 10ミリ秒待機
    timer.sleep(10);
  }
  // モータの停止
  // controller.stopWheelsMotor();

  // 走行ログ書き込み
  runLogger.outputToFile();
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
