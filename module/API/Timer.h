/**
 * @file Timer.h
 * @brief 時間測定に用いる関数をまとめたラッパークラス
 * @author takahashitom
 */

#ifndef TIMER_H
#define TIMER_H

#include "ev3api.h"
#include "Clock.h"

class Timer {
 public:
  /**
   * コンストラクタ
   */
  Timer();

  /**
   * @brief 自タスクスリープ（デフォルトは10ミリ秒）
   * @param milliSec スリープ時間(ミリ秒)
   */
  void sleep(int milliSec = 10);

  /**
   * @brief 走行時間を取得
   * @return 走行時間(ミリ秒)
   */
  int now();

 private:
  ev3api::Clock clock;
};

#endif