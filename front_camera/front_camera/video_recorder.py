"""
フロントカメラから動画を取得する
@author: YKhm20020 bizyutyu
"""

import time
from picamera2 import Picamera2
from picamera2.encoders import H264Encoder


class VideoRecorder:
    """カメラモジュールで動画を撮影するクラス"""

    def __init__(self, camera_id: int = 0, resolution=(1920, 1080), framerate=30) -> None:
        """コンストラクタ"""
        self.__camera_id = camera_id 
        self.__resolution = resolution
        self.__framerate = framerate
        self.__camera = None
    
    def start_camera(self) -> None:
        """Picamera2のインスタンス生成"""
        if self.__camera is None:
            camera = Picamera2()
            video_config = camera.create_video_configuration()
            # camera = Picamera2(camera_id = self.__camera_id)
            # video_config = camera.create_video_configuration(main={"size": self.__resolution, "framerate": self.__framerate})
            camera.configure(video_config)
            self.__camera = camera


    def start_recording(self, encoder, output) -> None:
        """動画の撮影を開始する"""
        self.__camera.start_recording(encoder, output)
        print("Recording started")

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
        # 出力する動画ファイルの名前
        encoder = H264Encoder(bitrate=10000000)
        output_file_name = "recorded_video.h264"

        video_recorder.start_recording(encoder, output_file_name)
        time.sleep(10)  # テストのため10秒間録画する
        video_recorder.stop_recording()

    finally:
        video_recorder.close()
