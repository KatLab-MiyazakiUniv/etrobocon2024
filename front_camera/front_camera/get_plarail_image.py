"""
プラレール・背景撮影動画から画像を取得する
@author: bizyutyu YKhm20020
"""

import cv2
import os
import time
from frame_timing_calculator import FrameTimingCalculator
from video_recorder import VideoRecorder
from picamera2.encoders import H264Encoder


class GetPlarailImage:
    def __init__(self, video_path):
        """コンストラクタ"""
        self.video_path = video_path
        self.frame_timing_calculator = FrameTimingCalculator(video_path)

    def extract_target_frame(self, output_path) -> None:
        """映像から特定のフレームを画像として切り出す"""
        # 目標フレームを取得
        target_frame = self.frame_timing_calculator.get_target_timing()

        if target_frame is None:
            print("目標フレームの取得に失敗しました。")
            return

        # 動画を開く
        cap = cv2.VideoCapture(self.video_path)

        # 目標フレームに移動
        cap.set(cv2.CAP_PROP_POS_FRAMES, target_frame)

        # フレームを読み込む
        ret, frame = cap.read()

        if ret:
            # フレームをJPEG形式で保存
            cv2.imwrite(output_path, frame)
            print(f"目標フレームを {output_path} に保存しました。")
        else:
            print("フレームの読み込みに失敗しました。")

        # キャプチャを解放
        cap.release()


if __name__ == "__main__":
    video_recorder = VideoRecorder()
    video_recorder.start_camera()

    try:
        os.makedirs("video_data", exist_ok=True)

        # 出力する動画ファイルの名前
        encoder = H264Encoder(bitrate=10000000)
        output_video_path = "video_data/recorded_video.h264"

        video_recorder.start_recording(encoder, output_video_path)
        time.sleep(20)  # 20秒間録画する
        video_recorder.stop_recording()

    finally:
        video_recorder.close()

    output_image_path = "Pla.jpeg"
    extractor = GetPlarailImage(output_video_path)
    extractor.extract_target_frame(output_image_path)
