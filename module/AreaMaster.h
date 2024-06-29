/**
 * @file   AreaMaster.h
 * @brief  エリアを攻略するクラス
 * @author keiya121
 */

#ifndef AREA_MASTER_H
#define AREA_MASTER_H

#include <vector>
#include <stdio.h>
#include <string.h>
#include "MotionParser.h"
#include "Logger.h"

// エリア名を持つ列挙型変数（LineTrace = 0, DoubleLoop = 1, DebrisRemoval = 2, SmartCarry = 3）
enum Area { LineTrace, DoubleLoop, DebrisRemoval, SmartCarry };

class AreaMaster {
 public:
  /**
   * コンストラクタ
   * @param area エリアの指定(Enum型のArea)
   * @param isLeftCourse コースのLR判定(true:Lコース, false:Rコース)
   * @param isLeftEdge エッジのLR判定(true:左エッジ, false:右エッジ)
   * @param targetBrightness 目標輝度
   */
  AreaMaster(Area area, bool isLeftCourse, bool& isLeftEdge, int targetBrightness);

  /**
   * @brief エリアを走行する
   */
  void run();

 private:
  enum Area area;
  bool isLeftCourse;
  bool isLeftEdge;
  int targetBrightness;

  // 各エリアのコマンドファイルベースパス
  const char* basePath = "etrobocon2024/datafiles/";

  // コマンドファイル名（各エリア名）
  const char* commandFileNames[4] = { "LineTrace", "DoubleLoop", "DebrisRemoval", "SmartCarry" };
};

#endif
