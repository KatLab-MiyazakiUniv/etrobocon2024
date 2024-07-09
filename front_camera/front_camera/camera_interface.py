"""
フロントカメラから画像を取得する
@author: bizyutyu
"""
import cv2
from picamera2 import Picamera2, MappedArray
import numpy as np

class CameraInterface:
    def __init__(self, camera_index=0):
        self.camera_index = camera_index
        self.cap = cv2.VideoCapture(camera_index)
        self.picam2 = Picamera2()
        self.picam2.configure(self.picam2.create_still_configuration())
        self.picam2.start()

    def capture_image_cv2(self, save_path):
        ret, frame = self.cap.read()
        if ret:
            cv2.imwrite(save_path, frame)
        else:
            raise Exception("Failed to capture image")

    def capture_image_picamera2(self, save_path):
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
    camera = CameraInterface()
    try:
        camera.capture_image_cv2("captured_image_cv2.jpg")
        camera.capture_image_picamera2("captured_image_picamera2.jpg")
        buffer = camera.capture_buffers()
        array = camera.capture_array()
        print("Buffer captured:", buffer)
        print("Array captured:", array)
    finally:
        camera.release()