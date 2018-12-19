#pragma once

namespace MathUtils
{
	// 範囲内に制限
	template<class T> T Clamp(T x, T min, T max)
	{
		return std::min(std::max(x, min), max);
	}

	// 0〜w の整数ループ
	int Loop(int x, int w);

	// 0〜w の小数ループ
	float Loop(float x, float w);

	// min〜max の整数ループ
	int Loop(int x, int min, int max);

	// min〜max の小数ループ
	float Loop(float x, float min, float max);

	// 浮動小数点数型の誤差を考慮に入れた比較
	bool FloatEquals(float a, float b);

	// 角度の単位変換([度]→[ラジアン])
	float ToRadians(float degree);

	// 角度の単位変換([ラジアン]→[度])
	float ToDegrees(float radian);

	// 0〜maxの範囲でxは何%の位置にいるのか
	// ※ 範囲外は範囲内に収められます
	float Percentage(float x, float max);

	// min〜maxの範囲でxは何%の位置にいるのか
	// ※ 範囲外は範囲内に収められます
	float Percentage(float x, float min, float max);

	// 0〜maxの範囲でのpercent%の位置
	float Lerp(float percent, float max);

	// min〜maxの範囲でのpercent%の位置
	float Lerp(float percent, float min, float max);

	// H : 色相　有効範囲 0.0f 〜 360.0f
	// S : 彩度　有効範囲 0.0f 〜 1.0f
	// V : 明度　有効範囲 0.0f 〜 1.0f
	int GetColorHSV(float H, float S, float V);
}
