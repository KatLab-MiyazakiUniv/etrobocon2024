/**
 * @file   ColorLineTracingTest.cpp
 * @brief  ColorLineTracingクラスのテスト
 * @author CHIHAYATAKU
 */

#include "ColorLineTracing.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2024_test {
  // 最初3回の色取得で連続して指定色を取得するテストケース
  TEST(ColorLineTracingTest, runToGetFirst)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::GREEN;
    double targetSpeed = 50000.0;
    double targetBrightness = 50.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;
    srand(9037);  // 3回連続して緑を取得する乱数シード
    cl.run();     // 緑までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);  // 初期値より少しでも進んでいる
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(ColorLineTracingTest, runLeftEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::BLUE;
    double targetSpeed = 100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(0);  // 最初に識別する色が青ではない乱数シード
    cl.run();  // 青までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);  // 実行後に少しでも進んでいる
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(ColorLineTracingTest, runRightEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetSpeed = 100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(0);  // 最初に識別する色が赤ではない乱数シード
    cl.run();  // 赤までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);  // 実行後に少しでも進んでいる
  }

  // 少し走ってから指定色を取得するテストケース（バック）
  TEST(ColorLineTracingTest, runBackLeftEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::YELLOW;
    double targetSpeed = -100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(0);  // 最初に識別する色が黄ではない乱数シード
    cl.run();  // 黄までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GT(expected, actual);  // 実行後に少しでも進んでいる
  }

  // 少し走ってから指定色を取得するテストケース（バック）
  TEST(ColorLineTracingTest, runBackRightEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::GREEN;
    double targetSpeed = -100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(0);  // 最初に識別する色が緑ではない乱数シード
    cl.run();  // 緑までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GT(expected, actual);  // 実行後に少しでも進んでいる
  }

  // targetSpeed値が0の時にwarning文を出力するテストケース
  TEST(ColorLineTracingTest, runZeroSpeed)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::BLUE;
    double targetSpeed = 0.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetSpeed value passed to ColorLineTracing is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    srand(0);  // 最初に識別する色が青ではない乱数シード
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cl.run();                            // 青までライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  // 目標の色がNONEの時にwarning文を出力するテストケース
  TEST(ColorLineTracingTest, runNoneColor)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::NONE;
    double targetSpeed = 100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetColor passed to ColorLineTracing is NONE";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cl.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  // 目標の色がNoneかつtargetSpeed値が0のときwarning文を出力するテストケース
  TEST(ColorLineTracingTest, runNoneColorAndZeroSpeed)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::NONE;
    double targetSpeed = 0.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorLineTracing cl(targetColor, targetSpeed, targetBrightness, gain, isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetColor passed to ColorLineTracing is NONE, and the "
                      "targetSpeed value passed "
                      "to ColorLineTracing is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cl.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }
}  // namespace etrobocon2024_test