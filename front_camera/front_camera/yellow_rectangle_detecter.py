"""
動画中の背景下部の黄色検出クラス
@author: bizyutyu
"""

import cv2



class YellowRectangleDetecter:
    def __init__(self, lower_yellow = (20, 160, 160), upper_yellow = (30, 255, 255)):
        """コンストラクタ

        Args:
            video_path (str): 動画の保存先パス(拡張子込み)
            bounding_box_width (int): 注目領域とするバウンディングボックスの幅、初期値は300
            bounding_box_height (int): 注目領域とするバウンディングボックスの高さ 初期値は600
        """
        # 受け取った黄色の範囲を保持
        self.lower_yellow = lower_yellow
        self.upper_yellow = upper_yellow


    def detect_yellow_rectangle(self, frame):
        """配置エリアAにおける背景を検出するため、黄色の矩形を検出する。
        Args:
            frame (int): 動画の何フレーム目を検出の対象とするかを示す数値
        """

        # HSV色空間に変換
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 黄色のマスクを作成
        mask = cv2.inRange(hsv, self.lower_yellow, self.upper_yellow)

        # 輪郭を検出
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # 最大の輪郭を見つける
        if contours:
            largest_contour = max(contours, key=cv2.contourArea)
            return cv2.boundingRect(largest_contour)

        return None


if __name__ == "__main__":
    video_path = "video_data/recorded_video.h264"
    output_path = "image_data/Pla.jpg"

    frameTimingCalculator = FrameTimingCalculator(video_path)
    frameTimingCalculator.get_target_timing()
