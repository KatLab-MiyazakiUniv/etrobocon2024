/**
 * @file RecoveringTest.cpp
 * @brief Recoveringクラスのテスト
 * @author CHIHAYATAKU
 */

#include "Recovering.h"
#include "Logger.h"
#include "Measurer.h"
#include "Controller.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2024_test {

  // 左コースで指定動作を行う際，run()が意図した通りに動作し，エラーメッセージが標準出力に表示されないことをチェックするテスト
  TEST(RecoveringTest, runRecoveringLeft)
  {
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    Recovering recovering(isLeftCourse, isLeftEdge, targetBrightness);
    recovering.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
    // WarningやErrorが出ていた場合にoutputを出力する
    if(!actual) {
      EXPECT_EQ(output, "");
    }
  }

  // 右コースで指定動作を行う際，run()が意図した通りに動作し，エラーメッセージが標準出力に表示されないことをチェックするテスト
  TEST(RecoveringTest, runRecoveringRight)
  {
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    Recovering recovering(isLeftCourse, isLeftEdge, targetBrightness);
    recovering.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
    // WarningやErrorが出ていた場合にoutputを出力する
    if(!actual) {
      EXPECT_EQ(output, "");
    }
  }

  // 左コースでコマンドを読み取って，指定動作を行う場合のテスト
  TEST(RecoveringTest, runRecoveringLeftCommand)
  {
    Measurer measurer;
    Controller controller;
    controller.resetWheelsMotorPwm();
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    Recovering recovering(isLeftCourse, isLeftEdge, targetBrightness);
    double expected = 0.0;
    srand(9037);  // 3回連続して緑を取得する乱数シード
    recovering.run();
    // 復帰動作後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);
    printf("%f\n", actual);

    EXPECT_NE(expected, actual);  // 初期値と異なる
  }

  // 右コースでコマンドを読み取って，指定動作を行う場合のテスト
  TEST(RecoveringTest, runRecoveringRightCommand)
  {
    Measurer measurer;
    Controller controller;
    controller.resetWheelsMotorPwm();
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    Recovering recovering(isLeftCourse, isLeftEdge, targetBrightness);
    double expected = 0.0;
    srand(9037);  // 3回連続して緑を取得する乱数シード
    recovering.run();
    // 復帰動作後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);
    printf("%f\n", actual);

    EXPECT_NE(expected, actual);  // 初期値と異なる
  }

  // 左コースで緑を指定回数連続で取得できないときのテスト（連続取得回数を100回（多ければ可能）にして以下のテストを実行すると，無限ループになることが確認できる．）
  // TEST(RecoveringTest, runRecoveringInfinite)
  // {
  //   Measurer measurer;
  //   Controller controller;
  //   controller.resetWheelsMotorPwm();
  //   bool isLeftCourse = false;
  //   bool isLeftEdge = isLeftCourse;
  //   int targetBrightness = 45;

  //   Recovering recovering(isLeftCourse, isLeftEdge, targetBrightness);
  //   double expected = 0.0;
  //   srand(0);  // 3回連続して緑を取得する乱数シード
  //   recovering.run();
  //   // 復帰動作後の走行距離
  //   int rightCount = measurer.getRightCount();
  //   int leftCount = measurer.getLeftCount();
  //   double actual = Mileage::calculateMileage(rightCount, leftCount);
  //   printf("%f\n", actual);

  //   EXPECT_NE(expected, actual);  // 初期値と異なる
  // }

}  // namespace etrobocon2024_test
