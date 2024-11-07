/**
 * @file AreaMasterTest.cpp
 * @brief AreaMasterクラスのテスト
 * @author keiya121
 */

#include "AreaMaster.h"
#include "Logger.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2024_test {

  // 左コースで指定動作を行う場合のテスト
  TEST(AreaMasterTest, runLineTraceLeft)
  {
    Area area = Area::LineTrace;
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
    areaMaster.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
    // WarningやErrorが出ていた場合にoutputを出力する
    if(!actual) {
      EXPECT_EQ(output, "");
    }
  }

  // 右コースで指定動作を行う場合のテスト
  TEST(AreaMasterTest, runLineTraceRight)
  {
    Area area = Area::LineTrace;
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
    areaMaster.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  }

  // 左コースで指定動作を行う場合のテスト
  TEST(AreaMasterTest, runDoubleLoopLeft)
  {
    Area area = Area::DoubleLoop;
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
    areaMaster.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
    // WarningやErrorが出ていた場合にoutputを出力する
    if(!actual) {
      EXPECT_EQ(output, "");
    }
  }

  // 右コースで指定動作を行う場合のテスト
  TEST(AreaMasterTest, runDoubleLoopRight)
  {
    Area area = Area::DoubleLoop;
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
    areaMaster.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  }

  // 左コースで指定動作を行う場合のテスト
  TEST(AreaMasterTest, runDebrisRemovalLeft)
  {
    Area area = Area::DebrisRemoval;
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
    areaMaster.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
    // WarningやErrorが出ていた場合にoutputを出力する
    if(!actual) {
      EXPECT_EQ(output, "");
    }
  }

  // 右コースで指定動作を行う場合のテスト
  TEST(AreaMasterTest, runDebrisRemovalRight)
  {
    Area area = Area::DebrisRemoval;
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
    areaMaster.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
    printf("%s", output.c_str());
    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  }

  // // 左コースで指定動作を行う場合のテスト
  // TEST(AreaMasterTest, runSmartCarryLeft)
  // {
  //   Area area = Area::SmartCarry;
  //   bool isLeftCourse = true;
  //   bool isLeftEdge = isLeftCourse;
  //   int targetBrightness = 45;

  //   testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
  //   class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
  //   areaMaster.run();
  //   string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

  //   // find("str")はstrが見つからない場合string::nposを返す
  //   bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
  //   printf("%s", output.c_str());
  //   EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  //   // WarningやErrorが出ていた場合にoutputを出力する
  //   if(!actual) {
  //     EXPECT_EQ(output, "");
  //   }
  // }

  // // 右コースで指定動作を行う場合のテスト
  // TEST(AreaMasterTest, runSmartCarryRight)
  // {
  //   Area area = Area::SmartCarry;
  //   bool isLeftCourse = false;
  //   bool isLeftEdge = isLeftCourse;
  //   int targetBrightness = 45;

  //   testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
  //   class AreaMaster areaMaster(area, isLeftCourse, isLeftEdge, targetBrightness);
  //   // areaMaster.run();
  //   string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

  //   // find("str")はstrが見つからない場合string::nposを返す
  //   bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;
  //   printf("%s", output.c_str());
  //   EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  // }

}  // namespace etrobocon2024_test
