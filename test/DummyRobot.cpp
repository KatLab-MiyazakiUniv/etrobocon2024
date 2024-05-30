/**
 * @file   DummyRobot.cpp
 * @brief  実機内部の状態を管理するダミーファイル
 * @author keiya121
 */


#include "DummyRobot.h"

// 静的メンバ変数の初期化
DummyRobot::ButtonState DummyRobot::buttonState = DummyRobot::ButtonState::none;

// コンストラクタ
DummyRobot::DummyRobot() {}

// 実機内部のボタンの押下状態を設定する静的メソッド
void DummyRobot::setButtonState(ButtonState state) {
    buttonState = state;
}

// 実機内部のボタンの押下状態を取得する静的メソッド
DummyRobot::ButtonState DummyRobot::getButtonState() {
    return buttonState;
}
