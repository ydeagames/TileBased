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

#pragma once
#include <iostream>

// <ベクトル>
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
	float x;	// X座標
	float y;	// Y座標

public:
	// <ベクトル作成>
	constexpr Vector2(float x, float y)
		: x(x)
		, y(y) {}

	// <ベクトル作成>
	constexpr Vector2(int x, int y)
		: Vector2(static_cast<float>(x), static_cast<float>(y)) {}

	// <ベクトル作成>
	constexpr Vector2()
		: Vector2(0, 0) {}

public:
	// <整数X>
	constexpr inline int X() const { return static_cast<int>(x); }

	// <整数Y>
	constexpr inline int Y() const { return static_cast<int>(y); }

	// <X成分ベクトル>
	constexpr inline Vector2 VecX() const { return { x, 0.f }; }

	// <Y成分ベクトル>
	constexpr inline Vector2 VecY() const { return { 0.f, y }; }

	// <ベクトルの長さ>
	float Length() const;

	// <ベクトルの長さの二乗>
	constexpr inline float LengthSquared() const { return x * x + y * y; }

	// <もう一方のベクトルとの内積>
	constexpr inline float Dot(const Vector2& other) const { return x * other.x + y * other.y; }

	// <もう一方のベクトルとの外積>
	constexpr inline float Cross(const Vector2& other) const { return x * other.y - y * other.x; }

	// <もう一方のベクトルとの距離>
	float LengthTo(const Vector2& other) const;

	// <もう一方のベクトルとの距離の二乗>
	constexpr inline float LengthSquaredTo(const Vector2& other) const { return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y); }

	// <正規化（長さを1にした）ベクトル>
	Vector2 Normalized() const;

	// <Xを整数にスナップしたベクトル>
	Vector2 SnapX(round func = std::roundf) const;

	// <Yを整数にスナップしたベクトル>
	Vector2 SnapY(round func = std::roundf) const;

	// <整数にスナップしたベクトル>
	Vector2 Snap(round func = std::roundf) const;

	// <Xを整数にスナップしたベクトルか>
	bool IsSnappedX(round func = std::roundf) const;

	// <Yを整数にスナップしたベクトルか>
	bool IsSnappedY(round func = std::roundf) const;

	// <整数にスナップしたベクトルか>
	bool IsSnapped(round func = std::roundf) const;

	// <同値のベクトルか>
	bool Equals(const Vector2& other) const;

	// <同値のベクトルか>
	bool operator ==(const Vector2& other) const;

	// <同値のベクトルではないか>
	bool operator !=(const Vector2& other) const;

	// <正にしたベクトル>
	Vector2 Abs() const;

	// <X軸上か>
	bool IsZeroX() const;

	// <Y軸上か>
	bool IsZeroY() const;

	// <0ベクトルか>
	bool IsZero() const;

	// <ベクトルの角度>
	float Angle() const;

	// <ベクトルの角度加算>
	Vector2 Rotate(float rot) const;

	// <最大値と最小値の範囲にクランプ>
	Vector2 Clamp(const Vector2& min, const Vector2& max) const;

	// <ベクトルを分解>
	void Decompose(const Vector2& angle, Vector2& vec_a, Vector2& vec_b) const;

	// <線形補間>
	static Vector2 Lerp(const Vector2& min, const Vector2& max, float step);

	// <線形補間>
	static Vector2 LerpUnclamped(const Vector2& min, const Vector2& max, float step);

	// <from から to への移動を得ます>
	static Vector2 TranslateTowards(const Vector2& from, const Vector2& to, float maxDelta);

	// <ベクトルループ>
	Vector2 Loop(const Vector2& max) const;

	// <ベクトルループ>
	Vector2 Loop(const Vector2& min, const Vector2& max) const;

	// <ベクトルはそのまま>
	constexpr inline Vector2 operator +() const { return *this; }

	// <ベクトルを反転>
	constexpr inline Vector2 operator -() const { return *this*-1; }

	// <ベクトルを加算>
	constexpr inline Vector2 operator +(const Vector2& other) const { return{ x + other.x, y + other.y }; }

	// <ベクトルを減算>
	constexpr inline Vector2 operator -(const Vector2& other) const { return{ x - other.x, y - other.y }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator *(const Vector2& scale) const { return{ x * scale.x, y * scale.y }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator *(float scale) const { return{ x * scale, y * scale }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator /(const Vector2& scale) const { return{ x / scale.x, y / scale.y }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator /(float scale) const { return{ x / scale, y / scale }; }

	// <ベクトルを剰余>
	Vector2 operator %(const Vector2& scale) const;

	// <ベクトルを剰余>
	Vector2 operator %(float scale) const;

	// <複合代入演算 +=>
	inline Vector2& operator +=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	// <複合代入演算 -=>
	inline Vector2& operator -=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// <複合代入演算 *=>
	inline Vector2& Vector2::operator *=(const Vector2& scale)
	{
		x *= scale.x;
		y *= scale.y;
		return *this;
	}

	// <複合代入演算 *=>
	inline Vector2& operator *=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	// <複合代入演算 /=>
	inline Vector2& Vector2::operator /=(const Vector2& scale)
	{
		x /= scale.x;
		y /= scale.y;
		return *this;
	}

	// <複合代入演算 /=>
	inline Vector2& operator /=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}

	// <複合代入演算 %=>
	Vector2& Vector2::operator %=(const Vector2& scale);

	// <複合代入演算 %=>
	Vector2& operator %=(float scale);

	// <入力>
	friend std::istream& operator >>(std::istream& is, Vector2& other);

	// <出力>
	friend std::ostream& operator <<(std::ostream& os, Vector2& other);

	// <Vector2 が後にくる 2項 *>
	constexpr inline friend Vector2 operator *(float scale, const Vector2& vec) { return{ scale * vec.x, scale * vec.y }; }

	// <Vector2 が後にくる 2項 />
	constexpr inline friend Vector2 operator /(float scale, const Vector2& vec) { return{ scale / vec.x, scale / vec.y }; }

	// <Vector2 が後にくる 2項 %>
	friend Vector2 operator %(float scale, const Vector2& vec);
};