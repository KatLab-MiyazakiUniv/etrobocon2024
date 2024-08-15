/**
 * @file   CameraAction.h
 * @brief  カメラ撮影動作
 * @author bizyutyu
 */

#ifndef CAMERAACTION_H
#define CAMERAACTION_H

#include "CompositeMotion.h"

class CameraAction : public CompositeMotion {
 public:
  /**
   * 撮影対象判別の為の型
   * @param subject FIGURE:ミニフィグ PLARAIL:プラレール・背景
   */
  enum class Subject { FIGURE, PLARAIL, UNDEFINED };

  /**
   * コンストラクタ
   * @param _subject 撮影対象　FIGURE:ミニフィグ PLARAIL:プラレール・背景
   */
  CameraAction(Subject _subject);

  /**
   * @brief 撮影動作を行う
   */
  void run() override;

  /**
   * @brief 実行のログを取る
   */
  void logRunning() override;

 private:
  Subject subject;  // 撮影対象(FIGURE:ミニフィグ, PLARAIL:プラレール・背景)
  static int countShootFigure;  // ミニフィグの撮影回数をカウント
};
#endif