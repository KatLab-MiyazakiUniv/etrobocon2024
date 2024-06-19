/**
 * @file   EdgeChanging.cpp
 * @brief  エッジ切り替え
 * @author takahashitom
 */

#include "EdgeChanging.h"

EdgeChanging::EdgeChanging(bool& _isLeftEdge, bool _nextEdge)
  : isLeftEdge(_isLeftEdge), nextEdge(_nextEdge)
{
}

void EdgeChanging::run()
{
  isLeftEdge = nextEdge;
}

void EdgeChanging::logRunning()
{
  char buf[LARGE_BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* isLeftEdgeStr = isLeftEdge ? "true" : "false";
  const char* nextEdgeStr = nextEdge ? "true" : "false";

  snprintf(buf, LARGE_BUF_SIZE, "Run EdgeChanging (isLeftEdge: %s, nextEdge: %s)", isLeftEdgeStr,
           nextEdgeStr);
  logger.log(buf);
}