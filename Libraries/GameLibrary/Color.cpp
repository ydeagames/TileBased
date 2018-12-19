#include "Color.h"

// <�F�R�[�h(�W���J���[16�F)>
namespace Colors
{
	// H : �F���@�L���͈� 0.0f �` 360.0f
	// S : �ʓx�@�L���͈� 0.0f �` 1.0f
	// V : ���x�@�L���͈� 0.0f �` 1.0f
	Color GetColorHSV(float H, float S, float V)
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