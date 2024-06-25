/**
 * @file   AreaMaster.cpp
 * @brief  エリアを攻略するクラス
 * @author keiya121
 */

#include "AreaMaster.h"

using namespace std;

AreaMaster::AreaMaster(Area _area, bool _isLeftCourse, bool& _isLeftEdge, int _targetBrightness)
  : area(_area),
    isLeftCourse(_isLeftCourse),
    isLeftEdge(_isLeftEdge),
    targetBrightness(_targetBrightness)
{
}

void AreaMaster::run()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;

  // ファイルから受け取る動作リスト
  vector<Motion*> motionList;

  // コマンドファイルパスを作成する
  char commandFilePath[SMALL_BUF_SIZE];
  snprintf(commandFilePath, SMALL_BUF_SIZE, "%s%s%s.csv", basePath,
           commandFileNames[static_cast<int>(area)], (isLeftCourse ? "Left" : "Right"));

  // 動作インスタンスのリストを生成する
  motionList = MotionParser::createMotions(commandFilePath, targetBrightness, isLeftEdge);

  // 動作実行のメッセージログを出す
  snprintf(buf, SMALL_BUF_SIZE, "\nRun the commands in '%s'\n", commandFilePath);
  logger.logHighlight(buf);

  // 各動作を実行する
  for(auto motion = motionList.begin(); motion != motionList.end();) {
    (*motion)->logRunning();
    (*motion)->run();
    delete *motion;                     // メモリを解放
    motion = motionList.erase(motion);  // リストから削除
  }
}