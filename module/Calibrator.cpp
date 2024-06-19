/**
 * @file Calibrator.cpp
 * @brief キャリブレーションからスタートまでを担当するクラス
 * @author takahashitom
 */

#include "Calibrator.h"

Calibrator::Calibrator() : isLeftCourse(true), targetBrightness(50) {}

void Calibrator::run()
{
  //  画像の削除
  char cmd[LARGE_BUF_SIZE];
  snprintf(cmd, LARGE_BUF_SIZE, "cd etrobocon2024/rear_camera_py && make rm-img && cd ../..");
  system(cmd);

  // 左右ボタンでコースのLRを選択する
  selectCourse();

  // 目標輝度を測定する
  measureTargetBrightness();
}

void Calibrator::selectCourse()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;
  bool _isLeftCourse = true;

  logger.log("Select a Course");
  logger.log(">> Set Left Course");
  // 右ボタンが押されたら確定する
  while(!measurer.getRightButton()) {
    if(measurer.getLeftButton() && !_isLeftCourse) {
      // 左ボタンが押されたときRコースがセットされていれば、Lコースをセットする
      _isLeftCourse = true;
      logger.log(">> Set Left Course");
      timer.sleep(500);  // 500ミリ秒スリープ
    } else if(measurer.getLeftButton() && _isLeftCourse) {
      // 左ボタンが押されたときLコースがセットされていれば、Rコースをセットする
      _isLeftCourse = false;
      logger.log(">> Set Right Course");
      timer.sleep(500);  // 500ミリ秒スリープ
    } else {
      timer.sleep();  // 10ミリ秒スリープ
    }
  }

  isLeftCourse = _isLeftCourse;
  const char* course = isLeftCourse ? "Left" : "Right";
  snprintf(buf, SMALL_BUF_SIZE, "\nWill Run on the %s Course\n", course);
  logger.logHighlight(buf);

  timer.sleep(1000);  // 1秒スリープ
}

void Calibrator::measureTargetBrightness()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;
  int whiteBrightness = -1;
  int blackBrightness = -1;
  targetBrightness = -1;

  // 黒線上で左ボタンを押して黒の輝度を取得し、右ボタンで決定する
  logger.log("Press the Left Button on the Black");

  // 黒
  // 左ボタンで輝度を取得し、右ボタンで黒の輝度を決定する
  while(blackBrightness < 0 || !measurer.getRightButton()) {
    // 左ボタンが押されるまで待機
    while(blackBrightness < 0 && !measurer.getLeftButton()) {
      timer.sleep();  // 10ミリ秒スリープ
    }
    // 輝度取得
    blackBrightness = measurer.getBrightness();
    snprintf(buf, SMALL_BUF_SIZE, ">> Black Brightness Value is %d", blackBrightness);
    logger.log(buf);
    timer.sleep();  // 10ミリ秒スリープ
  }

  // 白線上で左ボタンを押して白の輝度を取得し、右ボタンで決定する
  logger.log("Press the Left Button on the White");

  // 白
  // 左ボタンで輝度を取得し、右ボタンで白の輝度を決定する
  while(whiteBrightness < 0 || !measurer.getRightButton()) {
    // 左ボタンが押されるまで待機
    while(whiteBrightness < 0 && !measurer.getLeftButton()) {
      timer.sleep();  // 10ミリ秒スリープ
    }
    // 輝度取得
    whiteBrightness = measurer.getBrightness();
    snprintf(buf, SMALL_BUF_SIZE, ">> White Brightness Value is %d", whiteBrightness);
    logger.log(buf);
    timer.sleep();  // 10ミリ秒スリープ
  }

  targetBrightness = (whiteBrightness + blackBrightness) / 2;
  snprintf(buf, SMALL_BUF_SIZE, ">> Target Brightness Value is %d", targetBrightness);
  logger.log(buf);
}

void Calibrator::waitForStart()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;
  constexpr int startDistance = 5;  // 手などでスタート合図を出す距離[cm]

  logger.log("On standby.\n");
  snprintf(buf, SMALL_BUF_SIZE, "On standby.\n\nSignal within %dcm from Sonar Sensor.",
           startDistance);
  logger.log(buf);

  // startDistance以内の距離に物体がない間待機する
  while(measurer.getForwardDistance() > startDistance) {
    timer.sleep();  // 10ミリ秒スリープ
  }
}

bool Calibrator::getIsLeftCourse()
{
  return isLeftCourse;
}

int Calibrator::getTargetBrightness()
{
  return targetBrightness;
}