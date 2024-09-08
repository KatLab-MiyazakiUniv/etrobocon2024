"""
フロントカメラから画像を取得する
@author: bizyutyu YKhm20020 keiya121
"""

from picamera2 import Picamera2, MappedArray
from datetime import datetime
from typing import Tuple, Union
from PIL import Image
import cv2
import numpy as np
import os
import argparse


class CameraInterface:
    def __init__(
        self,
        camera_id: int = 0,
        data_format: str = "RGB888",
        size: Tuple[int, int] = (800, 600),
    ) -> None:
        """コンストラクタ

        Args:
            camera_id (int): カメラID、初期値は 0
            data_format (str): カラーフォーマット、初期値は "RGB888"
            size (Tuple[int, int]): カメラの解像度、初期値は (1640, 1232)
        """
        self.camera_id = camera_id
        # self.cap = cv2.VideoCapture(camera_id)
        # self.picam2 = Picamera2()
        # self.picam2.configure(self.picam2.create_still_configuration())
        # self.picam2.start()
        self.format = data_format
        self.size = size
        self.picam2 = None

    def start_camera(self) -> None:
        """Picamera2インスタンスの初期化を行う."""
        if self.picam2 is None:
            picam2 = Picamera2(camera_num=self.camera_id)
            conf = picam2.create_preview_configuration(
                main={"format": self.format, "size": self.size}
            )
            picam2.configure(conf)
            picam2.start()
            self.picam2 = picam2

    def capture_image(self) -> Union[np.ndarray, None]:
        """カメラで画像を取得する関数.

        Returns:
            Union[np.ndarray, None]: カメラ画像データ
        """
        return self.picam2.capture_array()

        # camera.capture_image_cv2("captured_image_cv2.jpeg")
        # camera.capture_image_picamera2("captured_image_picamera2.jpeg")
        # buffer = camera.capture_buffers()
        # array = camera.capture_array()
        # print("Buffer captured:", buffer)
        # print("Array captured:", array)

    def capture_save_image(self, save_path) -> None:
        """カメラで画像を取得し、保存する関数.

        Args:
            save_path (str): 画像の保存先パス(拡張子込み)
        """
        img = self.capture_image()
        img = np.array(img)
        img = img[:, :, ::-1]
        im = Image.fromarray(img)
        im.save(save_path)

    def capture_image_cv2(self, save_path):
        """OpenCVを用いて画像を取得する関数.

        Args:
            save_path (str): 画像の保存先パス(拡張子込み)

        Raises:
            Exception: 画像情報の取得に失敗
        """
        ret, frame = self.cap.read()
        if ret:
            cv2.imwrite(save_path, frame)
        else:
            raise Exception("Failed to capture image")

    def capture_image_picamera2(self, save_path):
        """Picamera2を用いて画像を取得する関数.

        Args:
            save_path (str): 画像の保存先パス(拡張子込み)
        """
        self.picam2.capture_file(save_path)

    def capture_buffers(self):
        buffer = self.picam2.capture_buffer("main")
        return buffer

    def capture_array(self):
        with MappedArray(self.picam2.capture_buffer("main")) as m:
            array = np.array(m.array)
        return array

    def release(self):
        self.cap.release()
        self.picam2.stop()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="フロントカメラに関するプログラム")
    parser.add_argument("--camera-num", type=int, default=0, help="カメラIDを指定する")
    parser.add_argument(
        "-spath", "--save_path", type=str, default=None, help="保存する画像の名前を指定"
    )
    args = parser.parse_args()
    camera = CameraInterface()

    # 保存用フォルダの作成
    current_path = os.path.dirname(os.path.abspath(__file__))
    parent_path = os.path.dirname(current_path)
    folder_path = os.path.join(parent_path, "image_data")
    if not os.path.exists(folder_path):
        os.mkdir(folder_path)

    # 画像の取得
    camera = CameraInterface(camera_id=args.camera_num)
    camera.start_camera()

    # リアカメラで画像を１枚取得する
    if args.save_path is not None:
        save_path = os.path.join(folder_path, args.save_path)
    else:
        file_name = datetime.now().strftime("%Y-%m-%d_%H-%M-%S") + ".jpeg"
        save_path = os.path.join(folder_path, file_name)

    camera.capture_save_image(save_path)
