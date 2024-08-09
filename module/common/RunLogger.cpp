/**
 * @file RunLogger.cpp
 * @brief 走行中の各種値可視化のためのcsvファイル作成に関するクラス
 * @author bizyutyu
 */
#include "RunLogger.h"

RunLogger::RunLogger() {}

void RunLogger::addTolog(int _Brightness, int _RightPwm, int _leftPwm, rgb_raw_t _Rgb)
{
    // 新しい配列を追加
    RunLogs.push_back({_Brightness, _RightPwm, _leftPwm, _Rgb.r, _Rgb.g, _Rgb.b});
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
  const char* fileName = "logfiles/Runlogfile.csv";  // 暫定のファイル名
  outputFile = fopen(fileName, "w");     // Runlogfile.csvを作成
  if(outputFile == NULL) {
    printf("cannot open file");
    return;
  }
  // RunLogsの各要素をCSV形式で書き込む
  for(const auto& log : RunLogs) {
    fprintf(outputFile, "%d,%.2f,%.2f,%d,%d,%d\n", 
            log[0], log[1], log[2], log[3], log[4], log[5]);
  }
  fclose(outputFile);

  /*
  NOTE: ロボコン環境だと，時刻を取得するtime.hのtime()や，
  ディレクトリを生成するためのヘッダdirect.hを使用できないため（多分），
  bashでRunlogfile.csvの名前をログ生成時刻に変更し，logfiles/に移動する
  */
  system("bash ./etrobocon2024/scripts/organize_logfile.sh");
}

void RunLogger::initRunLogs()
{
  RunLogs.clear(); // 配列を初期化
}

std::vector<std::array<int, 6>> RunLogger::RunLogs;
// char RunLogger::logs[65536] = "";  // logsを初期化
