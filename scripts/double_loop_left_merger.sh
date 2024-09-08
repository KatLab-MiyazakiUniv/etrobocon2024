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
output_file="$directory/DoubleLoopLeft.csv"

# 出力ファイルが既に存在する場合は削除する
if [ -f "$output_file" ]; then
    rm "$output_file"
    echo "DoubleLoopLeft.csvを削除しました。"
fi

# 撮影箇所に応じて連結するファイルを決める
if [ "$1" -le 3 ]; then
    double_loop_first="$parts_directory/DoubleLoopLeftFirst_$number.csv"
    double_loop_middle="$parts_directory/DoubleLoopLeftMiddle.csv"
    double_loop_end="$parts_directory/DoubleLoopLeftEnd.csv"
else
    double_loop_first="$parts_directory/DoubleLoopLeftFirst.csv"
    double_loop_middle="$parts_directory/DoubleLoopLeftMiddle.csv"
    double_loop_end="$parts_directory/DoubleLoopLeftEnd_$number.csv"
fi

# ファイルが存在しない場合はエラーを表示して終了
function check_file_exists() {
    if [ ! -f "$1" ]; then
        echo "エラー: $1 が見つかりません。"
        exit 1
    fi
}

# 3つのファイルが存在するかチェック
check_file_exists "$double_loop_first"
check_file_exists "$double_loop_middle"
check_file_exists "$double_loop_end"

# ファイルを結合する関数
function merge_files() {
    cat "$1" >> "$output_file"
    echo >> "$output_file"
}

# ファイルを結合する
merge_files "$double_loop_first"
merge_files "$double_loop_middle"
merge_files "$double_loop_end"

echo "CSVファイルが結合されました。"
