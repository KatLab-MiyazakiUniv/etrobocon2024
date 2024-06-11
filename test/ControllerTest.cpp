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

  // 右車輪のモータにPWM値をセットできるかのテスト
  TEST(ControllerTest, setRightMotorPwm)
  {
    Measurer measurer;
    Controller controller;
    const double pwm = 50.0;
    int initCount = measurer.getRightCount();
    controller.setRightMotorPwm(pwm);
    int currentCount = measurer.getRightCount();
    EXPECT_LT(initCount, currentCount);
    controller.resetRightMotorPwm();
  }

  // 右車輪のモータにマイナスのPWM値をセットできるかどうかのテスト
  TEST(ControllerTest, setRightMotorMinusPwm)
  {
    Measurer measurer;
    Controller controller;
    const double pwm = -50.0;
    int initCount = measurer.getRightCount();
    controller.setRightMotorPwm(pwm);
    int currentCount = measurer.getRightCount();
    EXPECT_GT(initCount, currentCount);
    controller.resetRightMotorPwm();
  }

  // 左車輪のモータにPWM値をセットできるかのテスト
  TEST(ControllerTest, setLeftMotorPwm)
  {
    Measurer measurer;
    Controller controller;
    const double pwm = 50.0;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_LT(initCount, currentCount);
    controller.resetLeftMotorPwm();
  }

  // 左車輪のモータにマイナスのPWM値をセットできるかどうかのテスト
  TEST(ControllerTest, setLeftMotorMinusPwm)
  {
    Measurer measurer;
    Controller controller;
    const double pwm = -50.0;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_GT(initCount, currentCount);
    controller.resetLeftMotorPwm();
  }

  // モータに設定するPWM値の制限が行われているか確認するテスト
  TEST(ControllerTest, setLeftMotorPwmMin)
  {
    Measurer measurer;
    Controller controller;
    const double pwm = -150.0;
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
    Controller controller;
    controller.stopMotor();
    SUCCEED();
  }

  // アームモータにPWM値を設定できるかどうか確認するテスト
  TEST(ControllerTest, setArmMotorPwm)
  {
    Measurer measurer;
    Controller controller;
    const double pwm = 50.0;
    int initCount = measurer.getArmMotorCount();
    controller.setArmMotorPwm(pwm);
    int currentCount = measurer.getArmMotorCount();
    EXPECT_LT(initCount, currentCount);
    controller.resetArmMotorPwm();
  }

  // stopArmMotor()を呼び出せるか確認するテスト
  TEST(ControllerTest, stopArmMotor)
  {
    Controller controller;
    controller.stopArmMotor();
    SUCCEED();
  }

  // 右タイヤのPWM値を取得できるかのテスト
  TEST(ControllerTest, getRightMotorPwm)
  {
    Controller controller;
    double expected = 0.0;
    double actual = controller.getRightMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    double pwm = 90.2;
    controller.setRightMotorPwm(pwm);
    expected = 90.2;
    actual = controller.getRightMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    pwm = 200.0;
    controller.setRightMotorPwm(pwm);
    expected = 100.0;
    actual = controller.getRightMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    pwm = -200.0;
    controller.setRightMotorPwm(pwm);
    expected = -100.0;
    actual = controller.getRightMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    controller.resetRightMotorPwm();
  }

  // 左タイヤのPWM値を取得できるかのテスト
  TEST(ControllerTest, getleftMotorPwm)
  {
    Controller controller;
    double expected = 0;
    double actual = controller.getLeftMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    double pwm = 80.1;
    controller.setLeftMotorPwm(pwm);
    expected = 80.1;
    actual = controller.getLeftMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    pwm = 200.0;
    controller.setLeftMotorPwm(pwm);
    expected = 100.0;
    actual = controller.getLeftMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    pwm = -200.0;
    controller.setLeftMotorPwm(pwm);
    expected = -100.0;
    actual = controller.getLeftMotorPwm();
    EXPECT_DOUBLE_EQ(expected, actual);
    controller.resetLeftMotorPwm();
  }
}  // namespace etrobocon2024_test