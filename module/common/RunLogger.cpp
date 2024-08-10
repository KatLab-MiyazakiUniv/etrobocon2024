/**
 * @file RunLogger.cpp
 * @brief 走行中の各種値可視化のためのcsvファイル作成に関するクラス
 * @author bizyutyu
 */
#include "RunLogger.h"

RunLogger::RunLogger() {}

void RunLogger::addTolog(int _Brightness, int _RightPwm, int _leftPwm, int _r, int _g, int _b)
{
  // 新しい配列を追加
  sprintf(RunLogs, "%s%d,%d,%d,%d,%d,%d\n", RunLogs, _Brightness, _RightPwm, _leftPwm, _r, _g, _b);
}

// void RunLogger::addBrightnessTolog(int _RightPwm, int _leftPwm)
// {
//   if(RunLogs.empty()) {
//     // RunLogsが空の場合、新しい配列を追加
//     RunLogs.push_back({_Brightness, 0, 0, 0, 0, 0});
//   } else {
//     // RunLogsが空でない場合、最初の配列の最初の要素を更新
//     RunLogs[0][0] = _Brightness;
//   }
// }

// void RunLogger::addPwmTolog(rgb_raw_t _Rgb)
// {
//   if(RunLogs.empty()) {
//     // RunLogsが空の場合、新しい配列を追加
//     RunLogs.push_back({_Brightness, 0, 0, 0, 0, 0});
//   } else {
//     // RunLogsが空でない場合、最初の配列の最初の要素を更新
//     RunLogs[0][0] = _Brightness;
//   }
// }

// void RunLogger::addRgbTolog(int _Brightness)
// {
//   if(RunLogs.empty()) {
//     // RunLogsが空の場合、新しい配列を追加
//     RunLogs.push_back({_Brightness, 0, 0, 0, 0, 0});
//   } else {
//     // RunLogsが空でない場合、最初の配列の最初の要素を更新
//     RunLogs[0][0] = _Brightness;
//   }
// }

// void RunLogger::convertToCsv()
// {
//   if(RunLogs.empty()) {
//     // RunLogsが空の場合、新しい配列を追加
//     RunLogs.push_back({_Brightness, 0, 0, 0, 0, 0});
//   } else {
//     // RunLogsが空でない場合、最初の配列の最初の要素を更新
//     RunLogs[0][0] = _Brightness;
//   }
// }

void RunLogger::outputToFile()
{
  FILE* outputFile;
  outputFile = fopen("etrobocon2024/logfiles/Runlogfile.csv", "w");  // Runlogfile.csvを作成
  if(outputFile == NULL) {
    printf("cannot open file\n");
    return;
  } else {
    printf("can open file!!!\n");
  }
  // RunLogsの各要素をCSV形式で書き込む
  fprintf(outputFile, "%s\n", RunLogs);
  fclose(outputFile);

  /*
  NOTE: ロボコン環境だと，時刻を取得するtime.hのtime()や，
  ディレクトリを生成するためのヘッダdirect.hを使用できないため（多分），
  bashでRunlogfile.csvの名前をログ生成時刻に変更し，logfiles/に移動する
  */
  // system("bash ./etrobocon2024/scripts/organize_logfile.sh");
}

void RunLogger::initRunLogs()
{
  RunLogs[0] = '\0';  // 配列を初期化
}

char RunLogger::RunLogs[65536] = "";  // logsを初期化
