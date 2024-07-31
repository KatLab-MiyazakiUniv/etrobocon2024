/**
 * @file   StopWheelsMotor.cpp
 * @brief  両輪モーター停止
 * @author Negimarge
 */

#include "StopWheelsMotor.h"

StopWheelsMotor::StopWheelsMotor() {}

void StopWheelsMotor::run()
{
  controller.stopWheelsMotor();
}

void StopWheelsMotor::logRunning()
{
  logger.log("Run StopWheelsMotor");
}
