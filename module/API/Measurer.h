/**
 * @file Measurer.h
 * @brief　計測に用いる関数をまとめたラッパークラス
 * @author keiya121
 */

#ifndef MEASURER_H
#define MEASURER_H

#include <algorithm>
#include "ev3api.h"
#include "ColorSensor.h"
#include "SonarSensor.h"
#include "Motor.h"

class Measurer {
 public:
  /**
   * @brief　コンストラクタ
   */
  Measurer();

  /**
   * @brief　明るさを取得
   * @return 反射光の強さ(0-100)
   */
  int getBrightness();

  /**
   * @brief　RGB値を取得
   * @return RGB値
   */
  rgb_raw_t getRawColor();

  /**
   * @brief　左モータ角位置取得
   * @return 左モータ角位置[deg]
   */
  int getLeftCount();

  /**
   * @brief　右モータ角位置取得
   * @return 右モータ角位置[deg]
   */
  int getRightCount();

  /**
   * @brief　アームモータ角位置取得
   * @return アームモータ角位置[deg]
   */
  int getArmMotorCount();

  /**
   * @brief　正面から見て左ボタンの押下状態を取得
   * @return 左ボタンの押下状態 true:押されてる, false：押されていない
   */
  bool getLeftButton();

  /**
   * @brief　正面から見て右ボタンの押下状態を取得
   * @return 右ボタンの押下状態 true:押されてる, false：押されていない
   */
  bool getRightButton();

  /**
   * @brief　中央ボタンの押下状態を取得
   * @return 中央ボタンの押下状態 true:押されてる, false：押されていない
   */
  bool getEnterButton();

  /**
   * @brief　超音波センサからの距離を取得
   * @return 超音波センサからの距離[cm]
   * @note センサが認識していない時は1000を返す
   */
  int getForwardDistance();

  /**
   * @brief　SPIKEの電圧を取得
   * @return SPIKEの電圧[V]
   */
  double getVoltage();

 private:
  ev3api::ColorSensor colorSensor;
  ev3api::SonarSensor sonarSensor;
  ev3api::Motor leftWheel;
  ev3api::Motor rightWheel;
  ev3api::Motor armMotor;
};

#endif