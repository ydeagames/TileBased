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

#include "Vector2.h"
#include "MathUtils.h"
#include <cmath>

const Vector2 Vector2::one = { 1, 1 };
const Vector2 Vector2::zero = { 0, 0 };
const Vector2 Vector2::left = { -1, 0 };
const Vector2 Vector2::up = { 0, -1 };
const Vector2 Vector2::right = { 1, 0 };
const Vector2 Vector2::down = { 0, 1 };

// <�x�N�g���쐬>
Vector2::Vector2(float x, float y)
	: x(x)
	, y(y) {}

// <�x�N�g���쐬>
Vector2::Vector2(int x, int y)
	: Vector2(static_cast<float>(x), static_cast<float>(y)) {}

// <�x�N�g���̒���>
float Vector2::Length() const
{
	return std::sqrtf(LengthSquared());
}

// <�x�N�g���̒����̓��>
float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

// <��������̃x�N�g���Ƃ̓���>
float Vector2::Dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

// <��������̃x�N�g���Ƃ̊O��>
float Vector2::Cross(const Vector2& other) const
{
	return x * other.y - y * other.x;
}

// <��������̃x�N�g���Ƃ̋���>
float Vector2::LengthTo(const Vector2& other) const
{
	return std::sqrtf(LengthSquaredTo(other));
}

// <��������̃x�N�g���Ƃ̋����̓��>
float Vector2::LengthSquaredTo(const Vector2& other) const
{
	return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
}

// <���K���i������1�ɂ����j�x�N�g��>
Vector2 Vector2::Normalized() const
{
	float length = Length();
	if (length > 0)
		return{ x / length, y / length };
	return{};
}

// <�����ɃX�i�b�v�����x�N�g��>
Vector2 Vector2::Snap() const
{
	return{ std::roundf(x), std::roundf(y) };
}

// <���l�̃x�N�g����>
bool Vector2::Equals(const Vector2& other, float epsilon) const
{
	return fabsf(x - other.x) < epsilon && fabsf(y - other.y) < epsilon;
}

// <���ɂ����x�N�g��>
Vector2 Vector2::Abs() const
{
	return{ std::abs(x), std::abs(y) };
}

// <0�x�N�g����>
bool Vector2::IsZero() const
{
	return Equals({});
}

// <�x�N�g���̊p�x>
float Vector2::Angle() const
{
	return atan2f(y, x);
}

// <�x�N�g���̊p�x���Z>
Vector2 Vector2::Rotate(float rot) const
{
	return{ x * std::cosf(rot) - y * std::sinf(rot), x * std::sinf(rot) + y * std::cosf(rot) };
}

// <�x�N�g���𕪉�>
void Vector2::Decompose(const Vector2& angle, Vector2& vec_a, Vector2& vec_b) const
{
	float angle_rota = angle.Angle();
	float vec_rota = Angle();
	float diff_rota = vec_rota - angle_rota;
	float vec_length = Length();

	float vec_a_length = vec_length * cosf(diff_rota);
	float vec_b_length = vec_length * sinf(diff_rota);
	float vec_a_rota = angle_rota;
	float vec_b_rota = angle_rota + MathUtils::ToRadians(90);

	vec_a = { vec_a_length * std::cosf(vec_a_rota), vec_a_length * std::sinf(vec_a_rota) };
	vec_b = { vec_b_length * std::cosf(vec_b_rota), vec_b_length * std::sinf(vec_b_rota) };
}

// <���`���>
Vector2 Vector2::Lerp(const Vector2& min, const Vector2& max, float step)
{
	return{
		MathUtils::Clamp(MathUtils::Lerp(step, min.x, max.x), min.x, max.x),
		MathUtils::Clamp(MathUtils::Lerp(step, min.y, max.y), min.y, max.y),
	};
}

// <���`���>
Vector2 Vector2::LerpUnclamped(const Vector2& min, const Vector2& max, float step)
{
	return{
		MathUtils::Lerp(step, min.x, max.x),
		MathUtils::Lerp(step, min.y, max.y),
	};
}

// <from ���� to �ւ̈ړ��𓾂܂�>
Vector2 Vector2::TranslateTowards(const Vector2& from, const Vector2& to, float maxDelta)
{
	Vector2 sub = to - from;
	Vector2 vel = sub.Normalized() * maxDelta;
	Vector2 towards = (vel.LengthSquared() < sub.LengthSquared()) ? vel : sub;
	return from + towards;
}

// <�x�N�g�����[�v>
Vector2 Vector2::Loop(const Vector2& max) const
{
	return{
		MathUtils::Loop(x, max.x),
		MathUtils::Loop(y, max.y),
	};
}

// <�x�N�g�����[�v>
Vector2 Vector2::Loop(const Vector2& min, const Vector2& max) const
{
	return{
		MathUtils::Loop(x, min.x, max.x),
		MathUtils::Loop(y, min.y, max.y),
	};
}

// <�x�N�g���͂��̂܂�>
Vector2 Vector2::operator +() const
{
	return *this;
}

// <�x�N�g���𔽓]>
Vector2 Vector2::operator -() const
{
	return *this*-1;
}

// <�x�N�g�������Z>
Vector2 Vector2::operator +(const Vector2& other) const
{
	return{ x + other.x, y + other.y };
}

// <�x�N�g�������Z>
Vector2 Vector2::operator -(const Vector2& other) const
{
	return{ x - other.x, y - other.y };
}

// <�x�N�g�����X�P�[��>
Vector2 Vector2::operator *(const Vector2& scale) const
{
	return{ x * scale.x, y * scale.y };
}

// <�x�N�g�����X�P�[��>
Vector2 Vector2::operator *(float scale) const
{
	return{ x * scale, y * scale };
}

// <�x�N�g�����X�P�[��>
Vector2 Vector2::operator/(const Vector2 & scale) const
{
	return{ x / scale.x, y / scale.y };
}

// <�x�N�g�����X�P�[��>
Vector2 Vector2::operator /(float scale) const
{
	return{ x / scale, y / scale };
}

// <�x�N�g������]>
Vector2 Vector2::operator%(const Vector2 & scale) const
{
	return{ MathUtils::Loop(x, scale.x), MathUtils::Loop(y, scale.y) };
}

// <�x�N�g������]>
Vector2 Vector2::operator%(float scale) const
{
	return{ MathUtils::Loop(x, scale), MathUtils::Loop(y, scale) };
}

// <����������Z +=>
Vector2& Vector2::operator +=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

// <����������Z -=>
Vector2& Vector2::operator -=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

// <����������Z *=>
Vector2& Vector2::operator *=(const Vector2& scale)
{
	x *= scale.x;
	y *= scale.y;
	return *this;
}

// <����������Z *=>
Vector2& Vector2::operator *=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

// <����������Z /=>
Vector2 & Vector2::operator/=(const Vector2 & scale)
{
	x /= scale.x;
	y /= scale.y;
	return *this;
}

// <����������Z /=>
Vector2& Vector2::operator /=(float scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

// <����������Z %=>
Vector2 & Vector2::operator%=(const Vector2 & scale)
{
	x = MathUtils::Loop(x, scale.x);
	y = MathUtils::Loop(x, scale.y);
	return *this;
}

// <����������Z %=>
Vector2 & Vector2::operator%=(float scale)
{
	x = MathUtils::Loop(x, scale);
	y = MathUtils::Loop(x, scale);
	return *this;
}

// <Vector2 ����ɂ��� 2�� *>
Vector2 operator *(float scale, const Vector2& vec)
{
	return{ scale * vec.x, scale * vec.y };
}

// <Vector2 ����ɂ��� 2�� />
Vector2 operator /(float scale, const Vector2& vec)
{
	return{ scale / vec.x, scale / vec.y };
}

// <Vector2 ����ɂ��� 2�� %>
Vector2 operator %(float scale, const Vector2& vec)
{
	return{ MathUtils::Loop(scale, vec.x), MathUtils::Loop(scale, vec.y) };
}
