/**
 *  @file   DistanceStraightTest.cpp
 *  @brief  DistanceStraightクラスのテスト
 *  @author bizyutyu
 */

#include "DistanceStraight.h"
#include <gtest/gtest.h>

using namespace std;

namespace etrobocon2023_test {
  TEST(DistanceStraightTest, run)
  {
    // Controllerクラスのオブジェクトを生成
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    double targetDistance = 350;
    double targetSpeed = 50;
    DistanceStraight ds(targetDistance, targetSpeed);

    // 初期値
    Measurer measurer;  // Measurerクラスのオブジェクトを生成
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    double leftInitial = Mileage::calculateWheelMileage(leftCount);
    double rightInitial = Mileage::calculateWheelMileage(rightCount);
    // 期待する走行距離
    double expectedDistance = Mileage::calculateMileage(rightCount, leftCount) + targetDistance;

    /**
     * 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
     * StraightRunnerのPWM値は100まで加速するので，許容誤差のpwmは100で計算する
     */
    double distanceError = Mileage::calculateMileage(100 * 0.05, 100 * 0.05);  // 許容誤差
    double expectedError = 1;  // タイヤの走行距離の誤差の期待値

    ds.run();  // 直進を実行

    // 関数実行後の走行距離
    leftCount = measurer.getLeftCount();
    rightCount = measurer.getRightCount();
    double leftActual = Mileage::calculateWheelMileage(leftCount);
    double rightActual = Mileage::calculateWheelMileage(rightCount);
    double actualDistance = Mileage::calculateMileage(rightCount, leftCount);

    // タイヤごとの走行距離
    double leftDifference = std::abs(leftActual - leftInitial);
    double rightDifference = std::abs(rightActual - rightInitial);
    // タイヤの走行距離の誤差
    double actualError = std::abs(leftDifference - rightDifference);

    // 走行距離のテスト
    EXPECT_LE(expectedDistance, actualDistance);
    EXPECT_GE(expectedDistance + distanceError, actualDistance);

    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(DistanceStraightTest, runFullPwm)
  {
    // Controllerクラスのオブジェクトを生成
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    double targetDistance = 350;
    double targetSpeed = 100;
    DistanceStraight ds(targetDistance, targetSpeed);

    // 初期値
    Measurer measurer;  // Measurerクラスのオブジェクトを生成
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    double leftInitial = Mileage::calculateWheelMileage(leftCount);
    double rightInitial = Mileage::calculateWheelMileage(rightCount);
    // 期待する走行距離
    double expectedDistance = Mileage::calculateMileage(rightCount, leftCount) + targetDistance;

    /**
     * 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
     * StraightRunnerのPWM値は100まで加速するので，許容誤差のpwmは100で計算する
     */
    double distanceError = Mileage::calculateMileage(100 * 0.05, 100 * 0.05);  // 許容誤差
    double expectedError = 1;  // タイヤの走行距離の誤差の期待値

    ds.run();  // 直進を実行

    // 関数実行後の走行距離
    leftCount = measurer.getLeftCount();
    rightCount = measurer.getRightCount();
    double leftActual = Mileage::calculateWheelMileage(leftCount);
    double rightActual = Mileage::calculateWheelMileage(rightCount);
    double actualDistance = Mileage::calculateMileage(rightCount, leftCount);

    // タイヤごとの走行距離
    double leftDifference = std::abs(leftActual - leftInitial);
    double rightDifference = std::abs(rightActual - rightInitial);
    // タイヤの走行距離の誤差
    double actualError = std::abs(leftDifference - rightDifference);

    // 走行距離のテスト
    EXPECT_LE(expectedDistance, actualDistance);
    EXPECT_GE(expectedDistance + distanceError, actualDistance);

    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(DistanceStraightTest, runMinusDistance)
  {
    // Controllerクラスのオブジェクトを生成
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    double targetDistance = -350;
    double targetSpeed = 100;
    DistanceStraight ds(targetDistance, targetSpeed);

    // 初期値
    Measurer measurer;  // Measurerクラスのオブジェクトを生成
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    // 期待する走行距離
    double expectedDistance = Mileage::calculateMileage(rightCount, leftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetDistance value passed to DistanceStraight is -350.00";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    ds.run();                            // 直進を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 関数実行後の走行距離
    leftCount = measurer.getLeftCount();
    rightCount = measurer.getRightCount();
    double actualDistance = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);      // 標準出力でWarningを出している
    EXPECT_EQ(expectedDistance, actualDistance);  // 直進前後で走行距離に変化はない
  }

  TEST(DistanceStraightTest, runBack)
  {
    // Controllerクラスのオブジェクトを生成
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    double targetDistance = 350;
    double targetSpeed = -50;
    DistanceStraight ds(targetDistance, targetSpeed);

    // 初期値
    Measurer measurer;  // Measurerクラスのオブジェクトを生成
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    double leftInitial = Mileage::calculateWheelMileage(leftCount);
    double rightInitial = Mileage::calculateWheelMileage(rightCount);
    // 期待する走行距離
    double expectedDistance = Mileage::calculateMileage(rightCount, leftCount) - targetDistance;

    /**
     * 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
     * StraightRunnerのPWM値は-100まで加速するので，許容誤差のpwmは-100で計算する
     */
    double distanceError = Mileage::calculateMileage(-100 * 0.05, -100 * 0.05);  // 許容誤差
    double expectedError = 1;  // タイヤの走行距離の誤差の期待値

    ds.run();  // 直進を実行

    // 関数実行後の走行距離
    leftCount = measurer.getLeftCount();
    rightCount = measurer.getRightCount();
    double leftActual = Mileage::calculateWheelMileage(leftCount);
    double rightActual = Mileage::calculateWheelMileage(rightCount);
    double actualDistance = Mileage::calculateMileage(rightCount, leftCount);

    // タイヤごとの走行距離
    double leftDifference = std::abs(leftActual - leftInitial);
    double rightDifference = std::abs(rightActual - rightInitial);
    // タイヤの走行距離の誤差
    double actualError = std::abs(leftDifference - rightDifference);

    // 走行距離のテスト
    EXPECT_GE(expectedDistance, actualDistance);
    EXPECT_LE(expectedDistance + distanceError, actualDistance);

    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(DistanceStraightTest, runBackFullPwm)
  {
    // Controllerクラスのオブジェクトを生成
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    double targetDistance = 350;
    double targetSpeed = -100;
    DistanceStraight ds(targetDistance, targetSpeed);

    // 初期値
    Measurer measurer;  // Measurerクラスのオブジェクトを生成
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    double leftInitial = Mileage::calculateWheelMileage(leftCount);
    double rightInitial = Mileage::calculateWheelMileage(rightCount);
    // 期待する走行距離
    double expectedDistance = Mileage::calculateMileage(rightCount, leftCount) - targetDistance;

    /**
     * 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
     * StraightRunnerのPWM値は-100まで加速するので，許容誤差のpwmは-100で計算する
     */
    double distanceError = Mileage::calculateMileage(-100 * 0.05, -100 * 0.05);  // 許容誤差
    double expectedError = 1;  // タイヤの走行距離の誤差の期待値

    ds.run();  // 直進を実行

    // 関数実行後の走行距離
    leftCount = measurer.getLeftCount();
    rightCount = measurer.getRightCount();
    double leftActual = Mileage::calculateWheelMileage(leftCount);
    double rightActual = Mileage::calculateWheelMileage(rightCount);
    double actualDistance = Mileage::calculateMileage(rightCount, leftCount);

    // タイヤごとの走行距離
    double leftDifference = std::abs(leftActual - leftInitial);
    double rightDifference = std::abs(rightActual - rightInitial);
    // タイヤの走行距離の誤差
    double actualError = std::abs(leftDifference - rightDifference);

    // 走行距離のテスト
    EXPECT_GE(expectedDistance, actualDistance);
    EXPECT_LE(expectedDistance + distanceError, actualDistance);

    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(DistanceStraightTest, runZeroPwm)
  {
    // Controllerクラスのオブジェクトを生成
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    double targetDistance = 350;
    double targetSpeed = 0;
    DistanceStraight ds(targetDistance, targetSpeed);

    // 初期値
    Measurer measurer;  // Measurerクラスのオブジェクトを生成
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    // 期待する走行距離
    double expectedDistance = Mileage::calculateMileage(rightCount, leftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetSpeed value passed to DistanceStraight is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    ds.run();                            // 直進を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 関数実行後の走行距離
    leftCount = measurer.getLeftCount();
    rightCount = measurer.getRightCount();
    double actualDistance = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);      // 標準出力でWarningを出している
    EXPECT_EQ(expectedDistance, actualDistance);  // 直進前後で走行距離に変化はない
  }

  TEST(DistanceStraightTest, runMinusDistanceZeroPwm)
  {
    // Controllerクラスのオブジェクトを生成
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    double targetDistance = -350;
    double targetSpeed = 0;
    DistanceStraight ds(targetDistance, targetSpeed);

    // 初期値
    Measurer measurer;  // Measurerクラスのオブジェクトを生成
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    // 期待する走行距離
    double expectedDistance = Mileage::calculateMileage(rightCount, leftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetSpeed value passed to DistanceStraight is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    ds.run();                            // 直進を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 関数実行後の走行距離
    leftCount = measurer.getLeftCount();
    rightCount = measurer.getRightCount();
    double actualDistance = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);      // 標準出力でWarningを出している
    EXPECT_EQ(expectedDistance, actualDistance);  // 直進前後で走行距離に変化はない
  }

}  // namespace etrobocon2023_test
