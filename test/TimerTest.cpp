/**
 * @file TimerTest.cpp
 * @brief Timerクラスをテストする
 * @author takahashitom
 */

#include "Timer.h"
#include <gtest/gtest.h>

namespace etrobocon2024_test {
  TEST(TimerTest, sleep)
  {
    Timer timer;
    timer.sleep();
  }

  TEST(TimerTest, now)
  {
    Timer timer;
    timer.now();
  }

  TEST(TimerTest, sleep50)
  {
    Timer timer;
    int sleepTime = 50;
    int initTime = timer.now();
    timer.sleep(sleepTime);
    int actualTime = timer.now();
    int expectedTime = initTime + sleepTime;
    EXPECT_EQ(expectedTime, actualTime);
  }
}  // namespace etrobocon2024_test