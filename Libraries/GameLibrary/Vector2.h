/**
* �x�N�g���N���X
*
* �x�N�g���̑����񋟂��܂�
*
* Copyright (c) 2018 YdeaGames
*
* This file is released under the MIT License.
* http://opensource.org/licenses/mit-license.php
*/

#pragma once
#include <iostream>

// <�x�N�g��>
class Vector2
{
public:
	static const Vector2 one;
	static const Vector2 zero;
	static const Vector2 left;
	static const Vector2 up;
	static const Vector2 right;
	static const Vector2 down;

public:
	using round = float(*)(float);

public:
	float x;	// X���W
	float y;	// Y���W

public:
	// <�x�N�g���쐬>
	constexpr Vector2(float x, float y)
		: x(x)
		, y(y) {}

	// <�x�N�g���쐬>
	constexpr Vector2(int x, int y)
		: Vector2(static_cast<float>(x), static_cast<float>(y)) {}

	// <�x�N�g���쐬>
	constexpr Vector2()
		: Vector2(0, 0) {}

public:
	// <����X>
	constexpr inline int X() const { return static_cast<int>(x); }

	// <����Y>
	constexpr inline int Y() const { return static_cast<int>(y); }

	// <X�����x�N�g��>
	constexpr inline Vector2 VecX() const { return { x, 0.f }; }

	// <Y�����x�N�g��>
	constexpr inline Vector2 VecY() const { return { 0.f, y }; }

	// <�x�N�g���̒���>
	float Length() const;

	// <�x�N�g���̒����̓��>
	constexpr inline float LengthSquared() const { return x * x + y * y; }

	// <��������̃x�N�g���Ƃ̓���>
	constexpr inline float Dot(const Vector2& other) const { return x * other.x + y * other.y; }

	// <��������̃x�N�g���Ƃ̊O��>
	constexpr inline float Cross(const Vector2& other) const { return x * other.y - y * other.x; }

	// <��������̃x�N�g���Ƃ̋���>
	float LengthTo(const Vector2& other) const;

	// <��������̃x�N�g���Ƃ̋����̓��>
	constexpr inline float LengthSquaredTo(const Vector2& other) const { return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y); }

	// <���K���i������1�ɂ����j�x�N�g��>
	Vector2 Normalized() const;

	// <X�𐮐��ɃX�i�b�v�����x�N�g��>
	Vector2 SnapX(round func = std::roundf) const;

	// <Y�𐮐��ɃX�i�b�v�����x�N�g��>
	Vector2 SnapY(round func = std::roundf) const;

	// <�����ɃX�i�b�v�����x�N�g��>
	Vector2 Snap(round func = std::roundf) const;

	// <X�𐮐��ɃX�i�b�v�����x�N�g����>
	bool IsSnappedX(round func = std::roundf) const;

	// <Y�𐮐��ɃX�i�b�v�����x�N�g����>
	bool IsSnappedY(round func = std::roundf) const;

	// <�����ɃX�i�b�v�����x�N�g����>
	bool IsSnapped(round func = std::roundf) const;

	// <���l�̃x�N�g����>
	bool Equals(const Vector2& other) const;

	// <���l�̃x�N�g����>
	bool operator ==(const Vector2& other) const;

	// <���l�̃x�N�g���ł͂Ȃ���>
	bool operator !=(const Vector2& other) const;

	// <���ɂ����x�N�g��>
	Vector2 Abs() const;

	// <X���ォ>
	bool IsZeroX() const;

	// <Y���ォ>
	bool IsZeroY() const;

	// <0�x�N�g����>
	bool IsZero() const;

	// <�x�N�g���̊p�x>
	float Angle() const;

	// <�x�N�g���̊p�x���Z>
	Vector2 Rotate(float rot) const;

	// <�ő�l�ƍŏ��l�͈̔͂ɃN�����v>
	Vector2 Clamp(const Vector2& min, const Vector2& max) const;

	// <�x�N�g���𕪉�>
	void Decompose(const Vector2& angle, Vector2& vec_a, Vector2& vec_b) const;

	// <���`���>
	static Vector2 Lerp(const Vector2& min, const Vector2& max, float step);

	// <���`���>
	static Vector2 LerpUnclamped(const Vector2& min, const Vector2& max, float step);

	// <from ���� to �ւ̈ړ��𓾂܂�>
	static Vector2 TranslateTowards(const Vector2& from, const Vector2& to, float maxDelta);

	// <�x�N�g�����[�v>
	Vector2 Loop(const Vector2& max) const;

	// <�x�N�g�����[�v>
	Vector2 Loop(const Vector2& min, const Vector2& max) const;

	// <�x�N�g���͂��̂܂�>
	constexpr inline Vector2 operator +() const { return *this; }

	// <�x�N�g���𔽓]>
	constexpr inline Vector2 operator -() const { return *this*-1; }

	// <�x�N�g�������Z>
	constexpr inline Vector2 operator +(const Vector2& other) const { return{ x + other.x, y + other.y }; }

	// <�x�N�g�������Z>
	constexpr inline Vector2 operator -(const Vector2& other) const { return{ x - other.x, y - other.y }; }

	// <�x�N�g�����X�P�[��>
	constexpr inline Vector2 operator *(const Vector2& scale) const { return{ x * scale.x, y * scale.y }; }

	// <�x�N�g�����X�P�[��>
	constexpr inline Vector2 operator *(float scale) const { return{ x * scale, y * scale }; }

	// <�x�N�g�����X�P�[��>
	constexpr inline Vector2 operator /(const Vector2& scale) const { return{ x / scale.x, y / scale.y }; }

	// <�x�N�g�����X�P�[��>
	constexpr inline Vector2 operator /(float scale) const { return{ x / scale, y / scale }; }

	// <�x�N�g������]>
	Vector2 operator %(const Vector2& scale) const;

	// <�x�N�g������]>
	Vector2 operator %(float scale) const;

	// <����������Z +=>
	inline Vector2& operator +=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	// <����������Z -=>
	inline Vector2& operator -=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// <����������Z *=>
	inline Vector2& Vector2::operator *=(const Vector2& scale)
	{
		x *= scale.x;
		y *= scale.y;
		return *this;
	}

	// <����������Z *=>
	inline Vector2& operator *=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	// <����������Z /=>
	inline Vector2& Vector2::operator /=(const Vector2& scale)
	{
		x /= scale.x;
		y /= scale.y;
		return *this;
	}

	// <����������Z /=>
	inline Vector2& operator /=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}

	// <����������Z %=>
	Vector2& Vector2::operator %=(const Vector2& scale);

	// <����������Z %=>
	Vector2& operator %=(float scale);

	// <����>
	friend std::istream& operator >>(std::istream& is, Vector2& other);

	// <�o��>
	friend std::ostream& operator <<(std::ostream& os, Vector2& other);

	// <Vector2 ����ɂ��� 2�� *>
	constexpr inline friend Vector2 operator *(float scale, const Vector2& vec) { return{ scale * vec.x, scale * vec.y }; }

	// <Vector2 ����ɂ��� 2�� />
	constexpr inline friend Vector2 operator /(float scale, const Vector2& vec) { return{ scale / vec.x, scale / vec.y }; }

	// <Vector2 ����ɂ��� 2�� %>
	friend Vector2 operator %(float scale, const Vector2& vec);
};