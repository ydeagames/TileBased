#pragma once

namespace MathUtils
{
	// ��Βl
	template<class T> T GetAbs(T a)
	{
		return a > 0 ? a : -a;
	}

	// �ŏ��l
	template<class T> T GetMin(T a, T b)
	{
		return a < b ? a : b;
	}

	// �ő�l
	template<class T> T GetMax(T a, T b)
	{
		return a > b ? a : b;
	}

	// �͈͓��ɐ���
	template<class T> T GetClamp(T x, T min, T max)
	{
		return GetMin(GetMax(x, min), max);
	}

	// 0.0��x��1.0 �̏��������_������
	float GetRandScale();

	// 0.0��x��max �̐��������_������
	int GetRand(int max);

	// 0.0��x��max �̏��������_������
	float GetRand(float max);

	// min��x��max �̐��������_������
	int GetRandRange(int min, int max);

	// min��x��max �̏��������_������
	float GetRandRange(float min, float max);

	// 0�`w �̐������[�v
	int GetLoop(int x, int w);

	// 0�`w �̏������[�v
	float GetLoop(float x, float w);

	// min�`max �̐������[�v
	int GetLoopRange(int x, int min, int max);

	// min�`max �̏������[�v
	float GetLoopRange(float x, float min, float max);

	// ���������_���^�̌덷���l���ɓ��ꂽ��r
	bool FloatEquals(float a, float b);

	// �p�x�̒P�ʕϊ�([�x]��[���W�A��])
	float ToRadians(float degree);

	// �p�x�̒P�ʕϊ�([���W�A��]��[�x])
	float ToDegrees(float radian);

	// 0�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float GetPercentage(float x, float max);

	// min�`max�͈̔͂�x�͉�%�̈ʒu�ɂ���̂�
	// �� �͈͊O�͔͈͓��Ɏ��߂��܂�
	float GetPercentageRange(float x, float min, float max);

	// 0�`max�͈̔͂ł�percent%�̈ʒu
	float GetPercentValue(float percent, float max);

	// min�`max�͈̔͂ł�percent%�̈ʒu
	float GetPercentValueRange(float percent, float min, float max);

	// H : �F���@�L���͈� 0.0f �` 360.0f
	// S : �ʓx�@�L���͈� 0.0f �` 1.0f
	// V : ���x�@�L���͈� 0.0f �` 1.0f
	int GetColorHSV(float H, float S, float V);
}