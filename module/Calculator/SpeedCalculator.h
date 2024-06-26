/**
 * @file SpeedCalculator.h
 *  @brief 目標速度に対応するPWM値を算出するクラス
 *  @author CHIHAYATAKU
 */

#ifndef SpeedCalculator_H
#define SpeedCalculator_H

#include "Measurer.h"
#include "Controller.h"
#include "Mileage.h"
#include "Pid.h"
#include "Timer.h"

class SpeedCalculator {
 public:
  /**
   * @brief 引数１つの場合のコンストラクタ
   * @param _targetSpeed 目標とする走行速度[mm/s]
   */
  SpeedCalculator(double _targetSpeed);

  /**
   * @brief 引数２つの場合のコンストラクタ．（2024版では使わないかもしれないが一応残しておく）
   * @param _rightTargetSpeed 目標とする右タイヤ走行速度[mm/s]
   * @param _leftTargetSpeed 目標とする左タイヤ走行速度[mm/s]
   */
  SpeedCalculator(double _rightTargetSpeed, double _leftTargetSpeed);

  /**
   * @brief 目標とする走行速度に相当する右車輪のPWM値を算出する
   * @return 走行速度に相当する右タイヤのPWM値
   */
  double calculateRightMotorPwmFromTargetSpeed();

  /**
   * @brief 目標とする走行速度に相当する左車輪のPWM値を算出する
   * @return 走行速度に相当する左タイヤのPWM値
   */
  double calculateLeftMotorPwmFromTargetSpeed();

 private:
  const double rightTargetSpeed;
  const double leftTargetSpeed;
  Pid rightPid;
  Pid leftPid;
  Timer timer;
  Measurer measurer;
  double rightMotorPwm;
  double leftMotorPwm;
  double prevRightMileage;
  double prevLeftMileage;
  int prevRightTime;
  int prevLeftTime;
  // 回頭以外のPIDゲイン
  static constexpr double K_P = 0.004;
  static constexpr double K_I = 0.0000005;
  static constexpr double K_D = 0.0007;
  // 回頭用PIDゲイン
  // ToDo：次イテレーションで調整
  static constexpr double R_K_P = 0.004;
  static constexpr double R_K_I = 0.0000005;
  static constexpr double R_K_D = 0.0007;

  /**
   * @brief 走行速度を算出する
   * @param diffMileage 移動距離[mm]
   * @param diffTime 移動時間[ms]
   * @return 走行速度[mm/s]
   */
  double calculateSpeed(double diffMileage, double diffTime);
};
#endif