"""
動画中のプラレールが最も手前に来たタイミングのフレームを返す
@author: bizyutyu
"""

import sys
import cv2
import numpy as np


class FrameTimingCalculator:
    def __init__(self, video_path, bounding_box_width=20, bounding_box_height=100):
        """コンストラクタ"""
        self.video_path = video_path
        self.bounding_box_width = bounding_box_width
        self.bounding_box_height = bounding_box_height

    def get_target_timing(self):
        """映像から特定のフレームを画像として切り出すタイミングを取得する"""
        sys.setrecursionlimit(5000)
        print(sys.getrecursionlimit())
        cap = cv2.VideoCapture(self.video_path)
        print(f"cap_prop_frame_width: {int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))}")
        print(f"cap_prop_frame_height: {int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))}")

        # 動画の最初のフレームを取得
        ret, first_frame = cap.read()
        if not ret:
            print("フレーム画像切り出しについて動画の初期フレーム取得に失敗。")
            return None

        # 黄色い長方形を検出
        yellow_rect = self.detect_yellow_rectangle(first_frame)

        if yellow_rect is None:
            # 黄色い長方形が見つからない場合は、画像中心付近にバウンディングボックスを配置
            width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
            box_x1 = width // 2 - self.bounding_box_width // 2
            box_y1 = 0
            print("yellow_rect is not found")
            print(f"box_x1={box_x1}, box_y1={box_y1}")
        else:
            # 黄色い長方形の下部にバウンディングボックスを配置
            box_x1 = yellow_rect[0] + yellow_rect[2] // 2 - self.bounding_box_width // 2
            box_y1 = yellow_rect[1] + yellow_rect[3]
            print("yellow_rect is found")
            print(f"box_x1={box_x1}, box_y1={box_y1}")

        box_x2 = box_x1 + self.bounding_box_width
        box_y2 = box_y1 + self.bounding_box_height

        print(f"box_x2={box_x2}, box_y2={box_y2}")

        entry_frame = None
        exit_frame = None
        frame_count = 0

        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                print("ret is false")
                cap.release()
                break

            frame_count += 1

            # バウンディングボックス内の領域を抽出（roi:Region of Interest (注目領域)の略です）
            roi = frame[box_y1:box_y2, box_x1:box_x2]
            print(f"roi.size:{roi.size}")

            # 動体検出（グレースケール化して閾値処理）
            gray_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
            _, thresh = cv2.threshold(gray_roi, 127, 255, cv2.THRESH_BINARY)

            # 動体が検出されたかチェック
            if np.sum(thresh) > 0 and entry_frame is None:
                entry_frame = frame_count
            elif np.sum(thresh) == 0 and entry_frame is not None and exit_frame is None:
                exit_frame = frame_count
                break

        cap.release()

        if entry_frame is None or exit_frame is None:
            print(
                "プラレールが侵入したフレーム、もしくは退出したフレームを検出できませんでした。"
            )
            return None

        center_frame = (entry_frame + exit_frame) // 2

        print(frame_count)

        return center_frame

    def detect_yellow_rectangle(self, frame):
        """配置エリアAにおける背景を検出するため、黄色の矩形を検出する。"""

        # HSV色空間に変換
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 黄色の範囲を定義
        lower_yellow = (20, 100, 100)
        upper_yellow = (30, 255, 255)

        # 黄色のマスクを作成
        mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

        # 輪郭を検出
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # 最大の輪郭を見つける
        if contours:
            largest_contour = max(contours, key=cv2.contourArea)
            return cv2.boundingRect(largest_contour)

        return None


if __name__ == "__main__":
    video_path = "video_data/recorded_video.h264"
    output_path = "Pla.jpg"

    frameTimingCalculator = FrameTimingCalculator(video_path)
    frameTimingCalculator.get_target_timing()
