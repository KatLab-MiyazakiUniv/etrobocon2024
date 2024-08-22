make = make --no-print-directory

help:

	@echo "	フロントカメラで画像を取得する"
	@echo " $$ make image"
	@echo "画像のファイル名を指定してフロントカメラで画像を取得する"
	@echo " $$ make image SAVE_NAME=(画像のファイル名)"
	@echo "取得した画像を一括削除する"
	@echo " $$ make rm-img"

## 画像取得関連 ##
ifeq ($(SAVE_NAME),)
    SAVE_NAME = Fig.jpeg # デフォルト値
endif
image:
	@${make} kill
	sudo python3 front_camera/camera_interface.py --save_path $(SAVE_NAME)
	@echo "$(SAVE_NAME) 画像取得しますた！！！！！！！"

rm-img:
	sudo rm -rf image_data/

kill:
	@ps aux | grep "python -m src --server --server-port 10338" | grep -v "grep" | awk '{print $$2}' | sudo xargs -r kill -9
