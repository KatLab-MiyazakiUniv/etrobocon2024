/**
 * @file PwmForSpeedTest.cpp
 * @brief PwmForSpeedクラスをテストする
 * @author CHIHAYATAKU
 */

#include "PwmForSpeed.h"
#include <gtest/gtest.h>

namespace etrobocon2023_test {
  TEST(PwmForSpeedTest, calcRightPwmFromSpeed)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(300.0);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcRightPwmFromMinusSpeed)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-250.7);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcRightPwmFromZeroSpeed)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(0.0);
    double actualPwm = speedCalc.calcRightPwmFromSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcLeftPwmFromSpeed)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(300.0);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_LT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcLeftPwmFromMinusSpeed)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-250.7);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcLeftPwmFromZeroSpeed)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(0.0);
    double actualPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_EQ(0, actualPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromMinusLeftSpeedWithTwoArguments)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(300.0, -300.0);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_LT(0, actualRightPwm);
    EXPECT_GT(0, actualLeftPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromMinusRightSpeedWithTwoArguments)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-250.7, 250.7);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromZeroRightSpeedWithTwoArguments)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(0.0, 250.7);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_EQ(0, actualRightPwm);
    EXPECT_LT(0, actualLeftPwm);
  }

  TEST(PwmForSpeedTest, calcPwmFromZeroLeftSpeedWithTwoArguments)
  {
    // PWMの初期化
    Controller::setRightMotorPwm(0.0);
    Controller::setLeftMotorPwm(0.0);
    PwmForSpeed speedCalc(-300.0, 0.0);
    double actualRightPwm = speedCalc.calcRightPwmFromSpeed();
    double actualLeftPwm = speedCalc.calcLeftPwmFromSpeed();
    EXPECT_GT(0, actualRightPwm);
    EXPECT_EQ(0, actualLeftPwm);
  }
}  // namespace etrobocon2023_test