/**
 * @file Pid.cpp
 * @brief PIDを計算するクラス
 * @author CHIHAYATAKU
 */

#include "Pid.h"

PidGain::PidGain(double _kp, double _ki, double _kd) : kp(_kp), ki(_ki), kd(_kd) {}

Pid::Pid(double _kp, double _ki, double _kd, double _targetValue)
  : pidGain(_kp, _ki, _kd), prevDeviation(0.0), integral(0.0), targetValue(_targetValue)
{
}

void Pid::setPidGain(double _kp, double _ki, double _kd)
{
  pidGain.kp = _kp;
  pidGain.ki = _ki;
  pidGain.kd = _kd;
}

double Pid::calculatePid(double currentValue, double delta)
{
  // 0除算を避けるために0の場合はデフォルト周期0.01とする
  if(delta == 0) delta = 0.01;

  // 現在の目標値との偏差を求める
  double currentDeviation = targetValue - currentValue;
  // 積分の処理を行う
  integral += currentDeviation * delta;
  // 微分の処理を行う
  double derivative = (currentDeviation - prevDeviation) / delta;
  // 前回の偏差を更新する
  prevDeviation = currentDeviation;

  // P制御の計算を行う
  double p = pidGain.kp * currentDeviation;
  // I制御の計算を行う
  double i = pidGain.ki * integral;
  // D制御の計算を行う
  double d = pidGain.kd * derivative;

  // 操作量 = P制御 + I制御 + D制御
  return (p + i + d);
}