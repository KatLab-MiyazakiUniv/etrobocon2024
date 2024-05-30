/**
 * @file   DummyRobot.h
 * @brief  実機内部の状態を管理するダミーファイル
 * @author keiya121
 */

#ifndef DUMMYROBOT_H
#define DUMMYROBOT_H

class DummyRobot {
public:
    // 実機内部のボタンの押下状態を表す列挙型
    enum class ButtonState {
        left,     // 実機の正面から見て左側のボタンが押されている状態
        enter,    // 実機の中央ボタンが押されている状態
        right,    // 実機の正面から見て右側のボタンが押されている状態
        none      // ボタンがいずれも押されていない状態
    };

    // コンストラクタ
    DummyRobot();

    // 実機内部のボタンの押下状態を設定するメソッド
    static void setButtonState(ButtonState state);

    // 実機内部のボタンの押下状態を取得するメソッド
    static ButtonState getButtonState() ;

private:
    // 実機内部のボタンの押下状態を管理するメンバ変数
    static ButtonState buttonState;
};

#endif
