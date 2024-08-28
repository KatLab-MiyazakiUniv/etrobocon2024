"""
動画中のプラレールが最も手前に来たタイミングのフレームを返す
@author: bizyutyu
"""

import cv2
import numpy as np

class FrameTimingCalculator:
    def __init__(self, video_path, bounding_box_width=50, bounding_box_height=100):
        self.video_path = video_path
        self.bounding_box_width = bounding_box_width
        self.bounding_box_height = bounding_box_height

    def get_target_timing(self):
        cap = cv2.VideoCapture(self.video_path)
        
        # 動画の最初のフレームを取得
        ret, first_frame = cap.read()
        if not ret:
            return None

        # 黄色い長方形を検出
        yellow_rect = self.detect_yellow_rectangle(first_frame)
        if yellow_rect is None:
            # 黄色い長方形が見つからない場合は、画像中心付近にバウンディングボックスを配置
            width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
            box_x1 = width // 2 - self.bounding_box_width // 2
            box_y1 = 0
        else:
            # 黄色い長方形の下部にバウンディングボックスを配置
            box_x1 = yellow_rect[0] + yellow_rect[2] // 2 - self.bounding_box_width // 2
            box_y1 = yellow_rect[1] + yellow_rect[3]

        box_x2 = box_x1 + self.bounding_box_width
        box_y2 = box_y1 + self.bounding_box_height
        
        entry_frame = None
        exit_frame = None
        frame_count = 0
        
        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                break
            
            frame_count += 1
            
            # バウンディングボックス内の領域を抽出（roi:Region of Interestの略です）
            roi = frame[:, box_x1:box_x2]
            
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
            return None
        
        center_frame = (entry_frame + exit_frame) // 2
        return center_frame

    def detect_yellow_rectangle(self, frame):
        # HSV色空間に変換
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 黄色の範囲を定義
        lower_yellow = np.array([20, 100, 100])
        upper_yellow = np.array([30, 255, 255])

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
    