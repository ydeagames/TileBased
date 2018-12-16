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
class Vector2
{
public:
	static constexpr float FLOAT_EPSILON = 10e-6f;

	static const Vector2 one;
	static const Vector2 zero;
	static const Vector2 left;
	static const Vector2 up;
	static const Vector2 right;
	static const Vector2 down;

public:
	float x;	// X座標
	float y;	// Y座標

	// <ベクトル作成>
	Vector2(float x = 0.f, float y = 0.f);

	// <ベクトル作成>
	Vector2(int x, int y);

	// <ベクトルの長さ>
	float Length() const;

	// <ベクトルの長さの二乗>
	float LengthSquared() const;

	// <もう一方のベクトルとの内積>
	float Dot(const Vector2& other) const;

	// <もう一方のベクトルとの外積>
	float Cross(const Vector2& other) const;

	// <もう一方のベクトルとの距離>
	float LengthTo(const Vector2& other) const;

	// <もう一方のベクトルとの距離の二乗>
	float LengthSquaredTo(const Vector2& other) const;

	// <正規化（長さを1にした）ベクトル>
	Vector2 Normalized() const;

	// <同値のベクトルか>
	bool Equals(const Vector2& other, float epsilon = FLOAT_EPSILON) const;

	// <正にしたベクトル>
	Vector2 Abs() const;

	// <0ベクトルか>
	bool IsZero() const;

	// <ベクトルの角度>
	float Angle() const;

	// <ベクトルの角度加算>
	Vector2 Rotate(float rot) const;

	// <ベクトルを分解>
	void Decompose(const Vector2& angle, Vector2& vec_a, Vector2& vec_b) const;

	// <線形補間>
	Vector2 Lerp(const Vector2 & min, const Vector2 & max, float step) const;

	// <線形補間>
	Vector2 LerpUnclamped(const Vector2 & min, const Vector2 & max, float step) const;

	// <ベクトルループ>
	Vector2 Loop(const Vector2& max) const;

	// <ベクトルループ>
	Vector2 Loop(const Vector2& min, const Vector2& max) const;

	// <ベクトルはそのまま>
	Vector2 operator +() const;

	// <ベクトルを反転>
	Vector2 operator -() const;

	// <ベクトルを加算>
	Vector2 operator +(const Vector2& other) const;

	// <ベクトルを減算>
	Vector2 operator -(const Vector2& other) const;

	// <ベクトルをスケール>
	Vector2 operator *(const Vector2& scale) const;

	// <ベクトルをスケール>
	Vector2 operator *(float scale) const;

	// <ベクトルをスケール>
	Vector2 operator /(const Vector2& scale) const;

	// <ベクトルをスケール>
	Vector2 operator /(float scale) const;

	// <ベクトルを剰余>
	Vector2 operator %(const Vector2& scale) const;

	// <ベクトルを剰余>
	Vector2 operator %(float scale) const;

	// <複合代入演算 +=>
	Vector2& operator +=(const Vector2& other);

	// <複合代入演算 -=>
	Vector2& operator -=(const Vector2& other);

	// <複合代入演算 *=>
	Vector2& Vector2::operator *=(const Vector2& scale);
		
	// <複合代入演算 *=>
	Vector2& operator *=(float scale);

	// <複合代入演算 /=>
	Vector2& Vector2::operator /=(const Vector2& scale);

	// <複合代入演算 /=>
	Vector2& operator /=(float scale);

	// <複合代入演算 %=>
	Vector2& Vector2::operator %=(const Vector2& scale);

	// <複合代入演算 %=>
	Vector2& operator %=(float scale);
};

// <Vector2 が後にくる 2項 *>
Vector2 operator *(float scale, const Vector2& vec);

// <Vector2 が後にくる 2項 />
Vector2 operator /(float scale, const Vector2& vec);

// <Vector2 が後にくる 2項 %>
Vector2 operator %(float scale, const Vector2& vec);