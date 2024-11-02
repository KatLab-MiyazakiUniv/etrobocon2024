"""
指定画像中の補正対象の色の矩形が中心に来るような補正角度を返す
@author: bizyutyu YKhm20020 keiya121 CHIHAYATAKU
"""

import argparse
import os
import cv2
import math
from camera_interface import CameraInterface
from color_rectangle_detector import ColorRectangleDetector

class GetCorrectionAngle:
    def __init__(self, color):
        """コンストラクタ
        Args:
            color (str): 補正対象の色
        """

        self.rectangle_detector = ColorRectangleDetector(color)

    def calculate_correction_angle(self, image_path):
        """補正角度を算出する

        Args:
            image_path (str): 画像の保存先パス(拡張子込み)

        Raises:
            ValueError: 画像読み込みができない
            ValueError: 対象色の矩形を検出できない

        Returns:
            int: 補正角度
        """

        # 画像を読み込む
        image = cv2.imread(image_path)
        if image is None:
            raise ValueError(f"画像を読み込めませんでした: {image_path}")

        # 画像の中心を計算
        image_center_x = image.shape[1] // 2
        # image_center_y = image.shape[0] // 2

        # 対象色の長方形を検出
        target_color_rect = self.rectangle_detector.detect_rectangle(image)
        if target_color_rect is None:
            raise ValueError(f"{self.rectangle_detector.color}色の長方形が検出されませんでした")

        # 対象色の長方形の中心のx座標を計算
        rect_center_x = target_color_rect[0] + target_color_rect[2] // 2

        # x軸方向の偏差を計算
        delta_x = rect_center_x - image_center_x

        # 偏差から角度を計算
        # 画像の幅を基準にして角度を計算
        angle = math.degrees(math.atan2(delta_x, image.shape[1] / 2))

        return angle

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="フロントカメラに関するプログラム")
    parser.add_argument("--camera-num", type=int, default=0, help="カメラIDを指定する")
    parser.add_argument("--color", type=str, default="yellow", help="検出する矩形の色を指定する")

    args = parser.parse_args()
    camera = CameraInterface()

    image_path = "correction.jpeg"
    folder_path = "confirmation_image"

    # 保存用フォルダの作成
    os.makedirs(folder_path, exist_ok=True)

    # 画像の取得
    camera = CameraInterface(camera_id=args.camera_num)
    camera.start_camera()

    save_path = os.path.join(folder_path, image_path)

    # フロントカメラで画像を１枚取得する
    camera.capture_save_image(save_path)

    #補正角度の算出
    angle_corrector = GetCorrectionAngle(args.color)
    angle = angle_corrector.calculate_correction_angle(save_path)
    #四捨五入してintに変換
    angle_int = int(round(angle))
    #角度だけを出力（C++側で読み取るため）
    print(angle_int)
