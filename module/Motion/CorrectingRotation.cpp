/**
 * @file   CorrectingRotation.cpp
 * @brief  プラレール・背景撮影のための角度補正回頭動作
 * @author bizyutyu
 */

#include "CorrectingRotation.h"
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

CorrectingRotation::CorrectingRotation(int _pwm) : pwm(_pwm){};

void CorrectingRotation::run()
{
  // 補正角度算出を行う
  // Pytnon側で算出に必要な画像取得から補正角度算出までを行う
  char cmd[512];
  snprintf(cmd, 512,
           "cd etrobocon2024/front_camera && make correction-angle > correction_angle.txt && sudo "
           "chmod 644 correction_angle.txt && cd ../..");


  // コマンドを実行
  int result = system(cmd);
  if(result != 0) {
    throw std::runtime_error("コマンドの実行に失敗しました");
  }

  // 一時ファイルから出力を読み取る
  ifstream file("etrobocon2024/front_camera/correction_angle.txt");
  string output;
  getline(file, output);
  file.close();

  // 改行文字を削除
  if(!output.empty() && output[output.length() - 1] == '\n') {
    output.erase(output.length() - 1);
  }

  // 一時ファイルを削除
  remove("etrobocon2024/front_camera/correction_angle.txt");

  // 出力を整数に変換
  int calculationAngle = 0;
  if(!output.empty()) {
    std::istringstream iss(output);
    if(!(iss >> calculationAngle)) {
      throw std::runtime_error("角度の変換に失敗しました: " + output);
    }
  } else {
    throw std::runtime_error("角度の出力が空です");
  }

  printf("補正角度: %d\n", calculationAngle);

  // calculationAngleの符号に基づいてisClockwiseを設定し、calculationAngleを正の値にする
  bool isClockwise = (calculationAngle >= 0);
  correctionAngle = abs(calculationAngle * 0.5) <= 10 ? 0 : abs(calculationAngle * 0.5);

  printf("ホゲータ回頭: %d\n", correctionAngle);
  PwmRotation pr(correctionAngle, pwm, isClockwise);
  Sleeping sl(500);

  // 補正のための回頭をする
  pr.run();
  sl.run();
}

void CorrectingRotation::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, LARGE_BUF_SIZE, "Run CorrectingRotation (correctionAngle: %d, pwm: %d)",
           correctionAngle, pwm);
  logger.log(buf);
}
