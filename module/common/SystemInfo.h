/**
 * @file SystemInfo.h
 * @brief 走行システムで統一する情報をまとめたファイル
 * @author takahashitom keiya121
 */

#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H
#include "Measurer.h"
#include "Controller.h"

static constexpr double RADIUS = 50.0;  // 車輪の半径[mm]
static constexpr double TREAD = 125.0;  // 走行体のトレッド幅（両輪の間の距離）[mm]
static bool shouldGetRunLogs = false;   // 実行ログを取得するかのフラグ

static Measurer *measurer;
static Controller *controller;

#endif