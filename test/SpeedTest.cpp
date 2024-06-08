/**
 * @file SpeedTest.cpp
 * @brief Speedクラスをテストする
 * @author CHIHAYATAKU
 */

#include "Speed.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {

  TEST(SpeedTest, calcRightPwmFromSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(300.0);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(SpeedTest, calcRightPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-250.7);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(SpeedTest, calcRightPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(0.0);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(SpeedTest, calcLeftPwmFromSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(300.0);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(SpeedTest, calcLeftPwmFromMinusSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-250.7);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(SpeedTest, calcLeftPwmFromZeroSpeed)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(0.0);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(SpeedTest, calcPwmFromMinusLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(300.0, -300.0);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_LT(0, actualRightPwm);
    EXPECT_GT(0, actualLeftPwm);
  }

  TEST(SpeedTest, calcPwmFromMinusRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-250.7, 250.7);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(SpeedTest, calcPwmFromZeroRightSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(0.0, 250.7);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_EQ(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(SpeedTest, calcPwmFromZeroLeftSpeedWithTwoArguments)
  {
    Controller controller;
    // PWMの初期化
    controller.setRightMotorPwm(0.0);
    controller.setLeftMotorPwm(0.0);
    Speed speedCalc(-300.0, 0.0);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_EQ(0, actualLeftPwm);
  }
}  // namespace etrobocon2024_test