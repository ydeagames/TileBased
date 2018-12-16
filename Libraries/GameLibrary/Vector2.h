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

// <�x�N�g��>
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
	float x;	// X���W
	float y;	// Y���W

	// <�x�N�g���쐬>
	Vector2(float x = 0.f, float y = 0.f);

	// <�x�N�g���쐬>
	Vector2(int x, int y);

	// <�x�N�g���̒���>
	float Length() const;

	// <�x�N�g���̒����̓��>
	float LengthSquared() const;

	// <��������̃x�N�g���Ƃ̓���>
	float Dot(const Vector2& other) const;

	// <��������̃x�N�g���Ƃ̊O��>
	float Cross(const Vector2& other) const;

	// <��������̃x�N�g���Ƃ̋���>
	float LengthTo(const Vector2& other) const;

	// <��������̃x�N�g���Ƃ̋����̓��>
	float LengthSquaredTo(const Vector2& other) const;

	// <���K���i������1�ɂ����j�x�N�g��>
	Vector2 Normalized() const;

	// <���l�̃x�N�g����>
	bool Equals(const Vector2& other, float epsilon = FLOAT_EPSILON) const;

	// <���ɂ����x�N�g��>
	Vector2 Abs() const;

	// <0�x�N�g����>
	bool IsZero() const;

	// <�x�N�g���̊p�x>
	float Angle() const;

	// <�x�N�g���̊p�x���Z>
	Vector2 Rotate(float rot) const;

	// <�x�N�g���𕪉�>
	void Decompose(const Vector2& angle, Vector2& vec_a, Vector2& vec_b) const;

	// <���`���>
	Vector2 Lerp(const Vector2 & min, const Vector2 & max, float step) const;

	// <���`���>
	Vector2 LerpUnclamped(const Vector2 & min, const Vector2 & max, float step) const;

	// <�x�N�g�����[�v>
	Vector2 Loop(const Vector2& max) const;

	// <�x�N�g�����[�v>
	Vector2 Loop(const Vector2& min, const Vector2& max) const;

	// <�x�N�g���͂��̂܂�>
	Vector2 operator +() const;

	// <�x�N�g���𔽓]>
	Vector2 operator -() const;

	// <�x�N�g�������Z>
	Vector2 operator +(const Vector2& other) const;

	// <�x�N�g�������Z>
	Vector2 operator -(const Vector2& other) const;

	// <�x�N�g�����X�P�[��>
	Vector2 operator *(const Vector2& scale) const;

	// <�x�N�g�����X�P�[��>
	Vector2 operator *(float scale) const;

	// <�x�N�g�����X�P�[��>
	Vector2 operator /(const Vector2& scale) const;

	// <�x�N�g�����X�P�[��>
	Vector2 operator /(float scale) const;

	// <�x�N�g������]>
	Vector2 operator %(const Vector2& scale) const;

	// <�x�N�g������]>
	Vector2 operator %(float scale) const;

	// <����������Z +=>
	Vector2& operator +=(const Vector2& other);

	// <����������Z -=>
	Vector2& operator -=(const Vector2& other);

	// <����������Z *=>
	Vector2& Vector2::operator *=(const Vector2& scale);
		
	// <����������Z *=>
	Vector2& operator *=(float scale);

	// <����������Z /=>
	Vector2& Vector2::operator /=(const Vector2& scale);

	// <����������Z /=>
	Vector2& operator /=(float scale);

	// <����������Z %=>
	Vector2& Vector2::operator %=(const Vector2& scale);

	// <����������Z %=>
	Vector2& operator %=(float scale);
};

// <Vector2 ����ɂ��� 2�� *>
Vector2 operator *(float scale, const Vector2& vec);

// <Vector2 ����ɂ��� 2�� />
Vector2 operator /(float scale, const Vector2& vec);

// <Vector2 ����ɂ��� 2�� %>
Vector2 operator %(float scale, const Vector2& vec);