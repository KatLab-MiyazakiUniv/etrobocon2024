/**
 * @file   Rotation.cpp
 * @brief  回頭動作の中間クラス
 * @author takahashitom
 */

#include "Rotation.h"

using namespace std;

Rotation::Rotation(int _pwm, bool _isClockwise) : pwm(_pwm), isClockwise(_isClockwise) {}

void Rotation::run()
{
  // 事前条件を判定する
  if(!isMetPrecondition()) {
    return;
  }

  // isClockwiseがtrueなら時計回り，falseなら反時計回り
  // isClockwiseは回転方向の係数
  int leftSign = isClockwise ? 1 : -1;
  int rightSign = isClockwise ? -1 : 1;

  // 呼び出し時の走行距離
  double initLeftMileage = Mileage::calculateWheelMileage(measurer.getLeftCount());
  double initRightMileage = Mileage::calculateWheelMileage(measurer.getRightCount());

  // 継続条件を満たしている間ループ
  while(isMetPostcondition(initLeftMileage, initLeftMileage, leftSign, rightSign)) {
    // モータにPWM値をセット
    controller.setLeftMotorPwm(pwm * leftSign);
    controller.setRightMotorPwm(pwm * rightSign);

    // 10ミリ秒待機
    timer.sleep();
  }

  // モータの停止
  controller.stopMotor();
}