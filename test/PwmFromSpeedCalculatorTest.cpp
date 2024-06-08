/**
 * @file PwmFromSpeedCalculatorTest.cpp
 * @brief SpeedCalculatorクラスをテストする
 * @author CHIHAYATAKU
 */

#include "PwmFromSpeedCalculator.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {

  TEST(PwmFromSpeedCalculatorTest, calculateLeftPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(300.0);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculateRightPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(-250.7);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculateRightPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(0.0);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculateRightPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(300.0);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculateLeftPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(-250.7);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculateLeftPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(0.0);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculatePwmFromMinusLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(300.0, -300.0);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_LT(0, actualRightPwm);
    EXPECT_GT(0, actualLeftPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculatePwmFromMinusRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(-250.7, 250.7);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculatePwmFromZeroRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(0.0, 250.7);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_EQ(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(PwmFromSpeedCalculatorTest, calculatePwmFromZeroLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmFromSpeedCalculator speedCalc(-300.0, 0.0);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_EQ(0, actualLeftPwm);
  }
}  // namespace etrobocon2024_test