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
}

void RunLogger::initRunLogs()
{
  RunLogs[0] = '\0';  // 配列を初期化
}

char RunLogger::RunLogs[65536] = "";  // logsを初期化
