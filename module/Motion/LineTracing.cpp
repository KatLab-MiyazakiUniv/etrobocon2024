/**
 * @file   LineTracing.cpp
 * @brief  ライントレース動作の中間クラス
 * @author CHIHAYATAKU
 */

#include "MotionParser.h"
#include "LineTracing.h"

using namespace std;

LineTracing::LineTracing(double _targetSpeed, int _targetBrightness, const PidGain& _pidGain,
                         bool& _isLeftEdge)
  : targetSpeed(_targetSpeed),
    targetBrightness(_targetBrightness),
    pidGain(_pidGain),
    isLeftEdge(_isLeftEdge)
{
  isRecoveryEnabled = true;
}

LineTracing::LineTracing(double _targetSpeed, int _targetBrightness, const PidGain& _pidGain,
                         bool& _isLeftEdge, bool _isRecoveryEnabled)
  : targetSpeed(_targetSpeed),
    targetBrightness(_targetBrightness),
    pidGain(_pidGain),
    isLeftEdge(_isLeftEdge),
    isRecoveryEnabled(_isRecoveryEnabled)
{
}

void LineTracing::run()
{
  Pid pid(pidGain.kp, pidGain.ki, pidGain.kd, targetBrightness);

  // 初期値を代入
  initDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());

  // 事前条件を判定する
  if(!isMetPreCondition(targetSpeed)) {
    return;
  }

  // 左右で符号を変える
  int edgeSign = isLeftEdge ? -1 : 1;

  // 呼び出し時の走行距離
  initLeftMileage = Mileage::calculateWheelMileage(measurer.getLeftCount());
  initRightMileage = Mileage::calculateWheelMileage(measurer.getRightCount());

  speedCalculator = new SpeedCalculator(targetSpeed);

  // 継続条件を満たしている間ループ
  while(isMetContinuationCondition()) {
    // 初期pwm値を計算
    double baseRightPwm = speedCalculator->calculateRightMotorPwmFromTargetSpeed();
    double baseLeftPwm = speedCalculator->calculateLeftMotorPwmFromTargetSpeed();

    // PIDで旋回値を計算
    double turningPwm = pid.calculatePid(measurer.getBrightness()) * edgeSign;

    // モータのPWM値をセット（前進の時0を下回らないように，後進の時0を上回らないようにセット）
    double rightPwm = baseRightPwm > 0.0 ? max(baseRightPwm - turningPwm, 0.0)
                                         : min(baseRightPwm + turningPwm, 0.0);
    double leftPwm = baseLeftPwm > 0.0 ? max(baseLeftPwm + turningPwm, 0.0)
                                       : min(baseLeftPwm - turningPwm, 0.0);
    controller.setRightMotorPwm(rightPwm);
    controller.setLeftMotorPwm(leftPwm);
    // 10ミリ秒待機
    timer.sleep(10);
    if(isRecoveryEnabled && isErrorState()) {
      recover();
      // 再インスタンス化
      delete speedCalculator;                              // 既存のインスタンスを解放
      speedCalculator = new SpeedCalculator(targetSpeed);  // 新しいインスタンスを生成
    }
  }
  delete speedCalculator;  // 既存のインスタンスを解放

  // モータの停止
  controller.stopWheelsMotor();
  timer.sleep(10);
}

void LineTracing::recover()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;
  double diffLeftMileage
      = Mileage::calculateWheelMileage(measurer.getLeftCount()) - initLeftMileage;
  double diffRightMileage
      = Mileage::calculateWheelMileage(measurer.getRightCount()) - initRightMileage;

  // ファイルから受け取る動作リスト
  vector<Motion*> motionList;

  // コマンドファイルパスを作成する
  char commandFilePath[SMALL_BUF_SIZE];
  snprintf(commandFilePath, SMALL_BUF_SIZE, "%s%s.csv", basePath, commandFileName);

  // 動作インスタンスのリストを生成する
  motionList = MotionParser::createMotions(commandFilePath, targetBrightness, isLeftEdge);

  // 動作実行のメッセージログを出す
  snprintf(buf, SMALL_BUF_SIZE, "\nRun the commands in '%s'\n", commandFilePath);
  logger.logHighlight(buf);

  logRunningRecovering();
  // 各動作を実行する
  for(auto motion = motionList.begin(); motion != motionList.end();) {
    (*motion)->logRunning();
    (*motion)->run();
    delete *motion;                     // メモリを解放
    motion = motionList.erase(motion);  // リストから削除
  }

    // 復帰動作コマンド実行後の角度補正
  int endTargetAngle = fabs((diffLeftMileage - diffRightMileage) / TREAD * 180 / M_PI)/1.4;  // 緑に入った角度によって回転角を変更
  int pwmForRotation = 70;
  bool isClockwise;
  if(diffLeftMileage <= diffRightMileage) {
    isClockwise = true;
  } else {
    isClockwise = false;
  }
  // 黒線に到達した後の処理
  PwmRotation endPwmRotation(endTargetAngle, pwmForRotation, isClockwise);
  controller.stopWheelsMotor();
  timer.sleep(200);
  endPwmRotation.run();

  COLOR endTargetColor = COLOR::BLACK; 
  int endTargetSpeed = 200;
  int endTargetBrightness = 15;
  PidGain endPidGain(0.6,0.24,0.1);
  bool endIsRecoveryEnabled = false;
  ColorLineTracing endColorLineTracing(endTargetColor, endTargetSpeed, endTargetBrightness, endPidGain, isLeftEdge, endIsRecoveryEnabled);
  endColorLineTracing.run();

  int endTargetDistance = 200; 
  DistanceLineTracing endDistanceLineTracing(endTargetDistance, endTargetSpeed, endTargetBrightness, endPidGain, isLeftEdge, endIsRecoveryEnabled);
  endDistanceLineTracing.run();

  // モータの停止
  controller.stopWheelsMotor();
  timer.sleep(10);
  logFinishingRecovering();
}

bool LineTracing::isErrorState()
{
  if(ColorJudge::getColor(measurer.getRawColor()) == targetColorForError) {
    errorColorCount++;
  } else {
    errorColorCount = 0;
  }
  if(errorColorCount < ERROR_JUDGE_COUNT) return false;
  // 指定された色をJUDGE_COUNT回連続で取得したときモータが止まる
  errorColorCount = 0;
  return true;
}

void LineTracing::logRunningRecovering()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, LARGE_BUF_SIZE, "Running Recovering");
  logger.log(buf);
}

void LineTracing::logFinishingRecovering()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, LARGE_BUF_SIZE, "Finishing Recovering");
  logger.log(buf);
}

void LineTracing::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* strWhetherIsLeftEdge = isLeftEdge ? "true" : "false";

  // targetValueと%~のオーバーライド必須
  snprintf(buf, LARGE_BUF_SIZE,
           "Run \"targetValue\" LineTracing (\"targetValue\": , targetSpeed: %.2f, "
           "targetBrightness: %d, Gain: (%.2f,%.2f,%.2f), isLeftEdge: %s)",
           targetSpeed, targetBrightness, pidGain.kp, pidGain.ki, pidGain.kd, strWhetherIsLeftEdge);
  logger.log(buf);
}