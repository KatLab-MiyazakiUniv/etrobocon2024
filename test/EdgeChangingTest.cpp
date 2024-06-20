/**
 * @file   EdgeChangingTest.cpp
 * @brief  EdgeChangingクラスのテスト
 * @author takahashitom
 */

#include "EdgeChanging.h"
#include <gtest/gtest.h>
#include <cmath>

namespace etrobocon2024_test {

  // 右エッジから右エッジの切り替えのテスト
  TEST(EdgeChanging, runFalseToFalse)
  {
    bool isLeftEdge = false;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = false;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  // 右エッジから左エッジの切り替えのテスト
  TEST(EdgeChanging, runFalseToTrue)
  {
    bool isLeftEdge = false;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = true;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  // 左エッジから右エッジの切り替えのテスト
  TEST(EdgeChanging, runTrueToFalse)
  {
    bool isLeftEdge = true;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = false;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  // 左エッジから左エッジの切り替えのテスト
  TEST(EdgeChanging, runTrueToTrue)
  {
    bool isLeftEdge = true;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = true;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

}  // namespace etrobocon2024_test