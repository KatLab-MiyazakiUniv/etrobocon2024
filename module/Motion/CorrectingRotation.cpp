/**
 * @file   CorrectingRotation.cpp
 * @brief  プラレール・背景撮影のための角度補正回頭動作
 * @author bizyutyu CHIHAYATAKU takahashitpom
 */

#include "CorrectingRotation.h"
#include <math.h>

using namespace std;

CorrectingRotation::CorrectingRotation(int _pwm, int _correctionTolerance, COLOR _color)
  : pwm(_pwm), correctionTolerance(_correctionTolerance), color(_color) {};

void CorrectingRotation::run()
{
  // 補正角度算出を行う
  // Pytnon側で算出に必要な画像取得から補正角度算出までを行う
  char cmd[512];
  snprintf(cmd, 512,
           "cd etrobocon2024/front_camera && make correction-angle COLOR=\"--color %s\"> "
           "correction_angle.txt && sudo "
           "chmod 644 correction_angle.txt && cd ../..",
           ColorJudge::colorToString(color));
  system(cmd);

  // 一時ファイルから出力を読み取る
  FILE* file = fopen("etrobocon2024/front_camera/correction_angle.txt", "r");
  if(file == NULL) {
    fprintf(stderr, "ファイルを開けませんでした\n");
    return;
  }

  char output[256];
  if(fgets(output, sizeof(output), file) == NULL) {
    fprintf(stderr, "ファイルの読み込みに失敗しました\n");
    fclose(file);
    return;
  }
  fclose(file);

  // 改行文字を削除
  size_t len = strlen(output);
  if(len > 0 && output[len - 1] == '\n') {
    output[len - 1] = '\0';
  }

// 一時ファイルを削除
#ifdef ENABLE_FILE_DELETION
  if(remove("etrobocon2024/front_camera/correction_angle.txt") == EOF) {
    printf("補正角度ファイルの削除に失敗しました\n");
  }
#endif

  // 出力を整数に変換
  int calculationAngle = 0;
  if(sscanf(output, "%d", &calculationAngle) != 1) {
    fprintf(stderr, "角度の変換に失敗しました: %s\n", output);
    return;
  }

  printf("補正角度: %d\n", calculationAngle);

  // calculationAngleの符号に基づいてisClockwiseを設定し、calculationAngleを正の値にする
  isClockwise = (calculationAngle >= 0);
  correctionAngle
      = abs(calculationAngle * 0.5) <= correctionTolerance ? 0 : abs(calculationAngle * 0.5);

  printf("ホゲータ回頭: %d\n", correctionAngle);
  PwmRotation pr(correctionAngle, pwm, isClockwise);
  Sleeping sl(500);

  // 補正のための回頭をする
  pr.run();
  sl.run();
}

int CorrectingRotation::getCorrectionAngle()
{
  if(isClockwise == true) {
    return (correctionAngle);
  } else {
    return (-correctionAngle);
  }
}

void CorrectingRotation::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, LARGE_BUF_SIZE, "Run CorrectingRotation (correctionAngle: %d, pwm: %d, color: %s)",
           correctionAngle, pwm, ColorJudge::colorToString(color));
  logger.log(buf);
}
