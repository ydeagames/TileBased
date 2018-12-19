#pragma once

// <�F�R�[�h>
using Color = unsigned int;
using AColor = unsigned int;

// <�F�R�[�h(�W���J���[16�F)>
namespace Colors
{
	enum : Color
	{
		Black = 0xff000000,		// ���F
		Navy = 0xff000080,		// �Z���F
		Green = 0xff008000,		// �ΐF
		Teal = 0xff008080,		// �ΐF
		Maroon = 0xff800000,	// �}���[���F
		Purple = 0xff800080,	// ���F
		Olive = 0xff808000,		// �I���[�u�F
		Gray = 0xff808080,		// �D�F
		Silver = 0xffc0c0c0,	// ��F
		Blue = 0xff0000ff,		// �F
		Lime = 0xff00ff00,		// ���C���O���[���F
		Aqua = 0xff00ffff,		// ���F
		Red = 0xffff0000,		// �ԐF
		Fuchsia = 0xffff00ff,	// �Ԏ��F
		Yellow = 0xffffff00,	// ���F
		White = 0xffffffff,		// ���F
	};

	// H : �F���@�L���͈� 0.0f �` 360.0f
	// S : �ʓx�@�L���͈� 0.0f �` 1.0f
	// V : ���x�@�L���͈� 0.0f �` 1.0f
	Color GetColorHSV(float H, float S, float V);
}

class RGBColor
{
public:
	int r, g, b;

public:
	RGBColor(int r = 0, int g = 0, int b = 0)
		: r(r)
		, g(g)
		, b(b) {}
	RGBColor(Color color = 0x000000)
		: RGBColor(static_cast<int>((color >> 16) & 0xff), static_cast<int>((color >> 8) & 0xff), static_cast<int>((color >> 0) & 0xff)) {}
	RGBColor(float R = 0, float G = 0, float B = 0)
		: RGBColor(static_cast<int>(R * 255.f), static_cast<int>(G * 255.f), static_cast<int>(B * 255.f)) {}

public:
	inline float R() { return r / 255.f; } const
	inline float G() { return g / 255.f; } const
	inline float B() { return b / 255.f; } const
	inline void SetR(float R) { r = static_cast<int>(R * 255.f); }
	inline void SetG(float G) { g = static_cast<int>(G * 255.f); }
	inline void SetB(float B) { b = static_cast<int>(B * 255.f); }
	inline AColor GetColor() { return ((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff) << 0); }

public:


};

class RGBAColor : public RGBColor
{
public:
	int a;

public:
	RGBAColor(int r = 0, int g = 0, int b = 0, int a = 0)
		: RGBColor(r, g, b)
		, a(a) {}
	RGBAColor(AColor color = 0xff000000)
		: RGBAColor(static_cast<int>((color >> 16) & 0xff), static_cast<int>((color >> 8) & 0xff), static_cast<int>((color >> 0) & 0xff), static_cast<int>((color >> 24) & 0xff)) {}
	RGBAColor(float R = 0, float G = 0, float B = 0, float A = 0)
		: RGBAColor(static_cast<int>(R * 255.f), static_cast<int>(G * 255.f), static_cast<int>(B * 255.f), static_cast<int>(A * 255.f)) {}

public:
	inline float A() { return a / 255.f; } const
	inline void SetA(float A) { a = static_cast<int>(A * 255.f); }
	inline AColor GetColor() { return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff) << 0); }
};

class HSVColor
{
public:
	float h, s, v;

public:
	HSVColor(float h = 0, float s = 0, float v = 0)
		: h(h)
		, s(s)
		, v(v) {}
};
