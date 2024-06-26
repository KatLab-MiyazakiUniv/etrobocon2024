/**
 * @file ColorJudge.h
 * @brief 色識別クラス
 * @author keiya121 YKhm20020
 */

#ifndef COLOR_JUDGE_H
#define COLOR_JUDGE_H

#include <string.h>
#include <algorithm>
#include "Measurer.h"

enum class COLOR : int {
  NONE = 0,
  BLACK = 1,
  WHITE = 2,
  BLUE = 3,
  GREEN = 4,
  YELLOW = 5,
  RED = 6,
};

struct Hsv {
  int hue;         // 色相(0-360)
  int saturation;  // 彩度(0-100)
  int value;       // 明度(0-255)
};

class ColorJudge {
 public:
  ColorJudge() = delete;  // 明示的にインスタンス化を禁止

  /**
   * 与えられたRGB値から、何色かを返す
   * @param rgb RGB値
   * @return 色
   */
  static COLOR getColor(rgb_raw_t const& rgb);

  /**
   * @brief 文字列を列挙型COLORに変換する
   * @param str 文字列の色
   * @return 色
   */
  static COLOR stringToColor(const char* str);

  /**
   * @brief 列挙型COLORを文字列に変換する
   * @param color 色
   * @return 文字列の色
   */
  static const char* colorToString(COLOR color);

 private:
  static constexpr int SATURATION_BORDER = 27;    // 無彩色かどうかの彩度の境界
  static constexpr int BLACK_LIMIT_BORDER = 10;   // 黒の明度の境界
  static constexpr int WHITE_LIMIT_BORDER = 250;  // 白の明度の境界
  static constexpr int BLACK_BORDER = 110;        // 無彩色の黒の明度の境界
  static constexpr int RED_BORDER = 25;           // 赤の色相の境界
  static constexpr int YELLOW_BORDER = 50;        // 黄の色相の境界
  static constexpr int GREEN_BORDER = 170;        // 緑の色相の境界
  static constexpr int BLUE_BORDER = 300;         // 青の色相の境界
  static constexpr rgb_raw_t MAX_RGB = { 244, 245, 252 };  // コースが白の時（最大）のRGB値
  static constexpr rgb_raw_t MIN_RGB = { 9, 10, 10 };  // コースが黒の時（最小）のRGB値

  /**
   * RGB値をHSV値に変換する
   * @param rgb RGB値
   * @return hsv HSV値
   */
  static Hsv convertRgbToHsv(rgb_raw_t const& rgb);
};

#endif
