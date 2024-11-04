"""
動画中の背景下部の指定色検出クラス
@author: bizyutyu YKhm20020 CHIHAYATAKU
"""
import cv2
import numpy as np
import os

class ColorRectangleDetector:
    # 色のHSV範囲を定数として定義
    COLOR_BOUNDS = {
        'YELLOW': ((20, 160, 160), (30, 255, 255)),
        'RED': [
            ((0, 70, 50), (10, 255, 255)),     # 赤色の低色相側
            ((173, 70, 50), (180, 255, 255))    # 赤色の高色相側
        ]
    }

    def __init__(self, color):
        """コンストラクタ
        Args:
            color (str): 検出する色の名前。COLOR_BOUNDSに定義された色から選択する。
        """
        # 対象の色の範囲を保持
        if color not in self.COLOR_BOUNDS:
            raise ValueError(f"{color}は定義されていません。定義されている色: {list(self.COLOR_BOUNDS.keys())}")

        self.bounds = self.COLOR_BOUNDS[color]
        self.color = color

    def detect_rectangle(self, frame):
        """対象色の矩形を検出する。
        Args:
            frame (numpy.ndarray): 処理対象の画像データ
        """
        # HSV色空間に変換
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        # 対象の色のマスクを作成
        if self.color == 'RED':
            # 赤色の場合、両方の範囲のマスクを作成して結合
            mask_red_lower = cv2.inRange(hsv, self.bounds[0][0], self.bounds[0][1])
            mask_red_upper = cv2.inRange(hsv, self.bounds[1][0], self.bounds[1][1])
            mask = cv2.bitwise_or(mask_red_lower, mask_red_upper)
        else:
            mask = cv2.inRange(hsv, self.bounds[0], self.bounds[1])

        # 収縮処理を行う
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
        erosion = cv2.erode(mask, kernel, iterations=1)

        # マスク画像を保存（確認用）
        # 保存先パスを指定
        save_dir = "confirmation_image"
        mask_path = os.path.join(save_dir, "mask_image.jpeg")
        erosion_path = os.path.join(save_dir, "erosion_image.jpeg")
        cv2.imwrite(mask_path, mask)  # マスク画像を保存
        cv2.imwrite(erosion_path, erosion)  # 収縮処理画像を保存

        if self.color == 'RED':
            # 赤色の場合、2階層構造を考慮して最大の輪郭を見つける
            # 輪郭を検出し、2階層の階層構造を取得
            contours, hierarchy = cv2.findContours(erosion, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)
            # 最大の面積を持つ輪郭を探す
            largest_contour_index = None
            max_area = 0

            for i in range(len(contours)):
                #  外側の輪郭だけを対象にする
                if hierarchy[0][i][3] == -1: # 親がいない輪郭のみ
                    area = cv2.contourArea(contours[i])
                    child_index = hierarchy[0][i][2]
                    if child_index != -1:
                        area -= cv2.contourArea(contours[child_index])

                    if area > max_area:
                        max_area = area
                        largest_contour_index = i

            # 最大の輪郭が見つかれば、その輪郭の矩形座標を返す
            if largest_contour_index is not None:
                return cv2.boundingRect(contours[largest_contour_index])
        else:
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
