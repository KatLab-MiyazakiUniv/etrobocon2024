make = make --no-print-directory

help:

	@echo "	フロントカメラで画像を取得する"
	@echo " $$ make image"
	@echo "画像のファイル名を指定してフロントカメラで画像を取得する"
	@echo " $$ make image SAVE_NAME=(画像のファイル名)"
	@echo "取得した画像を一括削除する"
	@echo " $$ make rm-img"

	@echo "テストを実行する"
	@echo " $$ make test"
	@echo "フォーマットを実行する"
	@echo " $$ make format"
	@echo "フォーマットとチェックを実行する"
	@echo " $$ make format-check"
	@echo "テストとフォーマットチェックを同時に実行する"
	@echo " $$ make all-check"
	@echo "デバッグを実行する"
	@echo " $$ make debug"
	@echo "デバッグフォルダを削除する"
	@echo " $$ make clean"
	@echo "ライブラリをinstallする"
	@echo " $$ make create-env-rear"

## 画像取得関連 ##
ifeq ($(SAVE_NAME),)
    SAVE_NAME = FigA_1.png # デフォルト値
endif
image:
	@${make} kill
	sudo python3 front_camera/camera_interface.py --save_path $(SAVE_NAME)
	@echo "$(SAVE_NAME) 画像取得！！！！！！！"

kill:
	@ps aux | grep "python -m src --server --server-port 10338" | grep -v "grep" | awk '{print $$2}' | sudo xargs -r kill -9


rm-img:
	sudo rm -rf image_data/

## 開発時コマンド ##
test:
	python -m unittest

format:
	autopep8 --in-place --recursive front_camera/ tests/
	python -m autopep8 -i -r front_camera/ tests/

format-check:
	@${make} format
	python -m pycodestyle front_camera/ tests/
	python -m pydocstyle front_camera/ tests/

all-check:
	@${make} test
	@${make} format-check

debug:
	python -m src --debug

clean:
	rm -rf ./debug
	
create-env-rear:	
	pip install -r ../requirements.txt
