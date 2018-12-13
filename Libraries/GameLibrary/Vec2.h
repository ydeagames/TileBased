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

// <ベクトル>
class Vec2
{
public:
	static constexpr float FLOAT_EPSILON = 10e-6f;

	static const Vec2 one;
	static const Vec2 zero;
	static const Vec2 left;
	static const Vec2 up;
	static const Vec2 right;
	static const Vec2 down;

public:
	float x;	// X座標
	float y;	// Y座標

	// <ベクトル作成>
	Vec2(float x = 0.f, float y = 0.f);

	// <ベクトル作成>
	Vec2(int x, int y);

	// <ベクトルの長さ>
	float Length() const;

	// <ベクトルの長さの二乗>
	float LengthSquared() const;

	// <もう一方のベクトルとの内積>
	float Dot(const Vec2& other) const;

	// <もう一方のベクトルとの外積>
	float Cross(const Vec2& other) const;

	// <もう一方のベクトルとの距離>
	float LengthTo(const Vec2& other) const;

	// <もう一方のベクトルとの距離の二乗>
	float LengthSquaredTo(const Vec2& other) const;

	// <正規化（長さを1にした）ベクトル>
	Vec2 Normalized() const;

	// <同値のベクトルか>
	bool Equals(const Vec2& other, float epsilon = FLOAT_EPSILON) const;

	// <正にしたベクトル>
	Vec2 Abs() const;

	// <0ベクトルか>
	bool IsZero() const;

	// <ベクトルの角度>
	float Angle() const;

	// <ベクトルの角度加算>
	Vec2 Rotate(float rot) const;

	// <ベクトルを分解>
	void Decompose(const Vec2& angle, Vec2& vec_a, Vec2& vec_b) const;

	// <ベクトルループ>
	Vec2 GetLoop(const Vec2& max) const;

	// <ベクトルループ>
	Vec2 GetLoopRange(const Vec2& min, const Vec2& max) const;

	// <ベクトルはそのまま>
	Vec2 operator +() const;

	// <ベクトルを反転>
	Vec2 operator -() const;

	// <ベクトルを加算>
	Vec2 operator +(const Vec2& other) const;

	// <ベクトルを減算>
	Vec2 operator -(const Vec2& other) const;

	// <ベクトルをスケール>
	Vec2 operator *(const Vec2& scale) const;

	// <ベクトルをスケール>
	Vec2 operator *(float scale) const;

	// <ベクトルをスケール>
	Vec2 operator /(const Vec2& scale) const;

	// <ベクトルをスケール>
	Vec2 operator /(float scale) const;

	// <ベクトルを剰余>
	Vec2 operator %(const Vec2& scale) const;

	// <ベクトルを剰余>
	Vec2 operator %(float scale) const;

	// <複合代入演算 +=>
	Vec2& operator +=(const Vec2& other);

	// <複合代入演算 -=>
	Vec2& operator -=(const Vec2& other);

	// <複合代入演算 *=>
	Vec2& Vec2::operator *=(const Vec2& scale);
		
	// <複合代入演算 *=>
	Vec2& operator *=(float scale);

	// <複合代入演算 /=>
	Vec2& Vec2::operator /=(const Vec2& scale);

	// <複合代入演算 /=>
	Vec2& operator /=(float scale);

	// <複合代入演算 %=>
	Vec2& Vec2::operator %=(const Vec2& scale);

	// <複合代入演算 %=>
	Vec2& operator %=(float scale);
};

// <Vec2 が後にくる 2項 *>
Vec2 operator *(float scale, const Vec2& vec);

// <Vec2 が後にくる 2項 />
Vec2 operator /(float scale, const Vec2& vec);

// <Vec2 が後にくる 2項 %>
Vec2 operator %(float scale, const Vec2& vec);