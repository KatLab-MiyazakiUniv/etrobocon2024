/**
 * @file   CameraAction.cpp
 * @brief  カメラ撮影動作
 * @author bizyutyu takahashitom keiya121
 */

#include "CameraAction.h"

using namespace std;

// countShootFigureの初期化
int CameraAction::countShootFigure = 0;

CameraAction::CameraAction(Subject _subject) : subject(_subject) {};

void CameraAction::run()
{
  // フロントカメラで画像を取得する
  // 画像のファイル名と撮影コマンドを指定
  char imageName[20];         // 画像のファイル名
  char makeImageCommand[20];  // 撮影に用いるmakeコマンド名
  char cmd[256];              // 実行コマンドを格納する
  if(subject == CameraAction::Subject::FIGURE) {
    countShootFigure++;
    sprintf(imageName, "Fig_%d.jpeg", countShootFigure);
    sprintf(makeImageCommand, "image");
    snprintf(cmd, 256, "cd etrobocon2024/front_camera && make %s SAVE_NAME=%s && cd ../..",
             makeImageCommand, imageName);
  } else if(subject == CameraAction::Subject::PLARAIL) {
    sprintf(imageName, "Pla.jpeg");
    sprintf(makeImageCommand, "record");
    snprintf(cmd, 256, "cd etrobocon2024/front_camera && make %s && cd ../..", makeImageCommand);
  }

  system(cmd);
  printf("%s\n", cmd);

  // Fig_1の場合、物体検出を行うエンドポイントに画像をアップロードする
  // それ以外の場合、画像をアップロードする処理をバックグラウンドで行う
  // 実行コマンドの最後に「&」をつけることでバックグラウンドで実行する
  // 参考：https://qiita.com/inosy22/items/341cfc589494b8211844
  char uploadImageName[20] = "Fig_1.jpeg";
  if(subject == CameraAction::Subject::FIGURE && strcmp(imageName, uploadImageName) == 0) {
    snprintf(cmd, 256,
             "cd etrobocon2024 && make upload-detect FILE_PATH=front_camera/image_data/%s && cd ..",
             imageName);
    system(cmd);
    printf("%s\n", cmd);
  } else if(subject == CameraAction::Subject::FIGURE) {
    snprintf(
        cmd, 256,
        "(cd etrobocon2024 && make upload-image FILE_PATH=front_camera/image_data/%s && cd ..) &",
        imageName);
    system(cmd);
    printf("%s\n", cmd);
  }

  // PLARAILが指定された場合には、画像の切り出し処理を行い無線通信デバイスに送信する処理をバックグラウンドで行う
  if(subject == CameraAction::Subject::PLARAIL) {
    sprintf(makeImageCommand, "plarail-image");
    snprintf(cmd, 256,
             "(cd etrobocon2024/front_camera && make %s && cd ../.. &&"
             "cd etrobocon2024 && make upload-image FILE_PATH=front_camera/image_data/%s && cd .. "
             ") &",
             makeImageCommand, imageName);
    system(cmd);
    printf("%s\n", cmd);
  }
}

void CameraAction::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, LARGE_BUF_SIZE, "Run CameraAction ()");
  logger.log(buf);
}