/**
 * @file ControllerTest.cpp
 * @brief Controllerクラスをテストする
 * @author takahashitom CHIHAYATAKU
 */

#include "ev3api.h"
#include "Controller.h"
#include "Measurer.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {
  Measurer measurer;
  Controller controller;

  // 右車輪のモータにPWM値をセットできるかのテスト
  TEST(ControllerTest, setRightMotorPwm)
  {
    const int pwm = 50;
    int initCount = measurer.getRightCount();
    controller.setRightMotorPwm(pwm);
    int currentCount = measurer.getRightCount();
    EXPECT_LT(initCount, currentCount);
    controller.resetRightMotorPwm();
  }

  // 右車輪のモータにマイナスのPWM値をセットできるかどうかのテスト
  TEST(ControllerTest, setRightMotorMinusPwm)
  {
    const int pwm = -50;
    int initCount = measurer.getRightCount();
    controller.setRightMotorPwm(pwm);
    int currentCount = measurer.getRightCount();
    EXPECT_GT(initCount, currentCount);
    controller.resetRightMotorPwm();
  }

  // 左車輪のモータにPWM値をセットできるかのテスト
  TEST(ControllerTest, setLeftMotorPwm)
  {
    const int pwm = 50;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_LT(initCount, currentCount);
    controller.resetLeftMotorPwm();
  }

  // 左車輪のモータにマイナスのPWM値をセットできるかどうかのテスト
  TEST(ControllerTest, setLeftMotorMinusPwm)
  {
    const int pwm = -50;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_GT(initCount, currentCount);
    controller.resetLeftMotorPwm();
  }

  // モータに設定するPWM値の制限が行われているか確認するテスト
  TEST(ControllerTest, setLeftMotorPwmMin)
  {
    const int pwm = -150;
    controller.setLeftMotorPwm(Controller::MOTOR_PWM_MIN);
    int minCount = measurer.getLeftCount();
    controller.resetLeftMotorPwm();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_EQ(minCount, currentCount);
    controller.resetLeftMotorPwm();
  }

  // stopMotor()を呼び出せるか確認するテスト
  TEST(ControllerTest, stopMotor)
  {
    controller.stopMotor();
    SUCCEED();
  }

  // アームモータにPWM値を設定できるかどうか確認するテスト
  TEST(ControllerTest, setArmMotorPwm)
  {
    const int pwm = 50;
    int initCount = measurer.getArmMotorCount();
    controller.setArmMotorPwm(pwm);
    int currentCount = measurer.getArmMotorCount();
    EXPECT_LT(initCount, currentCount);
    controller.resetArmMotorPwm();
  }

  // stopArmMotor()を呼び出せるか確認するテスト
  TEST(ControllerTest, stopArmMotor)
  {
    controller.stopArmMotor();
    SUCCEED();
  }

  // 右タイヤのPWMを取得できるかのテスト
  TEST(ControllerTest, getRightPwm)
  {
    double expected = 0;
    double actual = controller.getRightPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    int pwm = 80;
    controller.setRightMotorPwm(pwm);
    expected = 80;
    actual = controller.getRightPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
  }
  // 左タイヤのPWMを取得できるかのテスト
  TEST(ControllerTest, getLeftPwm)
  {
    double expected = 0;
    double actual = controller.getLeftPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    int pwm = 80;
    controller.setLeftMotorPwm(pwm);
    expected = 80;
    actual = controller.getLeftPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
  }
}  // namespace etrobocon2024_test