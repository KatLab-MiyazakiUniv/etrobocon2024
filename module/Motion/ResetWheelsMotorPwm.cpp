/**
 * @file   ResetWheelsMotorPwm.cpp
 * @brief  両輪モーターリセット&停止
 * @author Negimarge
 */

#include "ResetWheelsMotorPwm.h"

ResetWheelsMotorPwm::ResetWheelsMotorPwm() {}

void ResetWheelsMotorPwm::run()
{
  controller.resetWheelsMotorPwm();
}

void ResetWheelsMotorPwm::logRunning()
{
  logger.log("Run ResetWheelsMotorPwm");
}
