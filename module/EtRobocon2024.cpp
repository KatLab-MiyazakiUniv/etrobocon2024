/**
 * @file   EtRobocon2024.cpp
 * @brief  全体を制御するクラス
 * @author Negihara
 */

#include "EtRobocon2024.h"
// ev3api.hをインクルードしているものは.cppに書く
#include "ev3api.h"
#include "ColorSensor.h"
#include "SonarSensor.h"
#include "Measurer.h"
// #include "Motor.h"
// #include "Clock.h"

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

  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  Measurer measurer;

  rgb_raw_t actualColor = measurer.getRawColor();
  snprintf(buf, BUF_SIZE, "%s", actualColor);

  int actualBright = measurer.getBrightness();
  snprintf(buf, BUF_SIZE, "%s", actualBright);

  int actualLeftCount = measurer.getLeftCount();
  snprintf(buf, BUF_SIZE, "%s", actualLeftCount);

  int actualRightCount = measurer.getRightCount();
  snprintf(buf, BUF_SIZE, "%s", actualRightCount);

  int actualMotorCount = measurer.getArmMotorCount();
  snprintf(buf, BUF_SIZE, "%s", actualMotorCount);

  bool actualLeftButton = measurer.getLeftButton();
  snprintf(buf, BUF_SIZE, "%s", actualLeftButton);

  bool actualRightButton = measurer.getRightButton();
  snprintf(buf, BUF_SIZE, "%s", actualRightButton);

  bool actualEnterButton = measurer.getEnterButton();
  snprintf(buf, BUF_SIZE, "%s", actualEnterButton);

  int actualForwardDistance = measurer.getForwardDistance();
  snprintf(buf, BUF_SIZE, "%s", actualForwardDistance);

  int actualVoltage = measurer.getVoltage();
  snprintf(buf, BUF_SIZE, "%s", actualVoltage);

  

  // bool isLeftCourse = false;
  // bool isLeftEdge = false;

  //   // 強制終了(CTRL+C)のシグナルを登録する
  //   signal(SIGINT, sigint);

  //   // キャリブレーションする

  //   // 合図を送るまで待機する

  //   // スタートのメッセージログを出す
  //   const char* course = isLeftCourse ? "Left" : "Right";
  //   snprintf(buf, BUF_SIZE, "\nRun on the %s Course\n", course);
}

// void EtRobocon2024::sigint(int _)
// {
//   _exit(0);  // システムコールで強制終了
// }
