#pragma once

// グラフィックハンドル   
using HGRP = int;
// サウンドハンドル
using HSND = int;
// フォントハンドル
using HFNT = int;
// ネットワークハンドル 
using HNET = int;

// <色コード>
using Color = unsigned int;

// <色コード(標準カラー16色)>
namespace Colors
{
	enum : Color
	{
		Black = 0xff000000,		// 黒色
		Navy = 0xff000080,		// 濃紺色
		Green = 0xff008000,		// 緑色
		Teal = 0xff008080,		// 青緑色
		Maroon = 0xff800000,	// マルーン色
		Purple = 0xff800080,	// 紫色
		Olive = 0xff808000,		// オリーブ色
		Gray = 0xff808080,		// 灰色
		Silver = 0xffc0c0c0,	// 銀色
		Blue = 0xff0000ff,		// 青色
		Lime = 0xff00ff00,		// ライムグリーン色
		Aqua = 0xff00ffff,		// 水色
		Red = 0xffff0000,		// 赤色
		Fuchsia = 0xffff00ff,	// 赤紫色
		Yellow = 0xffffff00,	// 黄色
		White = 0xffffffff,		// 白色
	};
};

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