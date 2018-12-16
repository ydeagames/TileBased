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

#include "Vec2.h"
#include "MathUtils.h"
#include <cmath>

const Vec2 Vec2::one = { 1, 1 };
const Vec2 Vec2::zero = { 0, 0 };
const Vec2 Vec2::left = { -1, 0 };
const Vec2 Vec2::up = { 0, -1 };
const Vec2 Vec2::right = { 1, 0 };
const Vec2 Vec2::down = { 0, 1 };

// <�x�N�g���쐬>
Vec2::Vec2(float x, float y)
	: x(x)
	, y(y) {}

// <�x�N�g���쐬>
Vec2::Vec2(int x, int y)
	: Vec2(static_cast<float>(x), static_cast<float>(y)) {}

// <�x�N�g���̒���>
float Vec2::Length() const
{
	return std::sqrtf(LengthSquared());
}

// <�x�N�g���̒����̓��>
float Vec2::LengthSquared() const
{
	return x * x + y * y;
}

// <��������̃x�N�g���Ƃ̓���>
float Vec2::Dot(const Vec2& other) const
{
	return x * other.x + y * other.y;
}

// <��������̃x�N�g���Ƃ̊O��>
float Vec2::Cross(const Vec2& other) const
{
	return x * other.y - y * other.x;
}

// <��������̃x�N�g���Ƃ̋���>
float Vec2::LengthTo(const Vec2& other) const
{
	return std::sqrtf(LengthSquaredTo(other));
}

// <��������̃x�N�g���Ƃ̋����̓��>
float Vec2::LengthSquaredTo(const Vec2& other) const
{
	return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
}

// <���K���i������1�ɂ����j�x�N�g��>
Vec2 Vec2::Normalized() const
{
	float length = Length();
	if (length > 0)
		return{ x / length, y / length };
	return{};
}

// <���l�̃x�N�g����>
bool Vec2::Equals(const Vec2& other, float epsilon) const
{
	return fabsf(x - other.x) < epsilon && fabsf(y - other.y) < epsilon;
}

// <���ɂ����x�N�g��>
Vec2 Vec2::Abs() const
{
	return{ MathUtils::GetAbs(x), MathUtils::GetAbs(y) };
}

// <0�x�N�g����>
bool Vec2::IsZero() const
{
	return Equals({});
}

// <�x�N�g���̊p�x>
float Vec2::Angle() const
{
	return atan2f(y, x);
}

// <�x�N�g���̊p�x���Z>
Vec2 Vec2::Rotate(float rot) const
{
	return{ x * std::cosf(rot) - y * std::sinf(rot), x * std::sinf(rot) + y * std::cosf(rot) };
}

// <�x�N�g���𕪉�>
void Vec2::Decompose(const Vec2& angle, Vec2& vec_a, Vec2& vec_b) const
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
Vec2 Vec2::Lerp(const Vec2& min, const Vec2& max, float step) const
{
	return{
		MathUtils::GetClamp(MathUtils::GetPercentValueRange(x, min.x, max.x), min.x, max.x),
		MathUtils::GetClamp(MathUtils::GetPercentValueRange(y, min.y, max.y), min.y, max.y),
	};
}

// <���`���>
Vec2 Vec2::LerpUnclamped(const Vec2& min, const Vec2& max, float step) const
{
	return{
		MathUtils::GetPercentValueRange(x, min.x, max.x),
		MathUtils::GetPercentValueRange(y, min.y, max.y),
	};
}

// <�x�N�g�����[�v>
Vec2 Vec2::GetLoop(const Vec2& max) const
{
	return{
		MathUtils::GetLoop(x, max.x),
		MathUtils::GetLoop(y, max.y),
	};
}

// <�x�N�g�����[�v>
Vec2 Vec2::GetLoopRange(const Vec2& min, const Vec2& max) const
{
	return{
		MathUtils::GetLoopRange(x, min.x, max.x),
		MathUtils::GetLoopRange(y, min.y, max.y),
	};
}

// <�x�N�g���͂��̂܂�>
Vec2 Vec2::operator +() const
{
	return *this;
}

// <�x�N�g���𔽓]>
Vec2 Vec2::operator -() const
{
	return *this*-1;
}

// <�x�N�g�������Z>
Vec2 Vec2::operator +(const Vec2& other) const
{
	return{ x + other.x, y + other.y };
}

// <�x�N�g�������Z>
Vec2 Vec2::operator -(const Vec2& other) const
{
	return{ x - other.x, y - other.y };
}

// <�x�N�g�����X�P�[��>
Vec2 Vec2::operator *(const Vec2& scale) const
{
	return{ x * scale.x, y * scale.y };
}

// <�x�N�g�����X�P�[��>
Vec2 Vec2::operator *(float scale) const
{
	return{ x * scale, y * scale };
}

// <�x�N�g�����X�P�[��>
Vec2 Vec2::operator/(const Vec2 & scale) const
{
	return{ x / scale.x, y / scale.y };
}

// <�x�N�g�����X�P�[��>
Vec2 Vec2::operator /(float scale) const
{
	return{ x / scale, y / scale };
}

// <�x�N�g������]>
Vec2 Vec2::operator%(const Vec2 & scale) const
{
	return{ MathUtils::GetLoop(x, scale.x), MathUtils::GetLoop(y, scale.y) };
}

// <�x�N�g������]>
Vec2 Vec2::operator%(float scale) const
{
	return{ MathUtils::GetLoop(x, scale), MathUtils::GetLoop(y, scale) };
}

// <����������Z +=>
Vec2& Vec2::operator +=(const Vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

// <����������Z -=>
Vec2& Vec2::operator -=(const Vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

// <����������Z *=>
Vec2& Vec2::operator *=(const Vec2& scale)
{
	x *= scale.x;
	y *= scale.y;
	return *this;
}

// <����������Z *=>
Vec2& Vec2::operator *=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

// <����������Z /=>
Vec2 & Vec2::operator/=(const Vec2 & scale)
{
	x /= scale.x;
	y /= scale.y;
	return *this;
}

// <����������Z /=>
Vec2& Vec2::operator /=(float scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

// <����������Z %=>
Vec2 & Vec2::operator%=(const Vec2 & scale)
{
	x = MathUtils::GetLoop(x, scale.x);
	y = MathUtils::GetLoop(x, scale.y);
	return *this;
}

// <����������Z %=>
Vec2 & Vec2::operator%=(float scale)
{
	x = MathUtils::GetLoop(x, scale);
	y = MathUtils::GetLoop(x, scale);
	return *this;
}

// <Vec2 ����ɂ��� 2�� *>
Vec2 operator *(float scale, const Vec2& vec)
{
	return{ scale * vec.x, scale * vec.y };
}

// <Vec2 ����ɂ��� 2�� />
Vec2 operator /(float scale, const Vec2& vec)
{
	return{ scale / vec.x, scale / vec.y };
}

// <Vec2 ����ɂ��� 2�� %>
Vec2 operator %(float scale, const Vec2& vec)
{
	return{ MathUtils::GetLoop(scale, vec.x), MathUtils::GetLoop(scale, vec.y) };
}
