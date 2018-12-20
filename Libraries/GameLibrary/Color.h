#pragma once

/*
	// <使用方法>

	// Color、AColor
	// AColor定数→Color
	Color color = Colors::Blue & Colors::ColorMask;
	// Color→AColor
	AColor acolor = color | Colors::AlphaMask;

	// RGBColor、RGBAColor
	// AColor定数→RGBColor
	RGBColor rgb = Colors::Black;
	// RGBColor→RGBAColor
	RGBAColor rgba = rgb;
	// AColor→RGBAColor
	RGBAColor rgba_1 = acolor;
	// Color→RGBAColor
	RGBAColor rgba_2 = color | Colors::AlphaMask;
	// RGBAColor→RGBColor
	RGBColor rgb_1 = rgba;
	// RGBColor→RGBAColor
	RGBAColor rgba_3 = color;
	// RGBAColorのRed(int)
	rgba.r;
	// RGBAColorのAlpha(float)
	rgba.A();

	// HSV
	// RGBColor→HSVColor
	HSVColor hsv = rgb;
	// HSVColor→RGBColor
	RGBColor rgba_4 = hsv;
	// Color→RGBColor→HSVColor
	HSVColor hsv_1 = color;
	// HSVColor→RGBColor→RGBAColor
	RGBAColor rgba_5 = hsv;
	// HSVColorのHue(float)
	hsv.h;
	// HSVColorのBlue(int)
	static_cast<RGBColor>(hsv).b;
	// RGBColorのSaturation
	static_cast<HSVColor>(rgb).h;

	// Colorへ変換
	// RGBColor→Color
	Color color_1 = rgb;
	// RGBColor→AColor
	AColor acolor_1 = rgb;
	// RGBAColor→AColor
	AColor acolor_2 = rgba;
	// HSVColor→RGBColor→Color
	Color color_2 = static_cast<RGBColor>(hsv);

	// 関数
	auto f = [](RGBAColor color) {};
	// RGBColor→RGBAColor
	f(rgb);
	// AColor定数→RGBAColor
	f(Colors::Gray);
	// HSV→RGBAColor
	f(static_cast<RGBAColor>(hsv));
*/

// <色コード>
using Color = unsigned int;		// アルファなし色
using AColor = unsigned int;	// アルファ付き色

// <色コード(標準カラー16色)>
namespace Colors
{
	// AColor定数
	enum : AColor
	{
		Black = 0xff000000,		// 黒色
		Navy = 0xff000080,		// 濃紺色
		Green = 0xff008000,		// 緑色
		Teal = 0xff008080,		// 青緑色
		Maroon = 0xff800000,	// マルーン色
		Purple = 0xff800080,	// 紫色
		Olive = 0xff808000,		// オリーブ色
		Gray = 0xff808080,		// 灰色
		Silver = 0xffc0c0c0,	// 銀色
		Blue = 0xff0000ff,		// 青色
		Lime = 0xff00ff00,		// ライムグリーン色
		Aqua = 0xff00ffff,		// 水色
		Red = 0xffff0000,		// 赤色
		Fuchsia = 0xffff00ff,	// 赤紫色
		Yellow = 0xffffff00,	// 黄色
		White = 0xffffffff,		// 白色
	};

	// Color→AColor変換用 (or)
	const AColor AlphaMask = 0xff000000;
	// AColor→Color変換用 (and)
	const AColor ColorMask = 0x00ffffff;
	inline AColor GetAlphaMask(int alpha) { return (alpha & 0xff) << 24; }
	inline AColor GetAlphaColor(Color color, int alpha = 255) { return (color & ColorMask) | GetAlphaMask(alpha); }
	inline AColor GetAlphaMask(float alpha) { return GetAlphaMask(static_cast<int>(alpha * 255.f)); }
	inline AColor GetAlphaColor(Color color, float alpha) { return GetAlphaColor(color, static_cast<int>(alpha * 255.f)); }
}

class HSVColor;
class RGBColor;

// アルファなし色 (0 ～ 255)
class RGBColor
{
public:
	int r, g, b;

public:
	RGBColor(int r, int g, int b)
		: r(r)
		, g(g)
		, b(b) {}
	RGBColor()
		: RGBColor(0, 0, 0) {}
	RGBColor(Color color)
		: RGBColor(static_cast<int>((color >> 16) & 0xff), static_cast<int>((color >> 8) & 0xff), static_cast<int>((color >> 0) & 0xff)) {}
	RGBColor(float R, float G, float B)
		: RGBColor(static_cast<int>(R * 255.f), static_cast<int>(G * 255.f), static_cast<int>(B * 255.f)) {}
	RGBColor(const HSVColor& color);

public:
	inline float R() { return r / 255.f; } const
	inline float G() { return g / 255.f; } const
	inline float B() { return b / 255.f; } const
	inline void SetR(float R) { r = static_cast<int>(R * 255.f); }
	inline void SetG(float G) { g = static_cast<int>(G * 255.f); }
	inline void SetB(float B) { b = static_cast<int>(B * 255.f); }
	inline Color GetColor() { return (((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff) << 0)) | Colors::AlphaMask; }
	inline operator Color() { return GetColor(); }

public:
	HSVColor ToHSV() const;
};

// アルファ付き色 (0 ～ 255)
// Colorからの変換時はColors::AlphaMaskを使用してください
class RGBAColor : public RGBColor
{
public:
	int a;

public:
	RGBAColor(int r, int g, int b, int a = 255)
		: RGBColor(r, g, b)
		, a(a) {}
	RGBAColor(const RGBColor& color)
		: RGBColor(color)
		, a(255) {}
	RGBAColor()
		: RGBAColor(0, 0, 0, 255) {}
	RGBAColor(AColor color)
		: RGBAColor(static_cast<int>((color >> 16) & 0xff), static_cast<int>((color >> 8) & 0xff), static_cast<int>((color >> 0) & 0xff), static_cast<int>((color >> 24) & 0xff)) {}
	RGBAColor(float R, float G, float B, float A = 1)
		: RGBAColor(static_cast<int>(R * 255.f), static_cast<int>(G * 255.f), static_cast<int>(B * 255.f), static_cast<int>(A * 255.f)) {}

public:
	inline float A() { return a / 255.f; } const
	inline void SetA(float A) { a = static_cast<int>(A * 255.f); }
	inline AColor GetColor() { return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff) << 0); }
	inline operator AColor() { return GetColor(); }
};

// H : 色相　有効範囲 0.0f ～ 360.0f
// S : 彩度　有効範囲 0.0f ～ 1.0f
// V : 明度　有効範囲 0.0f ～ 1.0f
class HSVColor
{
public:
	float h, s, v;

public:
	HSVColor(float h, float s, float v)
		: h(h)
		, s(s)
		, v(v) {}
	HSVColor()
		: HSVColor(0, 0, 0) {}
	HSVColor(const RGBColor& color);

public:
	RGBColor ToRGB() const;
};
