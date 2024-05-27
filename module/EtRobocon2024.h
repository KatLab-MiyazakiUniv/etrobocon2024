/**
 * @file   EtRobocon2024.h
 * @brief  全体を制御するクラス
 * @author Negihara
 */

#ifndef ETROBOCON2024_H
#define ETROBOCON2024_H

// ev3api.hを読み込むヘッダは.cppに記述する
#include <signal.h>
#include <unistd.h>

class EtRobocon2024 {
 public:
  static void start();

 private:
  /**
   * @brief ログファイルを生成して終了するシグナルハンドラ
   * @param _ キャッチしたシグナルの値がセットされる(ここでは使用しない)
   */
  static void sigint(int _);
};

#endif
