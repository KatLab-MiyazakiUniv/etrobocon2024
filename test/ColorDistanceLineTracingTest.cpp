/**
 * @file   ColorDistanceLineTracingTest.cpp
 * @brief  ColorDistanceLineTracingクラスのテスト
 * @author Negimarge
 */

#include "ColorDistanceLineTracing.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2024_test {
  // 最初3回の色取得で連続して指定色を取得するテストケース
  TEST(ColorDistanceLineTracingTest, runToGetFirst)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::GREEN;
    double targetDistance = 10000;
    double targetSpeed = 50000.0;
    double targetBrightness = 50.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;
    srand(9037);  // 3回連続して緑を取得する乱数シード
    cd.run();     // 緑までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);  // 初期値より少しでも進んでいる
    EXPECT_LT(actual, targetDistance);
  }

  // 少し走ってから指定色を取得するテストケース（左エッジ走行）
  TEST(ColorDistanceLineTracingTest, colorRunLeftEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::BLUE;
    double targetDistance = 10000;
    double targetSpeed = 100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(0);  // 最初に識別する色が青ではない乱数シード
    cd.run();  // 青までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);        // 実行後に少しでも進んでいる
    EXPECT_LT(actual, targetDistance);  // 目標距離よりも進んでいない
  }

  // 少し走ってから指定色を取得するテストケース（右エッジ走行）
  TEST(ColorDistanceLineTracingTest, colorRunRightEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetDistance = 10000;
    double targetSpeed = 100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(0);  // 最初に識別する色が赤ではない乱数シード
    cd.run();  // 赤までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);        // 実行後に少しでも進んでいる
    EXPECT_LT(actual, targetDistance);  // 目標距離よりも進んでいない
  }

  // 少し走ってから指定色を取得するテストケース（バック，左エッジ走行）
  TEST(ColorDistanceLineTracingTest, colorRunBackLeftEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::YELLOW;
    double targetDistance = 1000;
    double targetSpeed = -100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(0);  // 最初に識別する色が黄ではない乱数シード
    cd.run();  // 黄までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GT(expected, actual);         // 実行後に少しでも進んでいる
    EXPECT_GT(actual, -targetDistance);  // 目標距離よりも進んでいない
  }

  // 少し走ってから指定色を取得するテストケース（バック，右エッジ走行）
  TEST(ColorDistanceLineTracingTest, colorRunBackRightEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::GREEN;
    double targetDistance = 1000;
    double targetSpeed = -100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    srand(5);  // 最初に識別する色が緑ではない乱数シード
    cd.run();  // 緑までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GT(expected, actual);         // 実行後に少しでも進んでいる
    EXPECT_GT(actual, -targetDistance);  // 目標距離よりも進んでいない
  }

  // targetSpeed値が0の時にwarning文を出力するテストケース
  TEST(ColorDistanceLineTracingTest, runZeroSpeed)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::BLUE;
    double targetDistance = 10000;
    double targetSpeed = 0.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetSpeed value passed to ColorDistanceLineTracing is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    srand(0);  // 最初に識別する色が青ではない乱数シード
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cd.run();                            // 青までライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  // 目標の色がNONEの時にwarning文を出力するテストケース
  TEST(ColorDistanceLineTracingTest, runNoneColorDistance)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::NONE;
    double targetDistance = 10000;
    double targetSpeed = 100.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetColor passed to ColorDistanceLineTracing is NONE";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cd.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  // 目標の色がNoneかつtargetSpeed値が0のときwarning文を出力するテストケース
  TEST(ColorDistanceLineTracingTest, runNoneColorDistanceAndZeroSpeed)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::NONE;
    double targetDistance = 0.0;
    double targetSpeed = 0.0;
    double targetBrightness = 45.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput
        += "Warning: The targetColor passed to ColorDistanceLineTracing is NONE, and the "
           "targetSpeed value passed "
           "to ColorDistanceLineTracing is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cd.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  // 目標距離までライントレースを行うテストケース（左エッジ走行）
  TEST(ColorDistanceLineTracingTest, DistanceRunLeftEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetSpeed = 100.0;
    double targetDistance = 100.0;
    double targetBrightness = 45.0;
    double basePwm = 100.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected
    //     = Mileage::calculateMileage(initialRightCount, initialLeftCount) + targetDistance;
    double expected = targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = Mileage::calculateMileage(basePwm * 0.05, basePwm * 0.05);  // 許容誤差

    cd.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以上である
    EXPECT_GT(expected + error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  // 目標距離までライントレースを行うテストケース（右エッジ走行）
  TEST(ColorDistanceLineTracingTest, distanceRunRightEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetSpeed = 100.0;
    double targetDistance = 1000.0;
    double targetBrightness = 45.0;
    double basePwm = 100.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected
    //     = Mileage::calculateMileage(initialRightCount, initialLeftCount) + targetDistance;
    double expected = targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = Mileage::calculateMileage(basePwm * 0.05, basePwm * 0.05);  // 許容誤差

    cd.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以上である
    EXPECT_GT(expected + error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  // 目標距離までライントレースを行うテストケース（バック，左エッジ走行）
  TEST(ColorDistanceLineTracingTest, distanceRunBackLeftEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetSpeed = -100.0;
    double targetDistance = 100.0;
    double targetBrightness = 45.0;
    double basePwm = -100.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected
    //     = Mileage::calculateMileage(initialRightCount, initialLeftCount) - targetDistance;
    double expected = -targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = Mileage::calculateMileage(std::abs(basePwm * 0.05),
                                             std::abs(basePwm * 0.05));  // 許容誤差

    cd.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以下である
    EXPECT_LT(expected - error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  // 目標距離までライントレースを行うテストケース（バック，右エッジ走行）
  TEST(ColorDistanceLineTracingTest, distanceRunBackRightEdge)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetSpeed = -100.0;
    double targetDistance = 100.0;
    double targetBrightness = 45.0;
    double basePwm = -100.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected
    //     = Mileage::calculateMileage(initialRightCount, initialLeftCount) - targetDistance;
    double expected = -targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = Mileage::calculateMileage(std::abs(basePwm * 0.05),
                                             std::abs(basePwm * 0.05));  // 許容誤差

    cd.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以下である
    EXPECT_LT(expected - error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  // targetDistance値が0以下の時にwarning文を出力するテストケース
  TEST(ColorDistanceLineTracingTest, runMinusDistance)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetSpeed = 100.0;
    double targetDistance = -1000.0;
    double targetBrightness = 45.0;
    double basePwm = 100.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput
        += "Warning: The targetDistance value passed to ColorDistanceLineTracing is -1000.00";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cd.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  // targetDistance値が0以下かつtargetSpeed値が0のときwarning文を出力するテストケース
  TEST(ColorDistanceLineTracingTest, runMinusDistanceAndZeroSpeed)
  {
    Controller controller;
    Measurer measurer;
    // PWMの初期化
    controller.resetWheelsMotorPwm();
    COLOR targetColor = COLOR::RED;
    double targetSpeed = 0.0;
    double targetDistance = -50.0;
    double targetBrightness = 45.0;
    double basePwm = 100.0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    ColorDistanceLineTracing cd(targetColor, targetDistance, targetSpeed, targetBrightness, gain,
                                isLeftEdge);

    // 初期値から期待する走行距離を求める
    // int initialRightCount = measurer.getRightCount();
    // int initialLeftCount = measurer.getLeftCount();
    // double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);
    double expected = 0.0;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetDistance value to ColorDistanceLineTracing is "
                      "-50.00, and the targetSpeed "
                      "value "
                      "to ColorDistanceLineTracing is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    cd.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }
}  // namespace etrobocon2024_test