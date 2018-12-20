#include "MathUtils.h"

namespace MathUtils
{
	// 0�`w �̐������[�v
	int Loop(int x, int w)
	{
		return ((x % w) + w) % w;
	}

	// 0�`w �̏������[�v
	float Loop(float x, float w)
	{
		return std::fmodf((std::fmodf(x, w) + w), w);
	}

	// min�`max �̐������[�v
	int Loop(int x, int min, int max)
	{
		if (max < min)
			std::swap(min, max);
		return Loop(x - min, max - min) + min;
	}

	// min�`max �̏������[�v
	float Loop(float x, float min, float max)
	{
		if (max < min)
			std::swap(min, max);
		return Loop(x - min, max - min) + min;
	}

	// ���������_���^�̌덷���l���ɓ��ꂽ��r
	bool FloatEquals(float a, float b)
	{
		return std::fabsf(a - b) <= FloatEpsilon;
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
	float Percentage(float x, float max)
	{
		float n = Clamp(x, 0.f, max);
		return n / max;
	}

	// min�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float Percentage(float x, float min, float max)
	{
		if (max < min)
		{
			x = max - x + min;
			std::swap(min, max);
		}
		return Percentage(x - min, max - min);
	}

	// 0�`max�͈̔͂ł�percent%�̈ʒu
	float Lerp(float percent, float max)
	{
		return max * percent;
	}

	// min�`max�͈̔͂ł�percent%�̈ʒu
	float Lerp(float percent, float min, float max)
	{
		if (max < min)
		{
			percent = 1 - percent;
			std::swap(min, max);
		}
		return Lerp(percent, max - min) + min;
	}
}
