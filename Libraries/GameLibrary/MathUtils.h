#pragma once

namespace MathUtils
{
	static constexpr float FloatEpsilon = 10e-6f;

	// �͈͓��ɐ���
	template<class T> T Clamp(T x, T min, T max)
	{
		return std::min(std::max(x, min), max);
	}

	// 0�`w �̐������[�v
	int Loop(int x, int w);

	// 0�`w �̏������[�v
	float Loop(float x, float w);

	// min�`max �̐������[�v
	int Loop(int x, int min, int max);

	// min�`max �̏������[�v
	float Loop(float x, float min, float max);

	// ���������_���^�̌덷���l���ɓ��ꂽ��r
	bool FloatEquals(float a, float b);

	// �p�x�̒P�ʕϊ�([�x]��[���W�A��])
	float ToRadians(float degree);

	// �p�x�̒P�ʕϊ�([���W�A��]��[�x])
	float ToDegrees(float radian);

	// 0�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float Percentage(float x, float max);

	// min�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float Percentage(float x, float min, float max);

	// 0�`max�͈̔͂ł�percent%�̈ʒu
	float Lerp(float percent, float max);

	// min�`max�͈̔͂ł�percent%�̈ʒu
	float Lerp(float percent, float min, float max);
}
