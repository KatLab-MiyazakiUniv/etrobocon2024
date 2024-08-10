/**
 * @file RunLogger.h
 * @brief 走行中の各種値可視化のためのcsvファイル作成に関するクラス
 * @author bizyutyu
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
   */
  void addTolog(int _Brightness, int _RightPwm, int _leftPwm, int _r, int _g, int _b);

  // /**
  //  * @brief 輝度を追加する
  //  * @param Brightness
  //  */
  // void addBrightnessTolog(int _Brightness);

  // /**
  //  * @brief PWMを追加する
  //  * @param Pwm
  //  */
  // void addPwmTolog(int _RightPwm, int _leftPwm);

  // /**
  //  * @brief RGBを追加する
  //  * @param Rgb
  //  */
  // void addRgbTolog(rgb_raw_t _Rgb);

  // /**
  //  * @brief 記録した走行ログを配列からcsv形式に変換
  //  */
  // void convertToCsv();

  /**
   * @brief 記録した走行ログをファイル出力する
   */
  void outputToFile();

  /**
   * @brief 記録した走行ログを初期化する
   */
  void initRunLogs();

 private:
  static char RunLogs[65536];  // 走行ログを保持する文字列
};

#endif
