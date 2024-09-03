"""
フロントカメラから動画を取得する
@author: YKhm20020 bizyutyu
"""

import os
import time
from typing import Tuple
from picamera2 import Picamera2
from picamera2.encoders import H264Encoder


class VideoRecorder:
    """カメラモジュールで動画を撮影するクラス"""

    def __init__(
        self, camera_id: int = 0, size: Tuple[int, int] = (1640, 1232)
    ) -> None:
        """コンストラクタ

        Args:
            camera_id (int): カメラID、初期値は 0
            size (Tuple[int, int]): カメラの解像度、初期値は (1640, 1232)
        """
        self.__camera_id = camera_id
        self.__size = size
        self.__camera = None

    def start_camera(self) -> None:
        """Picamera2のインスタンス生成"""
        if self.__camera is None:
            camera = Picamera2()
            video_config = camera.create_video_configuration(main={"size": self.__size})
            camera.configure(video_config)
            self.__camera = camera

    def start_recording(self, output) -> None:
        """動画の撮影を開始する

        Args:
            output (str): 画像の保存先パス(拡張子込み)
        """
        print("Recording started")
        self.__camera.start_and_record_video(output, duration=20)
        print("Recording stopped")

    def stop_recording(self) -> None:
        """動画の録画を停止する"""
        self.__camera.stop_recording()
        print("Recording stopped")

    def close(self) -> None:
        """カメラを終了する"""
        self.__camera.close()
        print("Camera module closed for recording video")


if __name__ == "__main__":
    video_recorder = VideoRecorder()
    video_recorder.start_camera()

    try:
        os.makedirs("video_data", exist_ok=True)

        # 出力する動画ファイルの名前
        encoder = H264Encoder(bitrate=10000000)
        output_file_name = "video_data/recorded_video.h264"

        video_recorder.start_recording(encoder, output_file_name)
        time.sleep(10)  # テストのため10秒間録画する
        video_recorder.stop_recording()

    finally:
        video_recorder.close()
