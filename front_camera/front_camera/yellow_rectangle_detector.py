"""
動画中の背景下部の黄色検出クラス
@author: bizyutyu YKhm20020
"""

import cv2



class YellowRectangleDetector:
    def __init__(self, lower_yellow = (20, 160, 160), upper_yellow = (30, 255, 255)):
        """コンストラクタ

        Args:
            lower_yellow (tuple): 黄色と認識するBGR値範囲の下限、初期値は (20, 160, 160).
            upper_yellow (tuple): 黄色と認識するBGR値範囲の上限、初期値は (30, 255, 255).
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

    # 循環インポート回避のため一旦コメントアウト
    # frameTimingCalculator = FrameTimingCalculator(video_path)
    # frameTimingCalculator.get_target_timing()
