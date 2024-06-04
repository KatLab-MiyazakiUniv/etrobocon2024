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
    double prevDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * kp;
    double i = (currentDeviation + prevDeviation) * DELTA / 2 * ki;
    double d = (currentDeviation - prevDeviation) * kd / DELTA;
    double expected = p + i + d;
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
    double prevDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * kp;
    double i = (currentDeviation + prevDeviation) * DELTA / 2 * ki;
    double d = (currentDeviation - prevDeviation) * kd / DELTA;
    double expected = p + i + d;
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
    double prevDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * kp;
    double i = (currentDeviation + prevDeviation) * DELTA / 2 * ki;
    double d = (currentDeviation - prevDeviation) * kd / DELTA;
    double expected = p + i + d;
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
    double prevDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * kp;
    double i = (currentDeviation + prevDeviation) * DELTA / 2 * ki;
    double d = (currentDeviation - prevDeviation) * kd / DELTA;
    double expected = p + i + d;
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
    double prevDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * kp;
    double i = (currentDeviation + prevDeviation) * kdELTA / 2 * ki;
    double d = (currentDeviation - prevDeviation) * kd / kdELTA;
    double expected = p + i + d;
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
    double prevDeviation = 0;
    double currentDiviation = (targetValue - currentValue);          // 現在の偏差
    double p = currentDiviation * kp;                                // P制御
    double i = (currentDiviation + prevDeviation) * DELTA / 2 * ki;  // I制御(誤差の累積は0)
    double d = (currentDiviation - prevDeviation) * kd / DELTA;      // D制御(前回の誤差は0)
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));

    double integral = (currentDiviation + prevDeviation) * DELTA / 2;  // 誤差の累積
    prevDeviation += currentDiviation;                                 // 前回の誤差の更新
    kp = 0.1;
    ki = 0.2;
    kd = 0.3;
    actualPid.setPidGain(kp, ki, kd);  // PIDゲインの更新
    currentValue = 100;
    currentDiviation = (targetValue - currentValue);
    integral += (currentDiviation + prevDeviation) * DELTA / 2;
    p = currentDiviation * kp;
    i = integral * ki;
    d = (currentDiviation - prevDeviation) / DELTA * kd;
    expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

}  // namespace etrobocon2024_test