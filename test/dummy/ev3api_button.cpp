/**
 * @file ev3api_button.cpp
 * @brief ボタン関連のダミー
 * @author keiya121
 */

#include "ev3api_button.h"
#include "../DummyRobot.h"
#include <iostream>

bool ev3_button_is_pressed(button_t button)
{
  DummyRobot::ButtonState currentButtonState = DummyRobot::getButtonState();

  //   std::cout << "Current ButtonState: ";
  //   switch (currentButtonState) {
  //       case DummyRobot::ButtonState::left:
  //           std::cout << "Left" << std::endl;
  //           break;
  //       case DummyRobot::ButtonState::enter:
  //           std::cout << "Enter" << std::endl;
  //           break;
  //       case DummyRobot::ButtonState::right:
  //           std::cout << "Right" << std::endl;
  //           break;
  //       case DummyRobot::ButtonState::none:
  //           std::cout << "None" << std::endl;
  //           break;
  //   }

  // 左ボタンが押された時（num=0）
  if(button == LEFT_BUTTON && currentButtonState == DummyRobot::ButtonState::left) return true;

  // 右ボタンが押された時（num=1）
  if(button == RIGHT_BUTTON && currentButtonState == DummyRobot::ButtonState::right) return true;

  // 中央ボタンが押された時（num=2）
  if(button == ENTER_BUTTON && currentButtonState == DummyRobot::ButtonState::enter) return true;

  if(button != LEFT_BUTTON && button != RIGHT_BUTTON && button != ENTER_BUTTON) {
    printf("\x1b[31m");  // 前景色を赤に
    printf("error: Variable \"button\" is an unexpected value");
    printf("\x1b[39m\n");  // 前景色をデフォルトに戻す
  }

  return false;
}