"""
プラレール・背景用送信画像を撮影する
@author: bizyutyu 
"""

import cv2
import os
import time


class CapturePlarailImage:
    def __init__(self, video_path, bounding_box_width=100, bounding_box_height=200):
        """コンストラクタ"""
        self.video_path = video_path
        self.bounding_box_width = bounding_box_width
        self.bounding_box_height = bounding_box_height
        self.frame_timing_calculator = FrameTimingCalculator(video_path)

    def capture_and_extract_frame(self, output_path):
        self.video_recorder.start_camera()

        try:
            cap = cv2.VideoCapture(0)  # ラズパイのカメラを使用
            
            # 最初のフレームを取得して黄色い長方形を検出
            ret, first_frame = cap.read()
            if not ret:
                print("カメラからのフレーム取得に失敗しました。")
                return

            yellow_rect = self.detect_yellow_rectangle(first_frame)

            if yellow_rect is None:
                width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
                box_x1 = width // 2 - self.bounding_box_width // 2
                box_y1 = 0
            else:
                box_x1 = yellow_rect[0] + yellow_rect[2] // 2 - self.bounding_box_width // 2
                box_y1 = (yellow_rect[1] + yellow_rect[3]) * 3

            box_x2 = box_x1 + self.bounding_box_width
            box_y2 = box_y1 + self.bounding_box_height

            entry_frame = None
            exit_frame = None
            frame_count = 0
            avg = None

            while True:
                ret, frame = cap.read()
                if not ret:
                    break

                frame_count += 1

                roi = frame[:, box_x1:box_x2]
                gray_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)

                if avg is None:
                    avg = gray_roi.copy().astype(float)
                    continue

                cv2.accumulateWeighted(gray_roi, avg, 0.001)
                frame_diff = cv2.absdiff(gray_roi, cv2.convertScaleAbs(avg))
                _, thresh = cv2.threshold(frame_diff, 127, 255, cv2.THRESH_BINARY)

                if np.sum(thresh) != 0 and entry_frame is None:
                    entry_frame = frame_count
                elif entry_frame is not None and np.sum(thresh) == 0 and exit_frame is None:
                    exit_frame = frame_count
                    break

            cap.release()

            if entry_frame is None or exit_frame is None:
                print("プラレールの侵入または退出を検出できませんでした。")
                return

            target_frame = (entry_frame + exit_frame) // 2

            cap = cv2.VideoCapture(0)
            cap.set(cv2.CAP_PROP_POS_FRAMES, target_frame)
            ret, frame = cap.read()

            if ret:
                cv2.imwrite(output_path, frame)
                print(f"目標フレームを {output_path} に保存しました。")
            else:
                print("目標フレームの取得に失敗しました。")

            cap.release()

        finally:
            self.video_recorder.close()


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
    output_image_path = "Pla.jpeg"
    extractor = CapturePlarailImage()
    extractor.capture_and_extract_frame(output_image_path)
