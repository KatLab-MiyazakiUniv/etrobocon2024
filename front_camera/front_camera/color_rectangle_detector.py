"""
動画中の背景下部の指定色検出クラス
@author: bizyutyu YKhm20020 CHIHAYATAKU
"""

import cv2



class ColorRectangleDetector:
    # 色のHSV範囲を定数として定義
    COLOR_BOUNDS = {
        'yellow': ((20, 160, 160), (30, 255, 255)),
        'red': ((0, 160, 160), (10, 255, 255)),
    }

    def __init__(self, color="yellow"):
        """コンストラクタ

        Args:
            color (str): 検出する色の名前。COLOR_BOUNDSに定義された色から選択する。
        """
        # 対象の色の範囲を保持
        if color not in self.COLOR_BOUNDS:
            raise ValueError(f"{color}は定義されていません。定義されている色: {list(self.COLOR_BOUNDS.keys())}")
        self.lower_bound, self.upper_bound = self.COLOR_BOUNDS[color]
        self.color = color


    def detect_rectangle(self, frame):
        """対象色の矩形を検出する。

        Args:
            frame (int): 動画の何フレーム目を検出の対象とするかを示す数値
        """

        # HSV色空間に変換
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 対象の色のマスクを作成
        mask = cv2.inRange(hsv, self.lower_bound, self.upper_bound)

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
