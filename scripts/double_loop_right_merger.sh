#!/bin/bash

# 引数から結合する番号を取得
number="$1"

# 引数がない場合はエラーを表示して終了
if [ -z "$number" ]; then
    echo "エラー: 結合する番号を引数として指定してください。"
    exit 1
fi

# 引数が0から5の範囲外の場合もエラーを表示して終了
if ! [[ "$number" =~ ^[0-5]$ ]]; then
    echo "エラー: 0から5までの番号を引数として指定してください。"
    exit 1
fi

# データファイルを生成するディレクトリパス
directory="./datafiles"

# データファイルのパーツがあるディレクトリパス
parts_directory="./datafiles/datafile_parts"

# 出力ファイル名
output_file="$directory/DoubleLoopRight.csv"

# 出力ファイルが既に存在する場合は削除する
if [ -f "$output_file" ]; then
    rm "$output_file"
    echo "DoubleLoopRight.csvを削除しました。"
fi

# ファイルが存在しない場合はエラーを表示して終了
function check_file_exists() {
    if [ ! -f "$1" ]; then
        echo "エラー: $1 が見つかりません。"
        exit 1
    fi
}

# 3つのファイルが存在するかチェック
check_file_exists "$parts_directory/DoubleLoopRightFirst.csv"
check_file_exists "$parts_directory/DoubleLoopRightMiddle_$number.csv"
check_file_exists "$parts_directory/DoubleLoopRightEnd.csv"

# ファイルを結合する関数
function merge_files() {
    if [ "$1" -le 3 ]; then
        cat "$1" >> "$output_file"
        echo >> "$output_file"
    else
        cat "$1" >> "$output_file"
        echo >> "$output_file"
    fi
}

# ファイルを結合する
merge_files "$parts_directory/DoubleLoopRightAreaBFirst_$number.csv"
merge_files "$parts_directory/DoubleLoopRightAreaA.csv"
merge_files "$parts_directory/DoubleLoopRightAreaBEnd_$number.csv"

echo "CSVファイルが結合されました。"
