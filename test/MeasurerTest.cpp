/**
 * @file MeasurerTest.cpp
 * @brief Measurerクラスをテストする
 * @author keiya121
 */

#include "Measurer.h"
#include "DummyRobot.h"
#include <gtest/gtest.h>

// rgb_raw_tの比較用関数
bool eqRgb(rgb_raw_t rgb1, rgb_raw_t rgb2)
{
  return rgb1.r == rgb2.r && rgb1.g == rgb2.g && rgb1.b == rgb2.b;
}

namespace etrobocon2024_test {

  // RGB値取得テスト
  TEST(RawColorTest, getRawColor)
  {
    Measurer measurer;
    rgb_raw_t expected1 = { 8, 9, 10 };       // black
    rgb_raw_t expected2 = { 104, 101, 146 };  // white
    rgb_raw_t expected3 = { 111, 19, 19 };    // red
    rgb_raw_t expected4 = { 120, 108, 71 };   // yellow
    rgb_raw_t expected5 = { 4, 75, 35 };      // green
    rgb_raw_t expected6 = { 81, 92, 144 };    // blue
    rgb_raw_t actual = measurer.getRawColor();

    ASSERT_TRUE(eqRgb(actual, expected1) || eqRgb(actual, expected2) || eqRgb(actual, expected3)
                || eqRgb(actual, expected4) || eqRgb(actual, expected5)
                || eqRgb(actual, expected6));
  }

  // 明度取得テスト
  TEST(BrightnessTest, getBrightness)
  {
    Measurer measurer;
    // 各色に対応する明度
    int expected1 = 3;
    int expected2 = 57;
    int expected3 = 43;
    int expected4 = 47;
    int expected5 = 29;
    int expected6 = 56;
    int actual = measurer.getBrightness();
    ASSERT_TRUE(actual == expected1 || actual == expected2 || actual == expected3
                || actual == expected4 || actual == expected5 || actual == expected6);
  }

  // 左モーター角位置取得テスト
  TEST(leftCountTest, getLeftCount)
  {
    Measurer measurer;
    int expected = 0;
    int actual = measurer.getLeftCount();

    EXPECT_EQ(expected, actual);
  }

  // 右モーター角位置取得テスト
  TEST(rightCountTest, getRightCount)
  {
    Measurer measurer;
    int expected = 0;
    int actual = measurer.getRightCount();

    EXPECT_EQ(expected, actual);
  }

  // アームモーター角位置取得テスト
  TEST(measurerTest, getArmMotorCount)
  {
    Measurer measurer;
    int expected = 0;
    int actual = measurer.getArmMotorCount();

    EXPECT_EQ(expected, actual);
  }

  // 左側ボタン押下時、実機内部で左側ボタン押下時の処理を行うケースのテスト
  TEST(leftButtonTestTrue, getLeftButton)
  {
    Measurer measurer;
    DummyRobot::setButtonState(
        DummyRobot::ButtonState::left);  // 実機のボタン押下状態を「左」に設定
    bool expected = true;
    bool actual = measurer.getLeftButton();

    EXPECT_EQ(expected, actual);
  }

  // 左側以外のボタン押下時（本テストでは右側)、実機内部で左側ボタン押下時の処理を行うケースのテスト
  TEST(leftButtonTestFalse, getLeftButton)
  {
    Measurer measurer;
    DummyRobot::setButtonState(
        DummyRobot::ButtonState::right);  // 実機のボタン押下状態を「右」に設定
    bool expected = false;
    bool actual = measurer.getLeftButton();

    EXPECT_EQ(expected, actual);
  }

  // 右側ボタン押下時、実機内部で右側ボタン押下時の処理を行うケースのテスト
  TEST(rightButtonTestTrue, getRightButton)
  {
    Measurer measurer;
    DummyRobot::setButtonState(
        DummyRobot::ButtonState::right);  // 実機のボタン押下状態を「右」に設定
    bool expected = true;
    bool actual = measurer.getRightButton();

    EXPECT_EQ(expected, actual);
  }

  // 右側以外のボタン押下時（本テストでは中央)、実機内部で右側ボタン押下時の処理を行うケースのテスト
  TEST(rightButtonTestFalse, getRightButton)
  {
    Measurer measurer;
    DummyRobot::setButtonState(
        DummyRobot::ButtonState::enter);  // 実機のボタン押下状態を「中央」に設定
    bool expected = false;
    bool actual = measurer.getRightButton();

    EXPECT_EQ(expected, actual);
  }

  // 中央ボタン押下時、実機内部で中央ボタン押下時の処理を行うケースのテスト
  TEST(enterButtonTestTrue, getEnterButton)
  {
    Measurer measurer;
    DummyRobot::setButtonState(
        DummyRobot::ButtonState::enter);  // 実機のボタン押下状態を「中央」に設定
    bool expected = true;
    bool actual = measurer.getEnterButton();

    EXPECT_EQ(expected, actual);
  }

  // 中央以外のボタン押下時（本テストでは右)、実機内部で中央ボタン押下時の処理を行うケースのテスト
  TEST(enterButtonTestFalse, getEnterButton)
  {
    Measurer measurer;
    DummyRobot::setButtonState(
        DummyRobot::ButtonState::right);  // 実機のボタン押下状態を「右」に設定
    bool expected = false;
    bool actual = measurer.getEnterButton();

    EXPECT_EQ(expected, actual);
  }

  // 超音波センサからの距離取得テスト
  TEST(forwardDistanceTest, getForwardDistance)
  {
    Measurer measurer;
    int expected = 99;  // 参照: SonarSensor.cpp　
    int actual = measurer.getForwardDistance();

    EXPECT_EQ(expected, actual);
  }

  // SPIKEの電圧取得テスト
  TEST(voltageTest, getVoltage)
  {
    Measurer measurer;
    int expected_min = 4;
    int expected_max = 7;
    int actual = measurer.getVoltage();

    EXPECT_GE(actual, expected_min);  // 4以上であることを確認
    EXPECT_LE(actual, expected_max);  // 7以下であることを確認
  }

}  // namespace etrobocon2024_test