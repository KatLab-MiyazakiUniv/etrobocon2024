/**
 * @file SpeedCalculatorTest.cpp
 * @brief SpeedCalculatorクラスをテストする
 * @author CHIHAYATAKU
 */

#include "SpeedCalculator.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {

  TEST(SpeedCalculatorTest, calculateLeftMotorPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(300.0);
    double actualPwm = speedCalc.calculateLeftMotorPwmFromTargetSpeed();
    EXPECT_LT(0.0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculaterightMotorPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-250.7);
    double actualPwm = speedCalc.calculateRightMotorPwmFromTargetSpeed();
    EXPECT_GT(0.0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculaterightMotorPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(0.0);
    double expected = 0.0;
    double actualPwm = speedCalc.calculateRightMotorPwmFromTargetSpeed();
    EXPECT_EQ(expected, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateRightMotorPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(300.0);
    double actualPwm = speedCalc.calculateRightMotorPwmFromTargetSpeed();
    EXPECT_LT(0.0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateleftMotorPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-250.7);
    double actualPwm = speedCalc.calculateLeftMotorPwmFromTargetSpeed();
    EXPECT_GT(0.0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateleftMotorPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(0.0);
    double expected = 0.0;
    double actualPwm = speedCalc.calculateLeftMotorPwmFromTargetSpeed();
    EXPECT_EQ(expected, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromMinusLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(300.0, -300.0);
    double actualrightMotorPwm = speedCalc.calculateRightMotorPwmFromTargetSpeed();
    double actualleftMotorPwm = speedCalc.calculateLeftMotorPwmFromTargetSpeed();
    EXPECT_LT(0.0, actualrightMotorPwm);
    EXPECT_GT(0.0, actualleftMotorPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromMinusRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-250.7, 250.7);
    double actualrightMotorPwm = speedCalc.calculateRightMotorPwmFromTargetSpeed();
    double actualleftMotorPwm = speedCalc.calculateLeftMotorPwmFromTargetSpeed();
    EXPECT_GT(0.0, actualrightMotorPwm);
    EXPECT_LT(0.0, actualleftMotorPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromZeroRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(0.0, 250.7);
    double actualrightMotorPwm = speedCalc.calculateRightMotorPwmFromTargetSpeed();
    double actualleftMotorPwm = speedCalc.calculateLeftMotorPwmFromTargetSpeed();
    double expected_right = 0.0;
    EXPECT_EQ(expected_right, actualrightMotorPwm);
    EXPECT_LT(0.0, actualleftMotorPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromZeroLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-300.0, 0.0);
    double actualrightMotorPwm = speedCalc.calculateRightMotorPwmFromTargetSpeed();
    double actualleftMotorPwm = speedCalc.calculateLeftMotorPwmFromTargetSpeed();
    double expected_left = 0.0;
    EXPECT_GT(0.0, actualrightMotorPwm);
    EXPECT_EQ(expected_left, actualleftMotorPwm);
  }
}  // namespace etrobocon2024_test