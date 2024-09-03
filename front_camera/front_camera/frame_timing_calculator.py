"""
動画中のプラレールが最も手前に来たタイミングのフレームを返す
@author: bizyutyu YKhm20020 keiya121
"""

import os
import cv2
import numpy as np


class FrameTimingCalculator:
    def __init__(self, video_path, bounding_box_width=300, bounding_box_height=600):
        """コンストラクタ"""
        self.video_path = video_path
        self.bounding_box_width = bounding_box_width
        self.bounding_box_height = bounding_box_height

    def get_target_timing(self):
        """映像から特定のフレームを画像として切り出すタイミングを取得する"""
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
            width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
            height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
            box_x1 = yellow_rect[0] + (yellow_rect[2] // 2) - (self.bounding_box_width // 2)
            box_y1 = max((yellow_rect[1] + yellow_rect[3]), height // 4)
            print("yellow_rect is found")
            print(f"box_x1={box_x1}, box_y1={box_y1}")

        box_x2 = box_x1 + self.bounding_box_width
        box_y2 = box_y1 + self.bounding_box_height
        with_bbox = cv2.rectangle(
            first_frame,
            (box_x1, box_y1),
            (box_x2, box_y2),
            color=(255, 0, 0),
            thickness=4,
        )

        os.makedirs("confirmation_image", exist_ok=True)

        cv2.imwrite("confirmation_image/bbox.jpeg", with_bbox)
        print(f"box_x2={box_x2}, box_y2={box_y2}")

        base_frame = None
        entry_frame = None
        exit_frame = None
        avg = None
        frame_count = 0

        # バウンディングボックス内の動体検出処理
        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                print("最終フレームに到達")
                cap.release()
                break

            frame_count += 1

            # バウンディングボックス内の領域を抽出（roi:Region of Interest (注目領域)の略です）
            roi = frame[box_y1:box_y2, box_x1:box_x2]
            gray_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)

            if avg is None:
                avg = gray_roi.copy().astype(float)
                continue

            cv2.accumulateWeighted(gray_roi, avg, 0.01)

            prev_frame_diff = cv2.absdiff(gray_roi, cv2.convertScaleAbs(avg))
            _, prev_thresh = cv2.threshold(prev_frame_diff, 127, 255, cv2.THRESH_BINARY)

            prev_thresh = prev_thresh.tolist()
            
            # 動体がバウンディングボックス内に存在しないタイミングのフレームを基準フレームとする
            if base_frame is None:
                if sum(sum(row) for row in prev_thresh) == 0:
                    base_frame = gray_roi
                    print(f"Base frame set at frame {frame_count}")
                    if ret:
                        cv2.imwrite("confirmation_image/base.jpeg", frame)  # フレーム画像を保存
                        print(f"Entry frame saved as 'base.jpeg'")
                    else:
                        print("Failed to retrieve the base frame.")
                continue
            
            # プラレール・背景撮影のための動体検出処理
            # 注目領域侵入時のフレームとの二値差分画像を計算
            frame_diff = cv2.absdiff(base_frame, gray_roi)
            _, thresh = cv2.threshold(frame_diff, 127, 255, cv2.THRESH_BINARY)

            thresh = thresh.tolist()

            # 動体が検出されたかチェック
            if entry_frame is None and sum(sum(row) for row in thresh) > 10000:
                entry_frame = frame_count

                print("entry_frame:", entry_frame)

            elif (
                entry_frame != 0
                and sum(sum(row) for row in thresh) <= 10000
                and entry_frame is not None
                and exit_frame is None
            ):
                exit_frame = frame_count
                break

        if entry_frame is None:
            print("プラレールが侵入したフレームを検出できませんでした。")
            return None

        if exit_frame is None:
            print("プラレールが退出したフレームを検出できませんでした。")
            return None

        center_frame = (entry_frame + exit_frame) // 2

        cap = cv2.VideoCapture(self.video_path)
        cap.set(cv2.CAP_PROP_POS_FRAMES, center_frame)

        ret, frame = cap.read()  # フレーム画像を取得

        if ret:
            cv2.imwrite("confirmation_image/center.jpeg", frame)  # フレーム画像を保存
            print(f"Center frame saved as 'center.jpeg'")
        else:
            print("Failed to retrieve the center frame.")

        # entry_frameとexit_frameの画像も保存

        cap.set(cv2.CAP_PROP_POS_FRAMES, entry_frame)

        ret, frame = cap.read()  # フレーム画像を取得

        if ret:
            cv2.imwrite("confirmation_image/entry.jpeg", frame)  # フレーム画像を保存
            print(f"Entry frame saved as 'entry.jpeg'")
        else:
            print("Failed to retrieve the entry frame.")

        cap.set(cv2.CAP_PROP_POS_FRAMES, exit_frame)

        ret, frame = cap.read()  # フレーム画像を取得

        if ret:
            cv2.imwrite("confirmation_image/exit.jpeg", frame)  # フレーム画像を保存
            print(f"Exit frame saved as 'exit.jpeg'")
        else:
            print("Failed to retrieve the exit frame.")

        print("entry_frame:", entry_frame)
        print("exit_frame:", exit_frame)
        print("center_frame:", center_frame)

        cap.release()

        return center_frame

    def detect_yellow_rectangle(self, frame):
        """配置エリアAにおける背景を検出するため、黄色の矩形を検出する。"""

        # HSV色空間に変換
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 黄色の範囲を定義
        lower_yellow = (20, 160, 160)
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
    output_path = "image_data/Pla.jpg"

    frameTimingCalculator = FrameTimingCalculator(video_path)
    frameTimingCalculator.get_target_timing()
