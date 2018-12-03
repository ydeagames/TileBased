#include "MathUtils.h"
#include <cmath>
#include <limits>
#include <utility>

namespace MathUtils
{
	// 0.0��x��1.0 �̏��������_������
	float GetRandScale()
	{
		return static_cast<float>(GetRand(RAND_MAX)) / RAND_MAX;
	}

	// 0.0��x��max �̐��������_������
	int GetRand(int max)
	{
		return DxLib::GetRand(max);
	}

	// 0.0��x��max �̏��������_������
	float GetRand(float max)
	{
		return GetRandScale() * max;
	}

	// min��x��max �̐��������_������
	int GetRandRange(int min, int max)
	{
		if (max < min)
			std::swap(min, max);
		return GetRand(max - min) + min;
	}

	// min��x��max �̏��������_������
	float GetRandRange(float min, float max)
	{
		if (max < min)
			std::swap(min, max);
		return GetRand(max - min) + min;
	}

	// 0�`w �̐������[�v
	int GetLoop(int x, int w)
	{
		return ((x % w) + w) % w;
	}

	// 0�`w �̏������[�v
	float GetLoop(float x, float w)
	{
		return std::fmodf((std::fmodf(x, w) + w), w);
	}

	// min�`max �̐������[�v
	int GetLoopRange(int x, int min, int max)
	{
		if (max < min)
			std::swap(min, max);
		return GetLoop(x - min, max - min) + min;
	}

	// min�`max �̏������[�v
	float GetLoopRange(float x, float min, float max)
	{
		if (max < min)
			std::swap(min, max);
		return GetLoop(x - min, max - min) + min;
	}

	// ���������_���^�̌덷���l���ɓ��ꂽ��r
	bool FloatEquals(float a, float b)
	{
		return std::abs(a - b) <= std::numeric_limits<float>::epsilon();
	}

	// �p�x�̒P�ʕϊ�([�x]��[���W�A��])
	float ToRadians(float degree)
	{
		return degree * DX_PI_F / 180.0f;
	}

	// �p�x�̒P�ʕϊ�([���W�A��]��[�x])
	float ToDegrees(float radian)
	{
		return radian * 180.0f / DX_PI_F;
	}

	// 0�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float GetPercentage(float x, float max)
	{
		float n = GetClamp(x, 0.f, max);
		return n / max;
	}

	// min�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float GetPercentageRange(float x, float min, float max)
	{
		if (max < min)
		{
			x = max - x + min;
			std::swap(min, max);
		}
		return GetPercentage(x - min, max - min);
	}

	// 0�`max�͈̔͂ł�percent%�̈ʒu
	float GetPercentValue(float percent, float max)
	{
		return max * percent;
	}

	// min�`max�͈̔͂ł�percent%�̈ʒu
	float GetPercentValueRange(float percent, float min, float max)
	{
		if (max < min)
		{
			percent = 1 - percent;
			std::swap(min, max);
		}
		return GetPercentValue(percent, max - min) + min;
	}

	// H : �F���@�L���͈� 0.0f �` 360.0f
	// S : �ʓx�@�L���͈� 0.0f �` 1.0f
	// V : ���x�@�L���͈� 0.0f �` 1.0f
	int GetColorHSV(float H, float S, float V)
	{
		int hi;
		float f, p, q, t;
		float r, g, b;
		int ir, ig, ib;

		hi = (int)(H / 60.0f);
		hi = hi == 6 ? 5 : hi %= 6;
		f = H / 60.0f - static_cast<float>(hi);
		p = V * (1.0f - S);
		q = V * (1.0f - f * S);
		t = V * (1.0f - (1.0f - f) * S);
		switch (hi)
		{
		case 0: r = V; g = t; b = p; break;
		case 1: r = q; g = V; b = p; break;
		case 2: r = p; g = V; b = t; break;
		case 3: r = p; g = q; b = V; break;
		case 4: r = t; g = p; b = V; break;
		case 5: r = V; g = p; b = q; break;
		}

		ir = (int)(r * 255.0f);
		if (ir > 255) ir = 255;
		else if (ir < 0) ir = 0;

		ig = (int)(g * 255.0f);
		if (ig > 255) ig = 255;
		else if (ig < 0) ig = 0;

		ib = (int)(b * 255.0f);
		if (ib > 255) ib = 255;
		else if (ib < 0) ib = 0;

		return GetColor(ir, ig, ib);
	}
}