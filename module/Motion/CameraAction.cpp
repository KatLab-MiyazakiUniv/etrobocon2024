/**
 * @file   CameraAction.cpp
 * @brief  カメラ撮影動作
 * @author bizyutyu
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
  char makeImageCommand[10];  // 撮影に用いるmakeコマンド名
  if(subject == CameraAction::Subject::FIGURE) {
    countShootFigure++;
    sprintf(imageName, "Fig_%d.jpeg", countShootFigure);
    sprintf(makeImageCommand, "image");
  } else if(subject == CameraAction::Subject::PLARAIL) {
    sprintf(imageName, "Pla.jpeg");
    sprintf(makeImageCommand, "image");
  }

  // 撮影に際してディレクトリ移動も行う
  char cmd[256];
  snprintf(cmd, 256, "cd etrobocon2024/front_camera && make %s SAVE_NAME=%s && cd ../..",
           makeImageCommand, imageName);
  system(cmd);
  printf("%s\n", cmd);

  // 画像アップロードに際してディレクトリ移動も行う
  char uploadImageName[20] = "Fig_1.jpeg";  // アップロードするミニフィグの画像を指定
  if(strcmp(imageName, uploadImageName) == 0 || strcmp(imageName, "Pla.jpeg") == 0) {
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