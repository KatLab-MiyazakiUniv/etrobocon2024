/**
 * @file EtRobocon2024Test.cpp
 * @brief EtRobocon2024クラスのテストケース
 * @author aridome222
 */

#include "../module/EtRobocon2024.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2024_test {

  class EtRobocon2024Test : public ::testing::Test {
    friend class EtRobocon2024;

   protected:
    virtual void SetUp() {}
    EtRobocon2024 et;
  };

  TEST_F(EtRobocon2024Test, startTest) {}
}  // namespace etrobocon2024_test