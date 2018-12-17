#pragma once

using ESG = std::function<float(float t, float b, float c, float d)>;

class Easing final
{
public:
	Easing(ESG easing);

	const ESG easing;

	// Easingを使用し0～maxの範囲でのpercent%の位置
	float GetEasingValue(float percent, float max = 1) const;

	// Easingを使用しmin～maxの範囲でのpercent%の位置
	float GetEasingValueRange(float percent, float min = 0, float max = 1) const;
};

namespace Easings
{
	const extern Easing LINEAR;
	const extern Easing INQUAD;
	const extern Easing OUTQUAD;
	const extern Easing INOUTQUAD;
	const extern Easing INCUBIC;
	const extern Easing OUTCUBIC;
	const extern Easing INOUTCUBIC;
	const extern Easing INQUART;
	const extern Easing OUTQUART;
	const extern Easing INOUTQUART;
	const extern Easing INQUINT;
	const extern Easing OUTQUINT;
	const extern Easing INOUTQUINT;
	const extern Easing INSINE;
	const extern Easing OUTSINE;
	const extern Easing INOUTSINE;
	const extern Easing INEXPO;
	const extern Easing OUTEXPO;
	const extern Easing INOUTEXPO;
	const extern Easing INCIRC;
	const extern Easing OUTCIRC;
	const extern Easing INOUTCIRC;
	const extern Easing INELASTIC;
	const extern Easing OUTELASTIC;
	const extern Easing INOUTELASTIC;
	const extern Easing INBACK;
	const extern Easing OUTBACK;
	const extern Easing INOUTBACK;
	const extern Easing INBOUNCE;
	const extern Easing OUTBOUNCE;
	const extern Easing INOUTBOUNCE;
}
