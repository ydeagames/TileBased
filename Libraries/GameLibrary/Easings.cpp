#include "Easings.h"
#include "MathUtils.h"
#include <cmath>
#include <algorithm>

Easing::Easing(ESG esg) :
	easing(esg)
{
}

// Easingを使用し0～maxの範囲でのpercent%の位置
float Easing::GetEasingValue(float percent, float max) const
{
	return MathUtils::GetPercentValue(easing(percent, 0, 1, 1), max);
}

// Easingを使用しmin～maxの範囲でのpercent%の位置
float Easing::GetEasingValueRange(float percent, float min, float max) const
{
	if (max < min)
	{
		percent = 1 - percent;
		std::swap(min, max);
	}
	return GetEasingValue(percent, max - min) + min;
}

namespace Easings
{
	const Easing LINEAR = { [](float t, float b, float c, float d) {
		return c * t / d + b;
	} };

	const Easing INQUAD = { [](float t, float b, float c, float d) {
		t /= d;
		return c * t*t + b;
	} };

	const Easing OUTQUAD = { [](float t, float b, float c, float d) {
		t /= d;
		return -c * t*(t - 2) + b;
	} };

	const Easing INOUTQUAD = { [](float t, float b, float c, float d) {
		t /= d / 2;
		if (t < 1)
			return c / 2 * t*t + b;
		t--;
		return -c / 2 * (t*(t - 2) - 1) + b;
	} };

	const Easing INCUBIC = { [](float t, float b, float c, float d) {
		t /= d;
		return c * t*t*t + b;
	} };

	const Easing OUTCUBIC = { [](float t, float b, float c, float d) {
		t /= d;
		t--;
		return c * (t*t*t + 1) + b;
	} };

	const Easing INOUTCUBIC = { [](float t, float b, float c, float d) {
		if ((t /= d / 2) < 1)
			return c / 2 * t*t*t + b;
		return c / 2 * ((t -= 2)*t*t + 2) + b;
	} };

	const Easing INQUART = { [](float t, float b, float c, float d) {
		return c * (t /= d)*t*t*t + b;
	} };

	const Easing OUTQUART = { [](float t, float b, float c, float d) {
		t /= d;
		t--;
		return -c * (t*t*t*t - 1) + b;
	} };

	const Easing INOUTQUART = { [](float t, float b, float c, float d) {
		t /= d / 2;
		if (t < 1)
			return c / 2 * t*t*t*t + b;
		t -= 2;
		return -c / 2 * (t*t*t*t - 2) + b;
	} };

	const Easing INQUINT = { [](float t, float b, float c, float d) {
		t /= d;
		return c * t*t*t*t*t + b;
	} };

	const Easing OUTQUINT = { [](float t, float b, float c, float d) {
		t /= d;
		t--;
		return c * (t*t*t*t*t + 1) + b;
	} };

	const Easing INOUTQUINT = { [](float t, float b, float c, float d) {
		t /= d / 2;
		if (t < 1)
			return c / 2 * t*t*t*t*t + b;
		t -= 2;
		return c / 2 * (t*t*t*t*t + 2) + b;
	} };

	const Easing INSINE = { [](float t, float b, float c, float d) {
		return -c * std::cosf(t / d * (DX_PI_F / 2)) + c + b;
	} };

	const Easing OUTSINE = { [](float t, float b, float c, float d) {
		return c * std::sinf(t / d * (DX_PI_F / 2)) + b;
	} };

	const Easing INOUTSINE = { [](float t, float b, float c, float d) {
		return -c / 2 * (std::cosf(DX_PI_F*t / d) - 1) + b;
	} };

	const Easing INEXPO = { [](float t, float b, float c, float d) {
		return c * std::powf(2, 10 * (t / d - 1)) + b;
	} };

	const Easing OUTEXPO = { [](float t, float b, float c, float d) {
		return c * (-std::powf(2, -10 * t / d) + 1) + b;
	} };

	const Easing INOUTEXPO = { [](float t, float b, float c, float d) {
		t /= d / 2;
		if (t < 1)
			return c / 2 * std::powf(2, 10 * (t - 1)) + b;
		t--;
		return c / 2 * (-std::powf(2, -10 * t) + 2) + b;
	} };

	const Easing INCIRC = { [](float t, float b, float c, float d) {
		t /= d;
		return -c * (std::sqrtf(1 - t * t) - 1) + b;
	} };

	const Easing OUTCIRC = { [](float t, float b, float c, float d) {
		t /= d;
		t--;
		return c * std::sqrtf(1 - t * t) + b;
	} };

	const Easing INOUTCIRC = { [](float t, float b, float c, float d) {
		t /= d / 2;
		if (t < 1)
			return -c / 2 * (std::sqrtf(1 - t * t) - 1) + b;
		t -= 2;
		return c / 2 * (std::sqrtf(1 - t * t) + 1) + b;
	} };

	const Easing INELASTIC = { [](float t, float b, float c, float d) {
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if (t == 0)
			return b;
		if ((t /= d) == 1)
			return b + c;
		p = d * .3f;
		if (a < fabsf(c)) {
			a = c;
			s = p / 4;
		}
		else
			s = p / (2 * DX_PI_F)*std::asinf(c / a);
		return -(a*std::powf(2, 10 * (t -= 1))*std::sinf((t*d - s)*(2 * DX_PI_F) / p)) + b;
	} };

	const Easing OUTELASTIC = { [](float t, float b, float c, float d) {
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if (t == 0)
			return b;
		if ((t /= d) == 1)
			return b + c;
		p = d * .3f;
		if (a < fabsf(c)) {
			a = c;
			s = p / 4;
		}
		else
			s = p / (2 * DX_PI_F)*std::asinf(c / a);
		return a * std::powf(2, -10 * t)*std::sinf((t*d - s)*(2 * DX_PI_F) / p) + c + b;
	} };

	const Easing INOUTELASTIC = { [](float t, float b, float c, float d) {
		float s = 1.70158f;
		float p = 0;
		float a = c;
		if (t == 0)
			return b;
		if ((t /= d / 2) == 2)
			return b + c;
		p = d * (.3f*1.5f);
		if (a < fabsf(c)) {
			a = c;
			s = p / 4;
		}
		else
			s = p / (2 * DX_PI_F)*std::asinf(c / a);
		if (t < 1)
			return -.5f*(a*std::powf(2, 10 * (t -= 1))*std::sinf((t*d - s)*(2 * DX_PI_F) / p)) + b;
		return a * std::powf(2, -10 * (t -= 1))*std::sinf((t*d - s)*(2 * DX_PI_F) / p)*.5f + c + b;
	} };

	const Easing INBACK = { [](float t, float b, float c, float d) {
		float s = 1.70158f;
		return c * (t /= d)*t*((s + 1)*t - s) + b;
	} };

	const Easing OUTBACK = { [](float t, float b, float c, float d) {
		float s = 1.70158f;
		return c * ((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
	} };

	const Easing INOUTBACK = { [](float t, float b, float c, float d) {
		float s = 1.70158f;
		if ((t /= d / 2) < 1)
			return c / 2 * (t*t*(((s *= 1.525f) + 1)*t - s)) + b;
		return c / 2 * ((t -= 2)*t*(((s *= 1.525f) + 1)*t + s) + 2) + b;
	} };

	const Easing OUTBOUNCE = { [](float t, float b, float c, float d) {
		if ((t /= d) < 1 / 2.75f)
			return c * (7.5625f*t*t) + b;
		else if (t < 2 / 2.75)
			return c * (7.5625f*(t -= 1.5f / 2.75f)*t + .75f) + b;
		else if (t < 2.5 / 2.75)
			return c * (7.5625f*(t -= 2.25f / 2.75f)*t + .9375f) + b;
		else
			return c * (7.5625f*(t -= 2.625f / 2.75f)*t + .984375f) + b;
	} };

	const Easing INBOUNCE = { [](float t, float b, float c, float d) {
		return c - OUTBOUNCE.easing(d - t, 0, c, d) + b;
	} };

	const Easing INOUTBOUNCE = { [](float t, float b, float c, float d) {
		if (t < d / 2)
			return INBOUNCE.easing(t * 2, 0, c, d)*.5f + b;
		return OUTBOUNCE.easing(t * 2 - d, 0, c, d)*.5f + c * .5f + b;
	} };
}
