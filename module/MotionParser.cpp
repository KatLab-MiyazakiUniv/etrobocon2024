/**
 * @file   MotionParser.cpp
 * @brief  動作コマンドファイルを解析するクラス
 * @author keiya121 bizyutyu CHIHAYATAKU
 */

#include "MotionParser.h"

using namespace std;

vector<Motion*> MotionParser::createMotions(const char* commandFilePath, int targetBrightness,
                                            bool& isLeftEdge)
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;
  int lineNum = 1;  // Warning用の行番号

  vector<Motion*> motionList;  // 動作インスタンスのリスト

  // ファイル読み込み
  FILE* fp = fopen(commandFilePath, "r");
  // ファイル読み込み失敗
  if(fp == NULL) {
    snprintf(buf, LARGE_BUF_SIZE, "%s file not open!\n", commandFilePath);
    logger.logWarning(buf);
    return motionList;
  }

  char row[READ_BUF_SIZE];      // 各行の文字を一時的に保持する領域
  const char* separator = ",";  // 区切り文字

  // 行ごとにパラメータを読み込む
  while(fgets(row, READ_BUF_SIZE, fp) != NULL) {
    vector<char*> params;
    // separatorを区切り文字にしてrowを分解し，paramに代入する
    char* param = strtok(row, separator);
    while(param != NULL) {
      // paramをパラメータとして保持する
      params.push_back(param);
      // 次のパラメータをparamに代入する
      // strtok()は第1引数にNULLを与えると、前回の続きのアドレスから処理が開始される
      param = strtok(NULL, separator);
    }

    // 取得したパラメータから動作インスタンスを生成する
    COMMAND command = convertCommand(params[0]);  // 行の最初のパラメータをCOMMAND型に変換

    if(command == COMMAND::PR) {                          // PWM指定回頭動作の生成
      PwmRotation* pr = new PwmRotation(atoi(params[1]),  // 目標角度
                                        atoi(params[2]),  // 目標PWM
                                        convertBool(params[0], params[3]));  // 回頭方向
      motionList.push_back(pr);                                              // 動作リストに追加
    } else if(command == COMMAND::DL) {  // 指定距離ライントレース動作の生成
      DistanceLineTracing* dl = new DistanceLineTracing(
          atof(params[1]),                                             // 目標距離
          atof(params[2]),                                             // 目標速度
          targetBrightness + atoi(params[3]),                          // 目標輝度 + 調整
          PidGain(atof(params[4]), atof(params[5]), atof(params[6])),  // PIDゲイン
          isLeftEdge);                                                 // エッジ

      motionList.push_back(dl);          // 動作リストに追加
    } else if(command == COMMAND::CL) {  // 指定色ライントレース動作の生成
      ColorLineTracing* cl = new ColorLineTracing(
          ColorJudge::stringToColor(params[1]),                        // 目標色
          atof(params[2]),                                             // 目標速度
          targetBrightness + atoi(params[3]),                          // 目標輝度 + 調整
          PidGain(atof(params[4]), atof(params[5]), atof(params[6])),  // PIDゲイン
          isLeftEdge);                                                 // エッジ
      motionList.push_back(cl);                                        // 動作リストに追加
    } else if(command == COMMAND::CD) {  // 色距離指定ライントレース動作の生成
      ColorDistanceLineTracing* cd = new ColorDistanceLineTracing(
          ColorJudge::stringToColor(params[1]),                        // 目標色
          atof(params[2]),                                             // 目標距離
          atof(params[3]),                                             // 目標速度
          targetBrightness + atoi(params[4]),                          // 目標輝度 + 調整
          PidGain(atof(params[5]), atof(params[6]), atof(params[7])),  // PIDゲイン
          isLeftEdge);                                                 // エッジ
      motionList.push_back(cd);                                        // 動作リストに追加
    } else if(command == COMMAND::DS) {                                // 指定距離直進動作の生成
      DistanceStraight* ds = new DistanceStraight(atof(params[1]),     // 目標距離
                                                  atof(params[2]));    // 目標速度

      motionList.push_back(ds);          // 動作リストに追加
    } else if(command == COMMAND::CS) {  // 指定色直進動作の生成
      ColorStraight* cs = new ColorStraight(ColorJudge::stringToColor(params[1]),  // 目標色
                                            atof(params[2]));                      // 目標速度

      motionList.push_back(cs);                        // 動作リストに追加
    } else if(command == COMMAND::EC) {                // エッジ切り替えの生成
      EdgeChanging* ec = new EdgeChanging(isLeftEdge,  // エッジ
                                          convertBool(params[0], params[1]));  // 切り替え後のエッジ

      motionList.push_back(ec);  // 動作リストに追加
    }

    else if(command == COMMAND::SL) {                // 自タスクスリープの生成
      Sleeping* sl = new Sleeping(atoi(params[1]));  // スリープ時間(ミリ秒)

      motionList.push_back(sl);  // 動作リストに追加
    }

    else if(command == COMMAND::RM) {  // 両輪モーターリセット&停止の生成
      // モーターのリセット
      ResetWheelsMotorPwm* rm = new ResetWheelsMotorPwm();  // モーターのリセット

      motionList.push_back(rm);  // 動作リストに追加
    }

    else if(command == COMMAND::SM) {               // 両輪モーター停止の生成
      StopWheelsMotor* sm = new StopWheelsMotor();  // モーターの停止

      motionList.push_back(sm);          // 動作リストに追加
    } else if(command == COMMAND::CA) {  // カメラ撮影動作の生成
      CameraAction* ca = new CameraAction(
          convertSubject(params[1]));  // フラグ確認を行うかの判断に用いる撮影対象

      motionList.push_back(ca);          // 動作リストに追加
    } else if(command == COMMAND::AC) {  // 配置エリアAでのミニフィグ撮影動作の生成
      AreaACameraAction* ac = new AreaACameraAction(
          atoi(params[1]),                    // 撮影位置(0~3)
          convertBool(params[0], params[2]),  // フロントカメラをミニフィグに向けるための回頭方向
          atoi(params[3]),                    // 撮影のための回頭角度
          atoi(params[4]),                    // 黒線復帰のための回頭角度
          atoi(params[5]),                    // 回頭時のPWM
          atof(params[6]),                    // 前進、後退の距離
          atof(params[7]));                   // 前進、後退の速度

      motionList.push_back(ac);          // 動作リストに追加
    } else if(command == COMMAND::XR) {  // 角度補正回頭動作の生成
      CorrectingRotation* xr
          = new CorrectingRotation(atoi(params[1]),                        // 目標PWM
                                   atoi(params[2]),                        // 補正許容角度
                                   ColorJudge::stringToColor(params[3]));  // 補正対象の色

      motionList.push_back(xr);          // 動作リストに追加
    } else if(command == COMMAND::BC) {  // 配置エリアB撮影動作の生成
      AreaBCameraAction* bc
          = new AreaBCameraAction(atoi(params[1]),  // 1回目の回頭目標回転角度(deg)
                                  atoi(params[2]),  // 1回目の回頭PWM値
                                  convertBool(params[0], params[3]),  // 1回目の回頭方向
                                  atoi(params[4]),                    // 角度補正回頭用のPWM値
                                  atoi(params[5]),                    // 2回目の回頭目標回転角度
                                  atoi(params[6])                     // 2回目の回頭PWM値
          );

      motionList.push_back(bc);  // 動作リストに追加
    }
    // TODO: 後で作成する

    //    }else if(command == COMMAND::DT) {  // 距離指定旋回動作の生成
    //     DistanceTurning* dt = new DistanceTurning(atof(params[1]),   // 目標距離
    //                                               atoi(params[2]),   // 左モータのPWM値
    //                                               atoi(params[3]));  // 右モータのPWM値

    //     motionList.push_back(dt);                                    // 動作リストに追加
    //   } else if(command == COMMAND::AU) {  // アームを上げる
    //     ArmUpping* au = new ArmUpping(atoi(params[1]), atoi(params[2]));

    //     motionList.push_back(au);          // 動作リストに追加
    //   } else if(command == COMMAND::AD) {  // アームを下げる
    //     ArmDownning* ad = new ArmDownnig(atoi(params[1]), atoi(params[2]));

    //     motionList.push_back(ad);          // 動作リストに追加
    //   }
    else {  // 未定義のコマンドの場合
      snprintf(buf, LARGE_BUF_SIZE, "%s:%d: '%s' is undefined command", commandFilePath, lineNum,
               params[0]);
      logger.logWarning(buf);
    }
    lineNum++;  // 行番号をインクリメントする
  }

  // ファイルを閉じる
  fclose(fp);

  return motionList;
}

COMMAND MotionParser::convertCommand(char* str)
{
  if(strcmp(str, "DL") == 0) {  // 文字列がDLの場合
    return COMMAND::DL;
  } else if(strcmp(str, "CL") == 0) {  // 文字列がCLの場合
    return COMMAND::CL;
  } else if(strcmp(str, "DS") == 0) {  // 文字列がDSの場合
    return COMMAND::DS;
  } else if(strcmp(str, "CD") == 0) {  // 文字列がCDの場合
    return COMMAND::CD;
  } else if(strcmp(str, "CS") == 0) {  // 文字列がCSの場合
    return COMMAND::CS;
  } else if(strcmp(str, "PR") == 0) {  // 文字列がPRの場合
    return COMMAND::PR;
  } else if(strcmp(str, "DT") == 0) {  // 文字列がDTの場合
    return COMMAND::DT;
  } else if(strcmp(str, "EC") == 0) {  // 文字列がECの場合
    return COMMAND::EC;
  } else if(strcmp(str, "SL") == 0) {  // 文字列がSLの場合
    return COMMAND::SL;
  } else if(strcmp(str, "AU") == 0) {  // 文字列がAUの場合
    return COMMAND::AU;
  } else if(strcmp(str, "AD") == 0) {  // 文字列がADの場合
    return COMMAND::AD;
  } else if(strcmp(str, "XR") == 0) {  // 文字列がXRの場合
    return COMMAND::XR;
  } else if(strcmp(str, "RM") == 0) {  // 文字列がRMの場合
    return COMMAND::RM;
  } else if(strcmp(str, "SM") == 0) {  // 文字列がSMの場合
    return COMMAND::SM;
  } else if(strcmp(str, "CA") == 0) {  // 文字列がCAの場合
    return COMMAND::CA;
  } else if(strcmp(str, "AC") == 0) {  // 文字列がACの場合
    return COMMAND::AC;
  } else if(strcmp(str, "BC") == 0) {  // 文字列がBCの場合
    return COMMAND::BC;
  } else {  // 想定していない文字列が来た場合
    return COMMAND::NONE;
  }
}

bool MotionParser::convertBool(char* command, char* stringParameter)
{
  Logger logger;

  // 末尾の改行を削除
  char* param = StringOperator::removeEOL(stringParameter);

  if((strcmp(command, "PR") == 0) || (strcmp(command, "AC") == 0)
     || (strcmp(command, "BC") == 0)) {    //  コマンドがPR・AC・BCのいずれかの場合
    if(strcmp(param, "clockwise") == 0) {  // パラメータがclockwiseの場合
      return true;
    } else if(strcmp(param, "anticlockwise") == 0) {  // パラメータがanticlockwiseの場合
      return false;
    } else {  // 想定していないパラメータが来た場合
      logger.logWarning("Parameter before conversion must be 'clockwise' or 'anticlockwise'");
      return true;
    }
  }

  if(strcmp(command, "EC") == 0) {    //  コマンドがECの場合
    if(strcmp(param, "left") == 0) {  // パラメータがleftの場合
      return true;
    } else if(strcmp(param, "right") == 0) {  // パラメータがrightの場合
      return false;
    } else {  // 想定していないパラメータが来た場合
      logger.logWarning("Parameter before conversion must be 'left' or 'right'");
      return true;
    }
  }
}

CameraAction::Subject MotionParser::convertSubject(char* stringParameter)
{
  Logger logger;

  // 末尾の改行を削除
  char* param = StringOperator::removeEOL(stringParameter);

  if(strcmp(param, "FIG") == 0) {  // パラメータがFIGの場合
    return CameraAction::Subject::FIGURE;
  } else if(strcmp(param, "PLA") == 0) {  // パラメータがPLAの場合
    return CameraAction::Subject::PLARAIL;
  } else {  // 想定していないパラメータが来た場合
    logger.logWarning("Parameter before conversion must be 'FIG' or 'PLA'");
    return CameraAction::Subject::UNDEFINED;
  }
}
