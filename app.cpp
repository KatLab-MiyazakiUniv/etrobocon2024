/**
 * @file app.cpp
 * @brief タスクを管理するクラス
 * @author aridome222
 */

#include "EtRobocon2024.h"
#include "app.h"

// メインタスク
void main_task(intptr_t unused)
{
  EtRobocon2024::start();
  ext_tsk();
}
