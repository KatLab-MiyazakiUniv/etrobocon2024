[![Google Test](https://github.com/KatLab-MiyazakiUniv/etrobocon2024/actions/workflows/google-test.yaml/badge.svg)](https://github.com/KatLab-MiyazakiUniv/etrobocon2024/actions/workflows/google-test.yaml)
[![Build Check](https://github.com/KatLab-MiyazakiUniv/etrobocon2024/actions/workflows/build-check.yaml/badge.svg)](https://github.com/KatLab-MiyazakiUniv/etrobocon2024/actions/workflows/build-check.yaml)

# etrobocon2024

宮崎大学片山徹郎研究室チーム KatLab が作成する[ET ロボコン 2024](https://www.etrobo.jp/)アドバンストクラスの走行システムプログラムです。

## 開発環境

- [ET ロボコン公式シミュレータ](https://github.com/ETrobocon/etrobo)
- [Raspi 用 SPIKE 制御開発環境「RasPike（ラスパイク）」](https://github.com/ETrobocon/RasPike)
- C++
- [GoogleTest](https://github.com/google/googletest)
- Git/GitHub/GitHub Actions

環境構築の詳細は、[wiki](https://github.com/KatLab-MiyazakiUniv/etrobocon2024/wiki)を見てください。

### PlantUML の環境構築

```plantuml
!include ClassDiagram.pu
```

上の図は、ClassDiagram.pu ファイルを描画したものである。
ClassDiagram.pu は、クラス図作成の補助のため、PlantUML を用いて、UML ダイアグラムを作成したファイルである。
以下に、環境構築の手順を記述する。

1. PlantUML をインストールする
   PlantUML をインストールするため、以下のコマンドで必要なパッケージをインストールする。
   Mac 環境では、Homebrew を用いて、以下のコマンドでインストールする。

   ```
   $ brew install adoptopenjdk --cask
   $ brew install graphviz
   $ brew install plantuml
   ```

   また、Mac 環境において、[Times free font](https://www.freebestfonts.com/timr45w-font#google_vignette)のインストールが必要な場合がある現象を確認した。ダウンロードしたフォントを開くと、フォントを追加するボタンが表示されるため、ボタンを押下して追加する。

2. VSCode の拡張機能をインストールする
   .vscode/extensions.json に記述している拡張機能をインストールする。

   - PlantUML
   - Mardown Preview Enhanced

3. .pu ファイルを記述し、プレビュー画面で確認する
   .pu ファイルを作成し、クラス図を作成する。書き方の詳細は、ClassDiagram.pu ファイルを参照。
   また、必要な拡張機能をインストールすることにより、.pu ファイルから画像を確認することができる。
   .pu ファイルを開くと、VSCode のウインドウ左上にある、「カーソル位置のダイアグラムをプレビュー」を押すと、PlantUML プレビューを右に分割して開くことができる。
   開いたプレビューは、.pu ファイルの記述から UML を自動作成した図を表示する。
   変更箇所を保存後、しばらくすると画像を更新し、プレビューに出力する画像に反映する。

4. .pu ファイルを SVG にエクスポートする
   miro に貼り付けるために、.pu ファイルから SVG でエクスポートする。
   なお、png ファイルでは左から始まって一定幅しか写らず、それ以上は切り取られてしまうため、写らない場所ができる可能性がある。プレビュー画面をスクリーンショットで切り取った場合でも、拡大すると解像度が下がり、文字を読めない場合がある。この問題は、劣化が少ない SVG ファイルをエクスポートし、miro に貼り付けることで解決できる。

   エクスポートは、Ctrl + Shift + P (Command + Shift + P) で、「PlantUML: ワークスペース内のダイアグラムをエクスポート (PlantUML: Export in WorkSpace Diagrams)」を選択することで、エクスポートできる。
   次に拡張子を選択(SVG を推奨)すると、ルートディレクトリに out ディレクトリを作成し、その中にさらに .pu ファイルと同名のディレクトリを作成し、1 行目にある @startuml {title} の title にあたるファイル名で SVG を出力する。
   例えば、ClassDiagram.pu に @startuml ETRobocon2024 と書かれている場合は、/out/ClassDiagram/ETRobocon2024.svg を出力する。

## Authors

KatLab メンバー, 宮崎大学片山徹郎研究室

## ビルド方法

ビルドする(開発環境、実機共通)

```

$ cd ~/etrobo/workspace/etrobocon2024
$ make build

```

走行を開始する(実機限定)

```

$ cd ~/etrobo/workspace/etrobocon2024
$ make start

```
