/**
 * @file ControllerTest.cpp
 * @brief Controllerクラスをテストする
 * @author takahashitom
 */

#include "ev3api.h"
#include "Controller.h"
#include "Measurer.h"
#include <gtest/gtest.h>

namespace etrobocon2023_test {
  Measurer measurer;
  Controller controller;

  TEST(ControllerTest, setRightMotorPwm)
  {
    const int pwm = 50;
    int initCount = measurer.getRightCount();
    controller.setRightMotorPwm(pwm);
    int currentCount = measurer.getRightCount();
    EXPECT_LT(initCount, currentCount);
  }

  TEST(ControllerTest, setRightMotorMinusPwm)
  {
    const int pwm = -30;
    int initCount = measurer.getRightCount();
    controller.setRightMotorPwm(pwm);
    int currentCount = measurer.getRightCount();
    EXPECT_GT(initCount, currentCount);
  }

  TEST(ControllerTest, setLeftMotorPwm)
  {
    const int pwm = 50;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_LT(initCount, currentCount);
  }

  TEST(ControllerTest, setLeftMotorMinusPwm)
  {
    const int pwm = -30;
    int initCount = measurer.getLeftCount();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_GT(initCount, currentCount);
  }

  TEST(ControllerTest, setLeftMotorPwmMin)
  {
    const int pwm = -150;
    controller.resetMotorPwm();
    controller.setLeftMotorPwm(Controller::MOTOR_PWM_MIN);
    int minCount = measurer.getLeftCount();
    controller.resetMotorPwm();
    controller.setLeftMotorPwm(pwm);
    int currentCount = measurer.getLeftCount();
    EXPECT_EQ(minCount, currentCount);
  }

  TEST(ControllerTest, stopMotor)
  {
    controller.stopMotor();
    SUCCEED();
  }

  TEST(ControllerTest, setArmMotorPwm)
  {
    const int pwm = 50;
    int initCount = measurer.getArmMotorCount();
    controller.setArmMotorPwm(pwm);
    int currentCount = measurer.getArmMotorCount();
    EXPECT_LT(initCount, currentCount);
  }

  TEST(ControllerTest, stopArmMotor)
  {
    controller.stopArmMotor();
    SUCCEED();
  }

}  // namespace etrobocon2023_test