/**
 * @file   Rotation.h
 * @brief  回頭動作の中間クラス
 * @author takahashitom
 */

#ifndef ROTATION_H
#define ROTATION_H

#include "Motion.h"
#include "Mileage.h"
#include "Timer.h"
#include "SystemInfo.h"

class Rotation : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetAngle 目標回転角度(deg) 0~360
   * @param _pwm 指定するPWM値 0~100
   * @param _isClockwise 回頭方向 true:時計回り, false:反時計回り
   */
  Rotation(int _targetAngle, int _pwm, bool _isClockwise);

  /**
   * @brief 回頭する
   */
  void run();

  /**
   * @brief 回頭する際の事前条件判定をする
   * @note オーバーライド必須
   */
  virtual bool isMetPreCondition() = 0;

  /**
   * @brief 回頭する際の継続条件判定をする　返り値がfalseでモーターが止まる
   * @param targetLeftDistance 左車輪の目標距離
   * @param targetRightDistance 右車輪の目標距離
   * @param leftSign 左車輪の回転方向
   * @param rightSign 右車輪の回転方向
   * @note オーバーライド必須
   */
  virtual bool isMetContCondition(double targetLeftDistance, double targetRightDistance,
                                  int leftSign, int rightSign)
      = 0;

  /**
   * @brief 実行のログを取る
   * @note オーバーライド必須
   */
  virtual void logRunning() = 0;

 protected:
  int targetAngle;   // 目標回転角度(deg) 0~360
  int pwm;           // PWM値
  bool isClockwise;  // 回頭方向 true:時計回り, false:反時計回り
  Timer timer;
  // Controller controller;
  // Measurer measurer;
};
#endif