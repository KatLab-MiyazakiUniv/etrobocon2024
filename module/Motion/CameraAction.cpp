/**
 * @file   CameraAction.cpp
 * @brief  カメラ撮影動作
 * @author bizyutyu takahashitom
 */

#include "CameraAction.h"

using namespace std;

// countShootFigureの初期化
int CameraAction::countShootFigure = 0;

CameraAction::CameraAction(Subject _subject) : subject(_subject){};

void CameraAction::run()
{
  // フロントカメラで画像を取得する
  // 画像のファイル名と撮影コマンドを指定
  char imageName[20];         // 画像のファイル名
  char makeImageCommand[20];  // 撮影に用いるmakeコマンド名
  char cmd[256];              // 撮影に際してディレクトリ移動も行う
  if(subject == CameraAction::Subject::FIGURE) {
    countShootFigure++;
    sprintf(imageName, "Fig_%d.jpeg", countShootFigure);
    sprintf(makeImageCommand, "image");
    snprintf(cmd, 256, "cd etrobocon2024/front_camera && make %s SAVE_NAME=%s && cd ../..",
             makeImageCommand, imageName);
  } else if(subject == CameraAction::Subject::PLARAIL) {
    sprintf(imageName, "Pla.jpeg");
    sprintf(makeImageCommand, "plarail-image");
    snprintf(cmd, 256, "cd etrobocon2024/front_camera && make %s && cd ../..", makeImageCommand);
  }

  system(cmd);
  printf("%s\n", cmd);

  // Fig_1の場合、物体検出を行うエンドポイントに画像をアップロードする
  char uploadImageName[20] = "Fig_1.jpeg";
  if(strcmp(imageName, uploadImageName) == 0) {
    snprintf(cmd, 256,
             "cd etrobocon2024 && make upload-detect FILE_PATH=front_camera/image_data/%s && cd ..",
             imageName);
    system(cmd);
    printf("%s\n", cmd);
  } else {
    snprintf(cmd, 256,
             "cd etrobocon2024 && make upload FILE_PATH=front_camera/image_data/%s && cd ..",
             imageName);
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