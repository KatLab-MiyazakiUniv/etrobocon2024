/**
 *  @file SpeedCalculator.cpp
 *  @brief 目標速度に対応するPWM値を算出するクラス
 *  @author CHIHAYATAKU
 */
#include "SpeedCalculator.h"

SpeedCalculator::SpeedCalculator(double _targetSpeed)
  : rightTargetSpeed(_targetSpeed),
    leftTargetSpeed(_targetSpeed),
    rightPid(K_P, K_I, K_D, _targetSpeed),
    leftPid(K_P, K_I, K_D, _targetSpeed)
{
  rightMotorPwm = Controller::getRightMotorPwm();
  leftMotorPwm = Controller::getLeftMotorPwm();
  int rightAngle = measurer.getRightCount();
  int leftAngle = measurer.getLeftCount();
  prevRightMileage = Mileage::calculateWheelMileage(rightAngle);
  prevLeftMileage = Mileage::calculateWheelMileage(leftAngle);
  int currentTime = timer.now();
  prevRightTime = currentTime;
  prevLeftTime = currentTime;
}

// 回頭用（2024版では使わないかもしれないが一応残しておく）
SpeedCalculator::SpeedCalculator(double _rightTargetSpeed, double _leftTargetSpeed)
  : rightTargetSpeed(_rightTargetSpeed),
    leftTargetSpeed(_leftTargetSpeed),
    rightPid(R_K_P, R_K_I, R_K_D, _rightTargetSpeed),
    leftPid(R_K_P, R_K_I, R_K_D, _leftTargetSpeed)
{
  rightMotorPwm = Controller::getRightMotorPwm();
  leftMotorPwm = Controller::getLeftMotorPwm();
  int rightAngle = measurer.getRightCount();
  int leftAngle = measurer.getLeftCount();
  prevRightMileage = Mileage::calculateWheelMileage(rightAngle);
  prevLeftMileage = Mileage::calculateWheelMileage(leftAngle);
  int currentTime = timer.now();
  prevRightTime = currentTime;
  prevLeftTime = currentTime;
}

double SpeedCalculator::calculateRightMotorPwmFromTargetSpeed()
{
  // 右タイヤの回転角度を取得
  int rightAngle = measurer.getRightCount();
  // 右タイヤの走行距離を算出
  double currentRightMileage = Mileage::calculateWheelMileage(rightAngle);
  double diffRightMileage = currentRightMileage - prevRightMileage;
  // 走行時間を算出
  int currentRightTime = timer.now();
  double diffRightTime = (double)(currentRightTime - prevRightTime);
  // 右タイヤの走行速度を算出
  double currentRightSpeed = calculateSpeed(diffRightMileage, diffRightTime);
  // 走行速度に相当する右タイヤのPWM値を算出
  rightMotorPwm += rightPid.calculatePid(currentRightSpeed, diffRightTime);
  // メンバを更新
  prevRightMileage = currentRightMileage;
  prevRightTime = currentRightTime;

  return rightMotorPwm;
}

double SpeedCalculator::calculateLeftMotorPwmFromTargetSpeed()
{
  // 左タイヤの回転角度を取得
  int leftAngle = measurer.getLeftCount();
  // 左タイヤの走行距離を算出
  double currentLeftMileage = Mileage::calculateWheelMileage(leftAngle);
  double diffLeftMileage = currentLeftMileage - prevLeftMileage;
  // 走行時間を算出
  int currentLeftTime = timer.now();
  double diffLeftTime = (double)(currentLeftTime - prevLeftTime);
  // 左タイヤの走行速度を算出
  double currentLeftSpeed = calculateSpeed(diffLeftMileage, diffLeftTime);
  // 走行速度に相当する左タイヤのPWM値を算出
  leftMotorPwm += leftPid.calculatePid(currentLeftSpeed, diffLeftTime);
  // メンバを更新
  prevLeftMileage = currentLeftMileage;
  prevLeftTime = currentLeftTime;

  return leftMotorPwm;
}

double SpeedCalculator::calculateSpeed(double diffMileage, double diffTime)
{
  // 走行時間が0のとき、0を返す
  if(diffTime == 0.0) return 0.0;
  // 走行速度[mm/s]を算出(= 1000 * mm / ms)
  double speed = 1000 * diffMileage / diffTime;
  return speed;
}