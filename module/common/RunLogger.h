/**
 * @file RunLogger.h
 * @brief 走行中の各種値可視化のためのcsvファイル作成に関するクラス
 * @author bizyutyu
 */
#ifndef RUNLOGGER_H
#define RUNLOGGER_H

#include <ColorSensor.h>
#include <vector>
#include <array>

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
  void addTolog(int _Brightness, int _RightPwm, int _leftPwm, rgb_raw_t _Rgb);

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
  static std::vector<std::array<int, 6>> RunLogs;  // 走行ログを保持する配列
};

#endif
