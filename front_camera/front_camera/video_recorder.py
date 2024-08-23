import time
import picamera


class VideoRecorder:
    """カメラモジュールで動画を撮影するクラス"""

    def __init__(self, resolution=(1920, 1080), framerate=30) -> None:
        """コンストラクタ"""
        self.camera = picamera.PiCamera()
        self.camera.resolution = resolution
        self.camera.framerate = framerate

    def start_recording(self) -> None:
        """動画の撮影を開始する"""
        self.camera.start_recording()
        print("Recording started")

    def stop_recording(self) -> None:
        """動画の録画を停止する"""
        self.camera.stop_recording()
        print("Recording stopped")

    def close(self) -> None:
        """カメラを終了する"""
        self.camera.close()
        print("Camera module closed for recording video")


if __name__ == "__main__":
    video_recorder = VideoRecorder()

    try:
        # 出力する動画ファイルの名前
        output_file_name = "recorded_video.h264"

        video_recorder.start_recording(output_file_name)
        time.sleep(10)  # テストのため10秒間録画する
        video_recorder.stop_recording()

    finally:
        video_recorder.close()
