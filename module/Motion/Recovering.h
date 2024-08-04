/**
 * @file   Recovering.h
 * @brief  コース復帰動作をするクラス
 * @author CHIHAYATAKU
 */

#ifndef RECOVERING_H
#define RECOVERING_H

#include <vector>
#include <stdio.h>
#include <string.h>
#include "MotionParser.h"
#include "ColorJudge.h"

class Recovering : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _isLeftCourse コースのLR判定(true:Lコース, false:Rコース)
   * @param _isLeftEdge エッジのLR判定(true:左エッジ, false:右エッジ)
   * @param _targetBrightness 目標輝度
   */
  Recovering(bool _isLeftCourse, const bool& _isLeftEdge, int _targetBrightness);

  /**
   * @brief 走行体がコースを外れたときに復帰動作をする
   */
  void run();

 private:
  /**
   * @brief 走行体がコースを脱線しているかを判定をする　返り値がtrueで復帰動作開始
   */
  bool isErrorState();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  bool isLeftCourse;     // コースのLR判定(true:Lコース, false:Rコース)
  bool isLeftEdge;       // エッジのLR判定(true:左エッジ, false:右エッジ)
  int targetBrightness;  // 目標輝度
  static constexpr int JUDGE_COUNT = 3;  // 目標色の連続取得回数の定義
  int colorCount = 0;                // 目標色の連続取得回数を記録するための変数
  COLOR targetColor = COLOR::GREEN;  // コース脱線判定のための目標色

  // コマンドファイルベースパス
  const char* basePath = "etrobocon2024/datafiles/";

  // コマンドファイル名
  const char* commandFileName = "Recovery";
  Measurer measurer;
};

#endif