"""
指定画像中の背景（の黄色矩形）が中心に来るような補正角度を返す
@author: bizyutyu YKhm20020 keiya121
"""

import argparse
import os
import cv2
import math
from .camera_interface import CameraInterface
from .yellow_rectangle_detector import YellowRectangleDetector

class GetCorrectionAngle:
    def __init__(self):
        self.yellow_rectangle_detector = YellowRectangleDetector()

    def calculate_correction_angle(self, image_path):
        # 画像を読み込む
        image = cv2.imread(image_path)
        if image is None:
            raise ValueError(f"画像を読み込めませんでした: {image_path}")

        # 画像の中心を計算
        image_center_x = image.shape[1] // 2
        image_center_y = image.shape[0] // 2

        # 黄色い長方形を検出
        yellow_rect = self.yellow_rectangle_detector.detect_yellow_rectangle(image)
        if yellow_rect is None:
            raise ValueError("黄色い長方形が検出されませんでした")

        # 黄色い長方形の中心のx座標を計算
        rect_center_x = yellow_rect[0] + yellow_rect[2] // 2

        # x軸方向の偏差を計算
        delta_x = rect_center_x - image_center_x

        # 偏差から角度を計算
        # 画像の幅を基準にして角度を計算
        angle = math.degrees(math.atan2(delta_x, image.shape[1] / 2))

        return angle

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="フロントカメラに関するプログラム")
    parser.add_argument("--camera-num", type=int, default=0, help="カメラIDを指定する")

    args = parser.parse_args()
    camera = CameraInterface()

    image_path = "correction.jpeg"
    folder_path = "confirmation_image"

    # 保存用フォルダの作成
    os.makedirs(folder_path, exist_ok=True)

    # 画像の取得
    camera = CameraInterface(camera_id=args.camera_num)
    camera.start_camera()

    # リアカメラで画像を１枚取得する
    if args.save_path is not None:
        save_path = os.path.join(folder_path, save_path)
    else:
        save_path = os.path.join(folder_path, image_path)

    camera.capture_save_image(save_path)
    
    #補正角度の算出
    angle_corrector = AngleCorrector()
    angle = angle_corrector.calculate_correction_angle(image_path)
    #四捨五入してintに変換
    angle_int = int(round(angle))
    #角度だけを出力（C++側で読み取るため）
    print(f"{angle_int}")
