#include "Color.h"

RGBColor::RGBColor(const HSVColor & color)
	: RGBColor(color.ToRGB())
{}

HSVColor RGBColor::ToHSV() const
{
	float h, s, v;

	//最大値・最小値の設定
	int MAX = std::max((std::max(r, g)), b);
	int MIN = std::min((std::min(r, g)), b);

	//明度の計算
	v = MAX / 256.f;

	if (MAX == MIN)
	{
		h = 0;
		s = 0;
	}
	else
	{
		//色相の計算
		if (MAX == r) h = 60.f*(g - b) / (MAX - MIN) + 0.f;
		else if (MAX == g) h = 60.f*(b - r) / (MAX - MIN) + 120.f;
		else if (MAX == b) h = 60.f*(r - g) / (MAX - MIN) + 240.f;

		if (h > 360.f) h = h - 360.f;
		else if (h < 0.f) h = h + 360.f;

		//彩度の計算
		s = static_cast<float>(MAX - MIN) / MAX;
	}

	return { h, s, v };
}

HSVColor::HSVColor(const RGBColor & color)
	: HSVColor(color.ToHSV())
{}

RGBColor HSVColor::ToRGB() const
{
	int hi;
	float f, p, q, t;
	float r, g, b;
	int ir, ig, ib;

	hi = (int)(h / 60.0f);
	hi = hi == 6 ? 5 : hi %= 6;
	f = h / 60.0f - static_cast<float>(hi);
	p = v * (1.0f - s);
	q = v * (1.0f - f * s);
	t = v * (1.0f - (1.0f - f) * s);
	switch (hi)
	{
	case 0: r = v; g = t; b = p; break;
	case 1: r = q; g = v; b = p; break;
	case 2: r = p; g = v; b = t; break;
	case 3: r = p; g = q; b = v; break;
	case 4: r = t; g = p; b = v; break;
	case 5: r = v; g = p; b = q; break;
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

	return { ir, ig, ib };
}
