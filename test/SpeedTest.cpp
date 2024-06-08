/**
 * @file SpeedTest.cpp
 * @brief Speedクラスをテストする
 * @author CHIHAYATAKU
 */

#include "Speed.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {

  TEST(SpeedTest, calculateLeftPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(300.0);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(SpeedTest, calculateRightPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-250.7);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(SpeedTest, calculateRightPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(0.0);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(SpeedTest, calculateRightPwmFromTargetSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(300.0);
    double actualPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(SpeedTest, calculateLeftPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-250.7);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(SpeedTest, calculateLeftPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(0.0);
    double actualPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(SpeedTest, calculatePwmFromMinusLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(300.0, -300.0);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_LT(0, actualRightPwm);
    EXPECT_GT(0, actualLeftPwm);
  }

  TEST(SpeedTest, calculatePwmFromMinusRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-250.7, 250.7);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(SpeedTest, calculatePwmFromZeroRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(0.0, 250.7);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_EQ(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(SpeedTest, calculatePwmFromZeroLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-300.0, 0.0);
    double actualRightPwm = speedCalc.calculateRightPwmFromTargetSpeed();
    double actualLeftPwm = speedCalc.calculateLeftPwmFromTargetSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_EQ(0, actualLeftPwm);
  }
}  // namespace etrobocon2024_test