/**
 * @file   ColorStraight.cpp
 * @brief  目標色まで直進するクラス
 * @author bizyutyu
 */

#include "ColorStraight.h"
using namespace std;

ColorStraight::ColorStraight(COLOR _targetColor, double _targetSpeed)
  : Straight(_targetSpeed), targetColor(_targetColor)
{
}

bool ColorStraight::isMetPreCondition()
{
  // 目標速度値が0の場合は終了する
  if(targetSpeed == 0) {
    logger.logWarning("The targetSpeed value passed to ColorStraight is 0");
    return false;
  }
  // 目標の色がNoneのときwarningを出して終了する
  if(targetColor == COLOR::NONE) {
    logger.logWarning("The targetColor passed to ColorStraight is NONE");
    return false;
  }

  return true;
}

bool ColorStraight::isMetContinuationCondition()
{
  COLOR color = ColorJudge::getColor(measurer.getRawColor());
  if(color == targetColor) {
    return false;
  }

  return true;
}

void ColorStraight::logRunning()
{
  char buf[SMALL_BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, SMALL_BUF_SIZE, "Run ColorStraight (Color: %s, targetSpeed: %f)",
           ColorJudge::colorToString(targetColor), targetSpeed);
  logger.log(buf);
}
