#pragma once

namespace MathUtils
{
	// 絶対値
	template<class T> T GetAbs(T a)
	{
		return a > 0 ? a : -a;
	}

	// 最小値
	template<class T> T GetMin(T a, T b)
	{
		return a < b ? a : b;
	}

	// 最大値
	template<class T> T GetMax(T a, T b)
	{
		return a > b ? a : b;
	}

	// 範囲内に制限
	template<class T> T GetClamp(T x, T min, T max)
	{
		return GetMin(GetMax(x, min), max);
	}

	// 0.0≦x≦1.0 の小数ランダム生成
	float GetRandScale();

	// 0.0≦x≦max の整数ランダム生成
	int GetRand(int max);

	// 0.0≦x≦max の小数ランダム生成
	float GetRand(float max);

	// min≦x≦max の整数ランダム生成
	int GetRandRange(int min, int max);

	// min≦x≦max の小数ランダム生成
	float GetRandRange(float min, float max);

	// 0～w の整数ループ
	int GetLoop(int x, int w);

	// 0～w の小数ループ
	float GetLoop(float x, float w);

	// min～max の整数ループ
	int GetLoopRange(int x, int min, int max);

	// min～max の小数ループ
	float GetLoopRange(float x, float min, float max);

	// 浮動小数点数型の誤差を考慮に入れた比較
	bool FloatEquals(float a, float b);

	// 角度の単位変換([度]→[ラジアン])
	float ToRadians(float degree);

	// 角度の単位変換([ラジアン]→[度])
	float ToDegrees(float radian);

	// 0～maxの範囲でxは何%の位置にいるのか
	// ※ 範囲外は範囲内に収められます
	float GetPercentage(float x, float max);

	// min～maxの範囲でxは何%の位置にいるのか
	// ※ 範囲外は範囲内に収められます
	float GetPercentageRange(float x, float min, float max);

	// 0～maxの範囲でのpercent%の位置
	float GetPercentValue(float percent, float max);

	// min～maxの範囲でのpercent%の位置
	float GetPercentValueRange(float percent, float min, float max);

	// H : 色相　有効範囲 0.0f ～ 360.0f
	// S : 彩度　有効範囲 0.0f ～ 1.0f
	// V : 明度　有効範囲 0.0f ～ 1.0f
	int GetColorHSV(float H, float S, float V);
}