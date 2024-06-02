/**
 * @file ControllerTest.cpp
 * @brief Controllerクラスをテストする
 * @author takahashitom
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
  }

  // 右車輪のモータにマイナスのPWM値をセットできるかどうかのテスト
  TEST(ControllerTest, setRightMotorMinusPwm)
  {
    const int pwm = -50;
    int initCount = measurer.getRightCount();
    controller.setRightMotorPwm(pwm);
    int currentCount = measurer.getRightCount();
    EXPECT_GT(initCount, currentCount);
  }

  // 左車輪のモータにPWM値をセットできるかのテスト
  TEST(ControllerTest, setLeftMotorPwm)
  {
    const int pwm = 50;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_LT(initCount, currentCount);
  }

  // 左車輪のモータにマイナスのPWM値をセットできるかどうかのテスト
  TEST(ControllerTest, setLeftMotorMinusPwm)
  {
    const int pwm = -50;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_GT(initCount, currentCount);
  }

  // モータに設定するPWM値の制限が行われているか確認するテスト
  TEST(ControllerTest, setLeftMotorPwmMin)
  {
    const int pwm = -150;
    controller.setLeftMotorPwm(Controller::MOTOR_PWM_MIN);
    int minCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(Controller::MOTOR_PWM_MIN * -1);
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_EQ(minCount, currentCount);
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
  }

  // stopArmMotor()を呼び出せるか確認するテスト
  TEST(ControllerTest, stopArmMotor)
  {
    controller.stopArmMotor();
    SUCCEED();
  }

}  // namespace etrobocon2024_test