/**
 * @file   AreaACameraAction.h
 * @brief  配置エリアAにおけるミニフィグ撮影動作
 * @author takahashitom
 */

#ifndef AREAACAMERAACTION_H
#define AREAACAMERAACTION_H

#include "SystemInfo.h"
#include "CompositeMotion.h"
#include "PwmRotation.h"
#include "DistanceStraight.h"
#include "CameraAction.h"
#include "Sleeping.h"

class AreaACameraAction : public CompositeMotion {
 public:
  /**
   * コンストラクタ
   * @param _position 撮影位置（0~3）
   * @param _isClockwise フロントカメラをミニフィグに向けるための回頭方向　true:時計回り,
   * false:反時計回り
   * @param _preTargetAngle フロントカメラをミニフィグに向けるための回頭角度
   * @param _postTargetAngle 黒線復帰のための回頭角度
   * @param _rotationPwm 回頭時のPWM
   * @param _targetDistance 前進、後退の距離
   * @param _speed 前進、後退の速度
   */
  AreaACameraAction(int _position, bool _isClockwise, int _preTargetAngle, int _postTargetAngle,
                    int _rotationPwm, double _targetDistance, double _speed);

  /**
   * @brief 撮影動作を行う
   */
  void run() override;

  /**
   * @brief 撮影動作を行う際の事前条件判定をする
   */
  bool isMetPreCondition();

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  int flag;  // 撮影を行うかどうかを確認するフラグ
  CameraAction::Subject subject
      = CameraAction::Subject::FIGURE;  // 配置エリアAではミニフィグの撮影を行う
  bool isClockwise;     // リアカメラをミニフィグに向けるための回頭方向
  int preTargetAngle;   // フロントカメラをミニフィグに向けるための回頭角度
  int postTargetAngle;  // 黒線復帰のための目標角度
  int rotationPwm;      // 回頭PWM
  double targetDistance;  // 撮影前後の前進・後退のための目標距離
  double targetSpeed;     // 撮影前後の前進・後退のための目標速度
  const char* ETROBO_PATH = "./etrobocon2024/";
};
#endif