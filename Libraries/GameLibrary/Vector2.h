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

public:
	// <ベクトル作成>
	Vector2(float x = 0.f, float y = 0.f);

	// <ベクトル作成>
	Vector2(int x, int y);

	// <コピーコンストラクタ>
	//Vector2(const Vector2& src);

public:
	// <代入演算子>
	//Vector2& operator =(const Vector2& src);

	// <整数X>
	int X() const;

	// <整数Y>
	int Y() const;

	// <X成分ベクトル>
	Vector2 VecX() const;

	// <Y成分ベクトル>
	Vector2 VecY() const;

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

	// <整数にスナップしたベクトル>
	Vector2 Snap() const;

	// <同値のベクトルか>
	bool Equals(const Vector2& other, float epsilon = FLOAT_EPSILON) const;

	// <同値のベクトルか>
	Vector2 operator ==(const Vector2& other) const;

	// <同値のベクトルではないか>
	Vector2 operator !=(const Vector2& other) const;

	// <正にしたベクトル>
	Vector2 Abs() const;

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

	// <入力>
	friend std::istream& operator >>(std::istream& is, Vector2& other);

	// <出力>
	friend std::ostream& operator <<(std::ostream& os, Vector2& other);

	// <Vector2 が後にくる 2項 *>
	friend Vector2 operator *(float scale, const Vector2& vec);

	// <Vector2 が後にくる 2項 />
	friend Vector2 operator /(float scale, const Vector2& vec);

	// <Vector2 が後にくる 2項 %>
	friend Vector2 operator %(float scale, const Vector2& vec);
};