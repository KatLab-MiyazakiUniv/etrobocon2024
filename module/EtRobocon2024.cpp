/**
 * @file   EtRobocon2024.cpp
 * @brief  全体を制御するクラス
 * @author Negihara
 */

#include "EtRobocon2024.h"
// ev3api.hをインクルードしているものは.cppに書く
#include "AreaMaster.h"
#include "Measurer.h"
#include "Controller.h"
#include "Calibrator.h"
#include "SystemInfo.h"
#include "ev3api.h"
#include "ColorSensor.h"
#include "SonarSensor.h"
#include "Motor.h"
#include "Clock.h"
#include "Timer.h"

void EtRobocon2024::start()
{
  // const ePortS colorSensorPort = PORT_2;
  // const ePortS sonarSensorPort = PORT_3;
  // const ePortM armMotorPort = PORT_A;
  // const ePortM rightMotorPort = PORT_B;
  // const ePortM leftMotorPort = PORT_C;

  // ev3api::ColorSensor* _colorSensorPtr = new ev3api::ColorSensor(colorSensorPort);
  // ev3api::SonarSensor* _sonarSensorPtr = new ev3api::SonarSensor(sonarSensorPort);
  // ev3api::Motor* _rightMotorPtr = new ev3api::Motor(rightMotorPort);
  // ev3api::Motor* _leftMotorPtr = new ev3api::Motor(leftMotorPort);
  // ev3api::Motor* _armMotorPtr = new ev3api::Motor(armMotorPort);
  // ev3api::Clock* _clockPtr = new ev3api::Clock();

  // const int BUF_SIZE = 128;
  // char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  // bool isLeftCourse = false;
  // bool isLeftEdge = false;

  //   // 強制終了(CTRL+C)のシグナルを登録する
  //   signal(SIGINT, sigint);

  //   // キャリブレーションする

  //   // 合図を送るまで待機する

  //   // スタートのメッセージログを出す
  //   const char* course = isLeftCourse ? "Left" : "Right";
  //   snprintf(buf, BUF_SIZE, "\nRun on the %s Course\n", course);
  bool isLeftCourse = true;
  bool isLeftEdge = true;
  Calibrator calibrator;

  // 　　　走行ログファイルを取得する場合
  if(shouldGetRunLogs) {
    // 現在の日付と時刻を取得
    time_t now = time(nullptr);
    tm* tm_now = localtime(&now);

    // UTCからJSTに変換
    tm_now->tm_hour += 8;
    if(tm_now->tm_hour >= 24) {
      tm_now->tm_hour -= 24;
      tm_now->tm_mday += 1;
    }

    // 走行ログを記録するcsvファイル名を作成
    strftime(RunLogger::csvFileName, sizeof(RunLogger::csvFileName),
             "etrobocon2024/logfiles/%Y-%m-%d-%H-%M.csv", tm_now);
  }

  // キャリブレーションする
  calibrator.run();
  isLeftCourse = calibrator.getIsLeftCourse();
  // isLeftCourse = true;
  isLeftEdge = isLeftCourse;
  int targetBrightness = calibrator.getTargetBrightness();

  // int targetBrightness = 50;
  // 各エリアを走行する
  // 走行状態をwait(開始合図待ち)に変更
  // setstate("wait");
  // 合図を送るまで待機する
  calibrator.waitForStart();

  AreaMaster LineTraceAreaMaster(Area::LineTrace, isLeftCourse, isLeftEdge, targetBrightness);
  AreaMaster DoubleLoopAreaMaster(Area::DoubleLoop, isLeftCourse, isLeftEdge, targetBrightness);
  AreaMaster DebrisRemovalAreaMaster(Area::DebrisRemoval, isLeftCourse, isLeftEdge,
                                     targetBrightness);
  AreaMaster SmartCarryAreaMaster(Area::SmartCarry, isLeftCourse, isLeftEdge, targetBrightness);

  // LAPゲートを通過する
  LineTraceAreaMaster.run();
  DoubleLoopAreaMaster.run();
  DebrisRemovalAreaMaster.run();
  SmartCarryAreaMaster.run();
}

// void EtRobocon2024::sigint(int _)
// {
//   _exit(0);  // システムコールで強制終了
// }