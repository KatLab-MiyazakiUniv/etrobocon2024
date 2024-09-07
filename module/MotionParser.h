/**
 * @file   MotionParser.h
 * @brief  動作コマンドファイルを解析するクラス
 * @author keiya121 bizyutyu
 */

#ifndef MOTION_PARSER_H
#define MOTION_PARSER_H

#include <vector>
#include <stdio.h>
#include <string.h>
#include "Logger.h"
#include "Motion.h"
#include "PwmRotation.h"
#include "StringOperator.h"
#include "ColorStraight.h"
#include "ColorLineTracing.h"
#include "DistanceLineTracing.h"
#include "ColorDistanceLineTracing.h"
#include "DistanceStraight.h"
#include "EdgeChanging.h"
#include "Sleeping.h"
#include "StopWheelsMotor.h"
#include "ResetWheelsMotorPwm.h"
#include "CameraAction.h"
#include "AreaACameraAction.h"
#include "CorrectingRotation.h"

#define READ_BUF_SIZE 256  // コマンドのパラメータ読み込み用の領域

enum class COMMAND {
  DL,  // 指定距離ライントレース
  CL,  // 指定色ライントレース
  CD,  // 色距離指定ライントレース
  DS,  // 指定距離直進
  CS,  // 指定色直進
  PR,  // PWM指定回頭
  DT,  // 旋回
  EC,  // エッジ切り替え
  SL,  // 自タスクスリープ
  AU,  // アームを上げる
  AD,  // アームを下げる
  XR,  // 角度補正回頭
  RM,  // 両輪モーターリセット&停止
  SM,  // 両輪モーター停止
  CA,  // カメラ撮影動作
  AC,  // 配置エリアAでのミニフィグ撮影動作
  NONE
};

class MotionParser {
 public:
  /**
   * @brief ファイルを解析して動作インスタンスのリストを生成する
   * @param filePath ファイルパス
   * @param targetBrightness 目標輝度
   * @param isLeftEdge エッジのLR判定(true:Lコース, false:Rコース)
   * @return 動作インスタンスリスト
   */
  static std::vector<Motion*> createMotions(const char* filePath, int targetBrightness,
                                            bool& isLeftEdge);

 private:
  MotionParser();  // インスタンス化を禁止する

  /**
   * @brief 文字列を列挙型COMMANDに変換する
   * @param str 文字列のコマンド
   * @return コマンド
   */
  static COMMAND convertCommand(char* str);

  /**
   * @brief 文字列をbool型に変換する
   * @param command 文字列のコマンド
   * @param stringParameter 文字列のパラメータ
   * @return bool値
   */
  static bool convertBool(char* command, char* stringParameter);

  /**
   * @brief 文字列をSubject型に変換する
   * @param stringParameter 文字列のパラメータ
   * @return Subject値
   */
  static CameraAction::Subject convertSubject(char* stringParameter);
};

#endif
