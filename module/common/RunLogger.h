/**
 * @file RunLogger.h
 * @brief 走行中の各種値可視化のためのcsvファイル作成に関するクラス
 * @author bizyutyu keiya121
 */
#ifndef RUNLOGGER_HPP
#define RUNLOGGER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class RunLogger {
 public:
  /**
   * コンストラクタ
   */
  RunLogger();

  /**
   * @brief 各種値を追加する
   * @param Brightness
   * @param Brightness
   * @param Brightness
   * @param Brightness
   */
  void addToLogs(int _Brightness, int _RightPwm, int _LeftPwm, int _r, int _g, int _b);

  /**
   * @brief 記録した走行ログをファイル出力する
   */
  void outputToFile();

  /**
   * @brief 記録した走行ログを初期化する
   */
  void initRunLogs();

  /**
   * @brief 走行ログcsvファイルのファイル名を保持する文字列
   */
  static char csvFileName[64];

 private:
  static char RunLogs[65536];  // 走行ログを保持する文字列
};

#endif
