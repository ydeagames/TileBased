/**
* ベクトルクラス
*
* ベクトルの操作を提供します
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

// <ベクトル作成>
Vector2::Vector2(float x, float y)
	: x(x)
	, y(y) {}

// <ベクトル作成>
Vector2::Vector2(int x, int y)
	: Vector2(static_cast<float>(x), static_cast<float>(y)) {}

// <ベクトルの長さ>
float Vector2::Length() const
{
	return std::sqrtf(LengthSquared());
}

// <ベクトルの長さの二乗>
float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

// <もう一方のベクトルとの内積>
float Vector2::Dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

// <もう一方のベクトルとの外積>
float Vector2::Cross(const Vector2& other) const
{
	return x * other.y - y * other.x;
}

// <もう一方のベクトルとの距離>
float Vector2::LengthTo(const Vector2& other) const
{
	return std::sqrtf(LengthSquaredTo(other));
}

// <もう一方のベクトルとの距離の二乗>
float Vector2::LengthSquaredTo(const Vector2& other) const
{
	return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
}

// <正規化（長さを1にした）ベクトル>
Vector2 Vector2::Normalized() const
{
	float length = Length();
	if (length > 0)
		return{ x / length, y / length };
	return{};
}

// <整数にスナップしたベクトル>
Vector2 Vector2::Snap() const
{
	return{ std::roundf(x), std::roundf(y) };
}

// <同値のベクトルか>
bool Vector2::Equals(const Vector2& other, float epsilon) const
{
	return fabsf(x - other.x) < epsilon && fabsf(y - other.y) < epsilon;
}

// <正にしたベクトル>
Vector2 Vector2::Abs() const
{
	return{ std::abs(x), std::abs(y) };
}

// <0ベクトルか>
bool Vector2::IsZero() const
{
	return Equals({});
}

// <ベクトルの角度>
float Vector2::Angle() const
{
	return atan2f(y, x);
}

// <ベクトルの角度加算>
Vector2 Vector2::Rotate(float rot) const
{
	return{ x * std::cosf(rot) - y * std::sinf(rot), x * std::sinf(rot) + y * std::cosf(rot) };
}

// <ベクトルを分解>
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

// <線形補間>
Vector2 Vector2::Lerp(const Vector2& min, const Vector2& max, float step)
{
	return{
		MathUtils::Clamp(MathUtils::Lerp(step, min.x, max.x), min.x, max.x),
		MathUtils::Clamp(MathUtils::Lerp(step, min.y, max.y), min.y, max.y),
	};
}

// <線形補間>
Vector2 Vector2::LerpUnclamped(const Vector2& min, const Vector2& max, float step)
{
	return{
		MathUtils::Lerp(step, min.x, max.x),
		MathUtils::Lerp(step, min.y, max.y),
	};
}

// <from から to への移動を得ます>
Vector2 Vector2::TranslateTowards(const Vector2& from, const Vector2& to, float maxDelta)
{
	Vector2 sub = to - from;
	Vector2 vel = sub.Normalized() * maxDelta;
	Vector2 towards = (vel.LengthSquared() < sub.LengthSquared()) ? vel : sub;
	return from + towards;
}

// <ベクトルループ>
Vector2 Vector2::Loop(const Vector2& max) const
{
	return{
		MathUtils::Loop(x, max.x),
		MathUtils::Loop(y, max.y),
	};
}

// <ベクトルループ>
Vector2 Vector2::Loop(const Vector2& min, const Vector2& max) const
{
	return{
		MathUtils::Loop(x, min.x, max.x),
		MathUtils::Loop(y, min.y, max.y),
	};
}

// <ベクトルはそのまま>
Vector2 Vector2::operator +() const
{
	return *this;
}

// <ベクトルを反転>
Vector2 Vector2::operator -() const
{
	return *this*-1;
}

// <ベクトルを加算>
Vector2 Vector2::operator +(const Vector2& other) const
{
	return{ x + other.x, y + other.y };
}

// <ベクトルを減算>
Vector2 Vector2::operator -(const Vector2& other) const
{
	return{ x - other.x, y - other.y };
}

// <ベクトルをスケール>
Vector2 Vector2::operator *(const Vector2& scale) const
{
	return{ x * scale.x, y * scale.y };
}

// <ベクトルをスケール>
Vector2 Vector2::operator *(float scale) const
{
	return{ x * scale, y * scale };
}

// <ベクトルをスケール>
Vector2 Vector2::operator/(const Vector2 & scale) const
{
	return{ x / scale.x, y / scale.y };
}

// <ベクトルをスケール>
Vector2 Vector2::operator /(float scale) const
{
	return{ x / scale, y / scale };
}

// <ベクトルを剰余>
Vector2 Vector2::operator%(const Vector2 & scale) const
{
	return{ MathUtils::Loop(x, scale.x), MathUtils::Loop(y, scale.y) };
}

// <ベクトルを剰余>
Vector2 Vector2::operator%(float scale) const
{
	return{ MathUtils::Loop(x, scale), MathUtils::Loop(y, scale) };
}

// <複合代入演算 +=>
Vector2& Vector2::operator +=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

// <複合代入演算 -=>
Vector2& Vector2::operator -=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

// <複合代入演算 *=>
Vector2& Vector2::operator *=(const Vector2& scale)
{
	x *= scale.x;
	y *= scale.y;
	return *this;
}

// <複合代入演算 *=>
Vector2& Vector2::operator *=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

// <複合代入演算 /=>
Vector2 & Vector2::operator/=(const Vector2 & scale)
{
	x /= scale.x;
	y /= scale.y;
	return *this;
}

// <複合代入演算 /=>
Vector2& Vector2::operator /=(float scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

// <複合代入演算 %=>
Vector2 & Vector2::operator%=(const Vector2 & scale)
{
	x = MathUtils::Loop(x, scale.x);
	y = MathUtils::Loop(x, scale.y);
	return *this;
}

// <複合代入演算 %=>
Vector2 & Vector2::operator%=(float scale)
{
	x = MathUtils::Loop(x, scale);
	y = MathUtils::Loop(x, scale);
	return *this;
}

// <Vector2 が後にくる 2項 *>
Vector2 operator *(float scale, const Vector2& vec)
{
	return{ scale * vec.x, scale * vec.y };
}

// <Vector2 が後にくる 2項 />
Vector2 operator /(float scale, const Vector2& vec)
{
	return{ scale / vec.x, scale / vec.y };
}

// <Vector2 が後にくる 2項 %>
Vector2 operator %(float scale, const Vector2& vec)
{
	return{ MathUtils::Loop(scale, vec.x), MathUtils::Loop(scale, vec.y) };
}
