/**
 * @file PwmForSpeedTest.cpp
 * @brief PwmForSpeedクラスをテストする
 * @author CHIHAYATAKU
 */

#include "PwmForSpeed.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {

  TEST(PwmForSpeedTest, calcRightPwmFromSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(300.0);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcRightPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-250.7);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcRightPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(0.0);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcLeftPwmFromSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(300.0);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcLeftPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-250.7);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcLeftPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(0.0);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromMinusLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(300.0, -300.0);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_LT(0, actualRightPwm);
    EXPECT_GT(0, actualLeftPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromMinusRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-250.7, 250.7);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromZeroRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(0.0, 250.7);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_EQ(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromZeroLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-300.0, 0.0);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_EQ(0, actualLeftPwm);
  }
}  // namespace etrobocon2024_test