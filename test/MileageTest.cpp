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

    // 計算過程
    // 1.右車輪の累計走行距離を算出
    // double rightWheelMileage = 2.0 * rightAngle * radius * M_PI / 360.0;
    // M_PI = 3.14: rightWheelMileage = 2.0 * 30.0 * 50.0 * 3.14 / 360.0 = 26.1666...
    // M_PI = 3.15: rightWheelMileage = 2.0 * 30.0 * 50.0 * 3.15 / 360.0 = 26.25
    // 2.左車輪の累計走行距離を算出
    // double leftWheelMileage = 2.0 * leftAngle * radius * M_PI / 360.0;
    // M_PI = 3.14: leftWheelMileage = 2.0 * 40.0 * 50.0 * 3.14 / 360.0 = 32.1111...
    // M_PI = 3.15: leftWheelMileage = 2.0 * 40.0 * 50.0 * 3.15 / 360.0 = 35.0
    // 3.両車輪の累計走行距離の平均を算出
    // double expected = (rightWheelMileage + leftWheelMileage) / 2.0;
    // M_PI = 3.14: (26.1666... + 32.1111...) / 2 = 29.13888...
    // M_PI = 3.15: (26.25 + 35) / 2 = 30.625
    double expected_min = 29.13888;
    double expected_max = 30.625;

    // actual: 30.543261909900767
    double actual = Mileage::calculateMileage(rightAngle, leftAngle);

    // M_PIが3.14で計算した値よりも大きいアサーションと、3.15で計算した値よりも小さいアサーションを両方満たすか
    EXPECT_LT(expected_min, actual);
    EXPECT_GT(expected_max, actual);
  }

  TEST(MileageTest, calculateMileageMinus)
  {
    double radius = 50.0;
    double rightAngle = -30.0;
    double leftAngle = -40.0;
    double expected_min = -30.625;
    double expected_max = -29.13888;
    double actual = Mileage::calculateMileage(rightAngle, leftAngle);
    EXPECT_LT(expected_min, actual);
    EXPECT_GT(expected_max, actual);
  }

  TEST(MileageTest, calculateMileageZero)
  {
    double radius = 50.0;
    double rightAngle = 0.0;
    double leftAngle = 0.0;
    double expected = 0.0;
    double actual = Mileage::calculateMileage(rightAngle, leftAngle);
    EXPECT_DOUBLE_EQ(expected, actual);
  }
}  // namespace etrobocon2024_test
