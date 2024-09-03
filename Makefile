MAKEFILE_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
HOST = $(shell hostname)
SERVER_URL = サーバーのURL
make = make --no-print-directory

# 使い方
help:
	@echo ビルドする
	@echo " $$ make build"
	@echo ビルドファイルを消してからビルドする
	@echo " $$ make rebuild"
	@echo 無線通信デバイスのサーバーに画像をアップロードする
	@echo " $$ make upload"
	@echo 走行を開始する\(実機限定\)
	@echo " $$ make start"
	@echo 中断したmakeプロセスをkillする
	@echo " $$ make kill"
	@echo ダブルループエリアのコマンドファイルを生成する
	@echo " $$ make double-left-%"
	@echo " $$ make double-right-%"

	@echo 指定ファイルをフォーマットする
	@echo " $$ make format FILES=<ディレクトリ名>/<ファイル名>.cpp"
	@echo すべての変更ファイルをフォーマットする
	@echo " $$ make format"
	@echo フォーマットチェックをする
	@echo " $$ make format-check"
	@echo C++のテストを実行する
	@echo " $$ make gtest"
	@echo C++のソースコードチェックとテストを実行する
	@echo " $$ make c-all-check"
	@echo Pythonのテストを実行する
	@echo " $$ make utest"
	@echo Pythonのソースコードチェックとテストを実行する
	@echo " $$ make py-all-check"
	@echo C++とPythonのソースコードチェックとテストを実行する
	@echo " $$ make all-check"

## 実行関連 ##
build:
# 実機で動かす場合(hostnameがkatlabから始まる場合)
ifeq ($(filter katlab%,$(HOST)), $(HOST))
	cd $(MAKEFILE_PATH)../ && make img=etrobocon2024
# それ以外の環境の場合(開発環境など)
else
	cd $(ETROBO_ROOT) && make app=etrobocon2024
endif

rebuild:
	rm -rf build
	@${make} build

# 無線通信デバイスのサーバーに画像をアップロードする
upload:
	curl -X POST -F "file=@"$(FILE_PATH)"" $(SERVER_URL)/images

# 実機の場合、走行を開始する 
start:
ifeq ($(filter katlab%,$(HOST)), $(HOST))
	cd $(MAKEFILE_PATH)../ && make start
endif

# makeのプロセスIDを抽出し、キルする
kill:
	@ps aux | grep make | grep -v "grep" | awk '{print $$2}' | xargs -r kill -9

# シェルファイルを実行し、ダブルループエリアのコマンドファイルを生成する
double-left-%:
	bash ./scripts/double_loop_left_merger.sh ${@:double-left-%=%}
double-right-%:
	bash ./scripts/double_loop_right_merger.sh ${@:double-right-%=%}


## 開発関連 ##
# ファイルにclang-formatを適用する
format:
# 指定ファイルがある場合、そのファイルにclang-formatを適用する
ifdef FILES
	clang-format -i -style=file $(FILES)
# ない場合、変更されたファイルのうち、cpp、hファイルにclang-formatを適用する
else
	git diff origin/main --name-only | awk '/\.cpp$$|\.h$$/ {print $$1}' | xargs clang-format -i -style=file
endif

format-check:
	find ./test ./module -type f -name "*.cpp" -o -name "*.h" | xargs clang-format --dry-run --Werror *.h *.cpp

# C++のテストを実行する
gtest:
	set -eu
	./test/gtest/gtest_build.sh

# C++のソースコードチェックとテストを実行する
c-all-check:
	@${make} format
	@${make} gtest
	@${make} format-check

# Pythonのテストを実行する
utest:
	cd rear_camera_py && make test

# Pythonのソースコードチェックとテストを実行する
py-all-check:
	cd rear_camera_py && make all-check

# C++とPythonのソースコードチェックとテストを実行する
all-check:
	@${make} format
	cd rear_camera_py && make format
	@${make} gtest
	@${make} utest
	@${make} format-check
	cd rear_camera_py && make format-check

