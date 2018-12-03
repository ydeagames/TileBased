#include "DrawUtils.h"
#include <cmath>
#include <cstdio>

#define DX(exp) if (exp) { return -1; }

namespace DrawUtils
{
	// カプセル描画における半円の分割数
	const int NUM_CAPSULE_DIVISION = 16;

	// 破線を描画
	int DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness)
	{
		int vx = x2 - x1;
		int vy = y2 - y1;

		double angle = atan2(vy, vx);
		float dx = static_cast<float>(length * cos(angle));
		float dy = static_cast<float>(length * sin(angle));

		int count = static_cast<int>(sqrt(vx * vx + vy * vy) / length);

		float x = static_cast<float>(x1);
		float y = static_cast<float>(y1);

		for (int i = 0; i < count; i += 2)
		{
			DX(DrawLine(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + dx), static_cast<int>(y + dy), color, thickness));
			x += dx * 2;
			y += dy * 2;
		}

		if (count % 2 == 0)
		{
			DX(DrawLine(static_cast<int>(x), static_cast<int>(y), x2, y2, color, thickness));
		}

		return 0;
	}

	// 破線を描画(アンチエイリアス効果付き)
	int DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness)
	{
		float vx = x2 - x1;
		float vy = y2 - y1;

		double angle = atan2(vy, vx);
		float dx = static_cast<float>(length * cos(angle));
		float dy = static_cast<float>(length * sin(angle));

		int count = static_cast<int>(sqrt(vx * vx + vy * vy) / length);

		float x = x1;
		float y = y1;

		for (int i = 0; i < count; i += 2)
		{
			DX(DrawLineAA(x, y, (x + dx), (y + dy), color, thickness));
			x += dx * 2;
			y += dy * 2;
		}

		if (count % 2 == 0)
		{
			DX(DrawLineAA(x, y, x2, y2, color, thickness));
		}

		return 0;
	}

	// カプセルを描画
	int DrawCapsule(int x1, int y1, int x2, int y2, int r, unsigned int color, int thickness)
	{
		int vx = x2 - x1;
		int vy = y2 - y1;

		double angle = atan2(vy, vx) + (DX_PI / 2);

		float dx[NUM_CAPSULE_DIVISION + 1];
		float dy[NUM_CAPSULE_DIVISION + 1];
		int i;

		for (i = 0; i < NUM_CAPSULE_DIVISION + 1; i++)
		{
			dx[i] = static_cast<float>(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
			dy[i] = static_cast<float>(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
		}


		DX(DrawLine(static_cast<int>(x1 + dx[0]), static_cast<int>(y1 + dy[0]), static_cast<int>(x2 + dx[0]), static_cast<int>(y2 + dy[0]), color, thickness));

		DX(DrawLine(static_cast<int>(x1 + dx[NUM_CAPSULE_DIVISION]), static_cast<int>(y1 + dy[NUM_CAPSULE_DIVISION]), static_cast<int>(x2 + dx[NUM_CAPSULE_DIVISION]), static_cast<int>(y2 + dy[NUM_CAPSULE_DIVISION]), color, thickness));


		for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
		{
			DX(DrawLine(static_cast<int>(x1 + dx[i]), static_cast<int>(y1 + dy[i]), static_cast<int>(x1 + dx[i + 1]), static_cast<int>(y1 + dy[i + 1]), color, thickness));
		}

		for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
		{
			DX(DrawLine(static_cast<int>(x2 - dx[i]), static_cast<int>(y2 - dy[i]), static_cast<int>(x2 - dx[i + 1]), static_cast<int>(y2 - dy[i + 1]), color, thickness));
		}

		return 0;
	}

	// カプセルを描画(アンチエイリアス効果付き)
	int DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, unsigned int color, float thickness)
	{
		float vx = x2 - x1;
		float vy = y2 - y1;

		double angle = atan2(vy, vx) + (DX_PI / 2);

		float dx[NUM_CAPSULE_DIVISION + 1];
		float dy[NUM_CAPSULE_DIVISION + 1];
		int i;

		for (i = 0; i < NUM_CAPSULE_DIVISION + 1; i++)
		{
			dx[i] = static_cast<float>(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
			dy[i] = static_cast<float>(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
		}


		DX(DrawLineAA(x1 + dx[0], y1 + dy[0], x2 + dx[0], y2 + dy[0], color, thickness));

		DX(DrawLineAA(x1 + dx[NUM_CAPSULE_DIVISION], y1 + dy[NUM_CAPSULE_DIVISION], x2 + dx[NUM_CAPSULE_DIVISION], y2 + dy[NUM_CAPSULE_DIVISION], color, thickness));


		for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
		{
			DX(DrawLineAA(x1 + dx[i], y1 + dy[i], x1 + dx[i + 1], y1 + dy[i + 1], color, thickness));
		}

		for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
		{
			DX(DrawLineAA(x2 - dx[i], y2 - dy[i], x2 - dx[i + 1], y2 - dy[i + 1], color, thickness));
		}

		return 0;
	}
}