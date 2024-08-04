/**
 * @file   Recovering.cpp
 * @brief  コース復帰動作をするクラス
 * @author CHIHAYATAKU
 */

#include "Recovering.h"

using namespace std;
Recovering::Recovering(bool _isLeftCourse, const bool& _isLeftEdge, int _targetBrightness)
  : isLeftCourse(_isLeftCourse), isLeftEdge(_isLeftEdge), targetBrightness(_targetBrightness)
{
}

void Recovering::run()
{
  while(1) {
    if(isErrorState()) {
      char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域
      Logger logger;

      // ファイルから受け取る動作リスト
      vector<Motion*> motionList;

      // コマンドファイルパスを作成する
      char commandFilePath[SMALL_BUF_SIZE];
      snprintf(commandFilePath, SMALL_BUF_SIZE, "%s%s%s.csv", basePath, commandFileName,
               (isLeftCourse ? "Left" : "Right"));

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
      break;  // 2024.08.05 並列処理実装まで，一回の復帰動作でループを抜けるようにする
    }
  }
}

bool Recovering::isErrorState()
{
  if(ColorJudge::getColor(measurer.getRawColor()) == targetColor) {
    colorCount++;
  } else {
    colorCount = 0;
  }
  if(colorCount < JUDGE_COUNT) return false;
  // 指定された色をJUDGE_COUNT回連続で取得したときモータが止まる
  colorCount = 0;
  return true;
}

void Recovering::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, LARGE_BUF_SIZE, "Run Recovering");
  logger.log(buf);
}