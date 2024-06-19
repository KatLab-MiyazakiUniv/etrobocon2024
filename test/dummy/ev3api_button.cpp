/**
 * @file ev3api_button.cpp
 * @brief ボタン関連のダミー
 * @author keiya121
 */

#include "ev3api_button.h"
#include "../DummyRobot.h"

bool ev3_button_is_pressed(button_t button)
{
  bool judge = false;

  DummyRobot::ButtonState currentButtonState = DummyRobot::getButtonState();

  // 左ボタンが押された時
  if(button == LEFT_BUTTON && currentButtonState == DummyRobot::ButtonState::left) judge = true;

  // 右ボタンが押された時
  if(button == RIGHT_BUTTON && currentButtonState == DummyRobot::ButtonState::right) judge = true;

  // 中央ボタンが押された時
  if(button == ENTER_BUTTON && currentButtonState == DummyRobot::ButtonState::enter) judge = true;

  if(button != LEFT_BUTTON && button != RIGHT_BUTTON && button != ENTER_BUTTON) {
    printf("\x1b[31m");  // 前景色を赤に
    printf("error: Variable \"button\" is an unexpected value");
    printf("\x1b[39m\n");  // 前景色をデフォルトに戻す
  }

  // 次のボタンの状態を設定する
  int nextButtonState = rand() % 4;
  if(nextButtonState == 0) {
    DummyRobot::setButtonState(DummyRobot::ButtonState::left);
  } else if(nextButtonState == 1) {
    DummyRobot::setButtonState(DummyRobot::ButtonState::enter);
  } else if(nextButtonState == 2) {
    DummyRobot::setButtonState(DummyRobot::ButtonState::right);
  } else if(nextButtonState == 3) {
    DummyRobot::setButtonState(DummyRobot::ButtonState::none);
  }

  return judge;
}