/**
 * @file RunLogger.cpp
 * @brief 走行中の各種値可視化のためのcsvファイル作成に関するクラス
 * @author bizyutyu keiya121
 */
#include "RunLogger.h"

RunLogger::RunLogger() {}

void RunLogger::addToLogs(int _Brightness, int _RightPwm, int _LeftPwm, int _r, int _g, int _b)
{
  // 新しい配列を追加
  sprintf(RunLogs, "%s%d,%d,%d,%d,%d,%d\n", RunLogs, _Brightness, _RightPwm, _LeftPwm, _r, _g, _b);
}

void RunLogger::outputToFile()
{
  FILE* outputFile;
  outputFile = fopen(RunLogger::csvFileName, "w");  // 走行時刻に応じたファイル名のcsvを作成
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

char RunLogger::RunLogs[65536] = "";   // logsを初期化
char RunLogger::csvFileName[64] = "";  // csvファイル名を初期化
