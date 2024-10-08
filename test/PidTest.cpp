/**
 * @file PidTest.cpp
 * @brief PidGainクラス,Pidクラスをテストする
 * @author CHIHAYATAKU
 */

#include "Pid.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {
  TEST(PidGainTest, pidGain)
  {
    double kp = 0.1;
    double ki = 0.03;
    double kd = 0.612;
    PidGain actualPidGain(kp, ki, kd);
    double expected_kp = kp;
    double expected_ki = ki;
    double expected_kd = kd;
    EXPECT_DOUBLE_EQ(expected_kp, actualPidGain.kp);
    EXPECT_DOUBLE_EQ(expected_ki, actualPidGain.ki);
    EXPECT_DOUBLE_EQ(expected_kd, actualPidGain.kd);
  }

  TEST(PidGainTest, pidGainZero)
  {
    double kp = 0.0;
    double ki = 0.0;
    double kd = 0.0;
    PidGain actualPidGain(kp, ki, kd);
    double expected_kp = kp;
    double expected_ki = ki;
    double expected_kd = kd;
    EXPECT_DOUBLE_EQ(expected_kp, actualPidGain.kp);
    EXPECT_DOUBLE_EQ(expected_ki, actualPidGain.ki);
    EXPECT_DOUBLE_EQ(expected_kd, actualPidGain.kd);
  }

  TEST(PidGainTest, pidGainMinus)
  {
    double kp = -0.5;
    double ki = -0.2;
    double kd = -0.3;
    PidGain actualPidGain(kp, ki, kd);
    double expected_kp = 0;
    double expected_ki = 0;
    double expected_kd = 0;
    EXPECT_DOUBLE_EQ(expected_kp, actualPidGain.kp);
    EXPECT_DOUBLE_EQ(expected_ki, actualPidGain.ki);
    EXPECT_DOUBLE_EQ(expected_kd, actualPidGain.kd);
  }

  TEST(PidTest, calculatePid)
  {
    constexpr double DELTA = 0.01;
    double kp = 0.6;
    double ki = 0.02;
    double kd = 0.03;
    double targetValue = 70;
    Pid actualPid(kp, ki, kd, targetValue);
    double currentValue = 20;
    // 計算過程
    // 1. 前回の誤差
    // prevDeviation = 0
    // 2. 現在の誤差
    // currentDeviation = (70 - 20) = 50
    // 3. 微分の処理を行う
    // currentDerivative = (50 - 0) / 0.01 = 5000
    // 微分項に低域通過フィルタを適用
    // alpha = 0.8;
    // filteredDerivative = 0.8 * 5000 + (1 - 0.8) * 0 = 4000
    // 4. 誤差の積分を計算
    // integral = 0 + (50 + 0) * 0.01 / 2 = 0.25
    // 5. PID制御を計算
    // expected = 0.6 * 50 + 0.02 * 0.25 + 0.03 * 4000 = 150.005
    double expected = 150.005;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

  TEST(PidTest, calculatePidZero)
  {
    constexpr double DELTA = 0.01;
    double kp = 0.0;
    double ki = 0.0;
    double kd = 0.0;
    double targetValue = 0;
    Pid actualPid(kp, ki, kd, targetValue);
    double currentValue = 40;
    // 計算過程
    // 1. PID制御を計算
    // expected = 0 * currentDeviation + 0 * integral + 0 * derivative = 0
    double expected = 0;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

  TEST(PidTest, calculatePidMinus)
  {
    constexpr double DELTA = 0.01;
    double kp = -0.3;
    double ki = -0.02;
    double kd = -0.175;
    double targetValue = 100;
    Pid actualPid(kp, ki, kd, targetValue);
    double currentValue = 0;
    double expected = 0;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

  TEST(PidTest, calculatePidChangeDelta)
  {
    constexpr double DELTA = 0.03;
    double kp = 0.6;
    double ki = 0.02;
    double kd = 0.03;
    double targetValue = 70;
    Pid actualPid(kp, ki, kd, targetValue);
    double currentValue = 55;
    // 計算過程
    // 1. 前回の誤差
    // prevDeviation = 0
    // 2. 現在の誤差
    // currentDeviation = (70 - 55) = 15
    // 3. 微分の処理を行う
    // currentDerivative = (15 - 0) / 0.03 = 500
    // 微分項に低域通過フィルタを適用
    // alpha = 0.8;
    // filteredDerivative = 0.8 * 500 + (1 - 0.8) * 0 = 400
    // 4. 誤差の積分を計算
    // integral = 0 + (15 + 0) * 0.03 / 2 = 0.225
    // 5. PID制御を計算
    // expected = 0.6 * 15 + 0.02 * 0.225 + 0.03 * 400 = 21.0045
    double expected = 21.0045;
    // 第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue, DELTA));
  }

  TEST(PidTest, calculatePidChangeDeltaMinus)
  {
    constexpr double DELTA = -0.03;
    double kp = 0.6;
    double ki = 0.02;
    double kd = 0.03;
    double targetValue = 70;
    Pid actualPid(kp, ki, kd, targetValue);
    double currentValue = 55;
    // 計算過程
    // 1. 前回の誤差
    // prevDeviation = 0
    // 2. 現在の誤差
    // currentDeviation = (70 - 55) = 15
    // 3. 微分の処理を行う
    // currentDerivative = (15 - 0) / (-0.03) = -500
    // 微分項に低域通過フィルタを適用
    // alpha = 0.8;
    // filteredDerivative = 0.8 * (-500) + (1 - 0.8) * 0 = -400
    // 4. 誤差の積分を計算
    // integral = 0 + (15 + 0) * (-0.03) / 2 = -0.225
    // 5. PID制御を計算
    // expected = 0.6 * 15 + 0.02 * (-0.225) + 0.03 * (-400) = -3.0045
    double expected = -3.0045;
    // 第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue, DELTA));
  }

  // 周期に0を渡したときに、デフォルト周期0.01として計算されるかをテストする
  TEST(PidTest, calculatePidChangeDeltaZero)
  {
    constexpr double DELTA = 0;      // 実際に渡す周期
    constexpr double kdELTA = 0.01;  // 期待される周期
    double kp = 0.6;
    double ki = 0.02;
    double kd = 0.03;
    double targetValue = 70;
    Pid actualPid(kp, ki, kd, targetValue);
    double currentValue = 55;
    // 計算過程
    // 1. 前回の誤差
    // prevDeviation = 0
    // 2. 現在の誤差
    // currentDeviation = (70 - 55) = 15
    // 3. 微分の処理を行う
    // currentDerivative = (15 - 0) / 0.01 = 1500
    // 微分項に低域通過フィルタを適用
    // alpha = 0.8;
    // filteredDerivative = 0.8 * 1500 + (1 - 0.8) * 0 = 1200
    // 4. 誤差の積分を計算
    // integral = 0 + (15 + 0) * 0.01 / 2 = 0.075
    // 5. PID制御を計算
    // expected = 0.6 * 15 + 0.02 * 0.075 + 0.03 * 1200 = 45.0015
    double expected = 45.0015;
    // 第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue, DELTA));
  }

  // setしてcalculatePidを呼び出す(Setterのテスト)
  TEST(PidTest, caluclatePidSetter)
  {
    constexpr double DELTA = 0.01;
    double kp = 0.6;
    double ki = 0.05;
    double kd = 0.01;
    double targetValue = 70;
    Pid actualPid(kp, ki, kd, targetValue);
    double currentValue = 60;
    // 計算過程
    // 1. 前回の誤差
    // prevDeviation = 0
    // 2. 現在の誤差
    // currentDeviation = (70 - 60) = 10
    // 3. 微分の処理を行う
    // currentDerivative = (10 - 0) / 0.01 = 1000
    // 微分項に低域通過フィルタを適用
    // alpha = 0.8;
    // filteredDerivative = 0.8 * 1000 + (1 - 0.8) * 0 = 800
    // 4. 誤差の積分を計算
    // integral = 0 + (10 + 0) * 0.01 / 2 = 0.05
    // 5. PID制御を計算
    // expected = 0.6 * 10 + 0.05 * 0.05 + 0.01 * 800 = 14.0025
    double expected = 14.0025;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
    // 6. 前回の誤差の更新
    //  prevDeviation = 10
    kp = 0.1;
    ki = 0.2;
    kd = 0.3;
    actualPid.setPidGain(kp, ki, kd);  // PIDゲインの更新
    currentValue = 100;
    // 7. 現在の誤差
    // currentDeviation = (70 - 100) = -30
    // 8. 微分の処理を行う
    // currentDerivative = (-30 - 10) / 0.01 = -4000
    // 微分項に低域通過フィルタを適用
    // alpha = 0.8;
    // filteredDerivative = 0.8 * (-4000) + (1 - 0.8) * 800 = -3040
    // 9. 誤差の積分を計算
    // integral = 0.05 + (-30 + 10) * 0.01 / 2 = -0.05
    // 10. PID制御を計算
    // expected = 0.1 * (-30) + 0.2 * (-0.05) + 0.3 * (-3040) = -915.01
    expected = -915.01;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

}  // namespace etrobocon2024_test