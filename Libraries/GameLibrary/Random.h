#pragma once

namespace Random
{
	// 0.0��x��1.0 �̏��������_������
	float Value();

	// 0.0��x��max �̐��������_������
	int Rand(int max);

	// 0.0��x��max �̏��������_������
	float Rand(float max);

	// min��x��max �̐��������_������
	int Range(int min, int max);

	// min��x��max �̏��������_������
	float Range(float min, float max);
}
