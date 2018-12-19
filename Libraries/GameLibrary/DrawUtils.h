#pragma once
#include "Color.h"

// グラフィックハンドル   
using HGRP = int;
// サウンドハンドル
using HSND = int;
// フォントハンドル
using HFNT = int;
// ネットワークハンドル 
using HNET = int;

// スクリーン開始
#define screen_start(screen) \
{ \
	HGRP screen_stack = GetDrawScreen(); \
	SetDrawScreen(screen); \
	{
// スクリーン終了
#define screen_end \
	} \
	SetDrawScreen(screen_stack); \
}

// <図形描画関連>
namespace DrawUtils
{
	// 破線を描画
	int DrawDashedLine(int x1, int y1, int x2, int y2, Color color, int length, int thickness = 1);

	// 破線を描画(アンチエイリアス効果付き)
	int DrawDashedLineAA(float x1, float y1, float x2, float y2, Color color, float length, float thickness = 1.0f);

	// カプセルを描画
	int DrawCapsule(int x1, int y1, int x2, int y2, int r, Color color, int thickness = 1);

	// カプセルを描画(アンチエイリアス効果付き)
	int DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, Color color, float thickness = 1.0f);
}