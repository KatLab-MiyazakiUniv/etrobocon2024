/**
 * @file SpeedCalculatorTest.cpp
 * @brief SpeedCalculatorクラスをテストする
 * @author CHIHAYATAKU
 */

#include "SpeedCalculator.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {

  TEST(SpeedCalculatorTest, calculateLeftPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(300.0);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateRightPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-250.7);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateRightPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(0.0);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateRightPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(300.0);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateLeftPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-250.7);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculateLeftPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(0.0);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromMinusLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(300.0, -300.0);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_LT(0, actualRightPwm);
    EXPECT_GT(0, actualLeftPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromMinusRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-250.7, 250.7);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromZeroRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(0.0, 250.7);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_EQ(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(SpeedCalculatorTest, calculatePwmFromZeroLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    SpeedCalculator speedCalc(-300.0, 0.0);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_EQ(0, actualLeftPwm);
  }
}  // namespace etrobocon2024_test