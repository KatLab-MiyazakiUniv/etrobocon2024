"""mainモジュール.

プロジェクトルートで、以下のコマンドを実行すると最初に呼び出されるファイル
> python -m myproject

必要最低限のコードのみを記述するようにする
@author: bizyutyu
"""
import argparse

from .camera_interface import CameraInterface

parser = argparse.ArgumentParser(description="回頭補正用角度算出プログラム")
parser.add_argument("--camera-num", type=int, default=0,
                    help="カメラID")
parser.add_argument("--debug", action="store_true",
                    help="デバッグを行う場合指定するフラグ")

args = parser.parse_args()

camera = CameraInterface(args.camera_num)
camera.start_camera()
