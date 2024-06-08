/**
 * @file MileageTest.cpp
 * @brief 走行距離の測定用クラスのテスト
 * @author YKhm20020
 */

#include "Mileage.h"
#include <cmath>
#include <gtest/gtest.h>

namespace etrobocon2024_test {
  TEST(MileageTest, calculateMileage)
  {
    double radius = 50.0;
    double rightAngle = 30.0;
    double leftAngle = 40.0;
    double rightWheelMileage = 2.0 * rightAngle * radius * M_PI / 360.0;
    double leftWheelMileage = 2.0 * leftAngle * radius * M_PI / 360.0;
    double expected = (rightWheelMileage + leftWheelMileage) / 2.0;
    double actual = Mileage::calculateMileage(rightAngle, leftAngle);
    EXPECT_DOUBLE_EQ(expected, actual);
  }

  TEST(MileageTest, calculateMileageMinus)
  {
    double radius = 50.0;
    double rightAngle = -30.0;
    double leftAngle = -40.0;
    double rightWheelMileage = 2.0 * rightAngle * radius * M_PI / 360.0;
    double leftWheelMileage = 2.0 * leftAngle * radius * M_PI / 360.0;
    double expected = (rightWheelMileage + leftWheelMileage) / 2.0;
    double actual = Mileage::calculateMileage(rightAngle, leftAngle);
    EXPECT_DOUBLE_EQ(expected, actual);
  }

  TEST(MileageTest, calculateMileageZero)
  {
    double radius = 50.0;
    double rightAngle = 0.0;
    double leftAngle = 0.0;
    double rightWheelMileage = 2.0 * rightAngle * radius * M_PI / 360.0;
    double leftWheelMileage = 2.0 * leftAngle * radius * M_PI / 360.0;
    double expected = (rightWheelMileage + leftWheelMileage) / 2.0;
    double actual = Mileage::calculateMileage(rightAngle, leftAngle);
    EXPECT_DOUBLE_EQ(expected, actual);
  }
}  // namespace etrobocon2024_test
