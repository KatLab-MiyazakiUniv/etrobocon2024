/**
 * @file   LineTracing.h
 * @brief  ライントレース動作
 * @author CHIHAYATAKU
 */

#ifndef LINE_TRACING_H
#define LINE_TRACING_H

#include "SpeedCalculator.h"
#include "Motion.h"
#include "Mileage.h"
#include "Timer.h"
#include "Pid.h"
#include "ColorJudge.h"

class LineTracing : public Motion {
 public:
  /**
   * コンストラクタ（引数が4つの場合）
   * @param _targetSpeed 目標速度 0~
   * @param _targetBrightness 目標輝度 0~
   * @param _pidGain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  LineTracing(double _targetSpeed, int _targetBrightness, const PidGain& _pidGain,
              bool& _isLeftEdge);

  /**
   * コンストラクタ（引数が5つの場合）
   * @param _targetSpeed 目標速度 0~
   * @param _targetBrightness 目標輝度 0~
   * @param _pidGain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   * @param _isRecoveryEnabled 復帰動作を行うかの判定(true:行う, false:行わない)
   */
  LineTracing(double _targetSpeed, int _targetBrightness, const PidGain& _pidGain,
              bool& _isLeftEdge, bool _isRecoveryEnabled);

  /**
   * @brief ライントレースする
   */
  void run();

 protected:
  /**
   * @brief ライントレースする際の事前条件判定をする
   * @param targetSpeed 目標速度
   * @note オーバーライド必須
   */
  virtual bool isMetPreCondition(double targetSpeed) = 0;

  /**
   * @brief ライントレースする際の継続条件判定をする　返り値がfalseでモーターが止まる
   * @note オーバーライド必須
   */
  virtual bool isMetContinuationCondition() = 0;

  /**
   * @brief 実行のログを取る
   */
  virtual void logRunning();

  /**
   * @brief 走行体がコースを外れたときに復帰動作をする
   */
  void recover();

  /**
   * @brief 走行体がコースを脱線しているかを判定をする　返り値がtrueで復帰動作開始
   */
  bool isErrorState();

  /**
   * @brief 復帰動作実行のログを取る
   */
  void logRunningRecovering();

  /**
   * @brief 復帰動作終了のログを取る
   */
  void logFinishingRecovering();

 protected:
  double targetSpeed;    // 目標速度 0~
  int targetBrightness;  // 目標輝度 0~
  PidGain pidGain;       // PIDゲイン

  bool& isLeftEdge;         // エッジの左右判定(true:左エッジ, false:右エッジ)
  bool isRecoveryEnabled;   // 復帰動作を行うかの判定(true:行う, false:行わない)
  double initLeftMileage;   // クラス呼び出し時の左車輪の走行距離
  double initRightMileage;  // クラス呼び出し時の右車輪の走行距離
  double initDistance;      // 実行前の走行距離
  Timer timer;
  Measurer measurer;
  Controller controller;
  SpeedCalculator* speedCalculator;

  static constexpr int ERROR_JUDGE_COUNT = 10;  // コース脱線判定に用いる目標色の連続取得回数の定義
  int errorColorCount = 0;  // コース脱線判定に用いる目標色の連続取得回数を記録するための変数
  COLOR targetColorForError = COLOR::GREEN;  // コース脱線判定のための目標色

  // 復帰動作コマンドファイルベースパス
  const char* basePath = "etrobocon2024/datafiles/";

  // 復帰動作コマンドファイル名
  const char* commandFileName = "Recovery";
};

#endif