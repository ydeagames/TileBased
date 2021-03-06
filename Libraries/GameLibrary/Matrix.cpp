#include "Matrix.h"

const Matrix3 Matrix3::Identity = CreateIdentity();

Matrix3 Matrix3::Inverse() const
{
	float det =
		p[0][0] * p[1][1] * p[2][2] +
		p[0][1] * p[1][2] * p[2][0] +
		p[0][2] * p[1][0] * p[2][1] -
		p[0][2] * p[1][1] * p[2][0] -
		p[0][1] * p[1][0] * p[2][2] -
		p[0][0] * p[1][2] * p[2][1];

	Matrix3 temp = {};

	temp(0, 0) = p[1][1] * p[2][2] - p[1][2] * p[2][1];
	temp(1, 0) = -(p[1][0] * p[2][2] - p[1][2] * p[2][0]);
	temp(2, 0) = p[1][0] * p[2][1] - p[1][1] * p[2][0];

	temp(0, 1) = -(p[0][1] * p[2][2] - p[0][2] * p[2][1]);
	temp(1, 1) = p[0][0] * p[2][2] - p[0][2] * p[2][0];
	temp(2, 1) = -(p[0][0] * p[2][1] - p[0][1] * p[2][0]);

	temp(0, 2) = p[0][1] * p[1][2] - p[0][2] * p[1][1];
	temp(1, 2) = -(p[0][0] * p[1][2] - p[0][2] * p[1][0]);
	temp(2, 2) = p[0][0] * p[1][1] - p[0][1] * p[1][0];

	return (1.f / det) * temp;
}

Vector2 operator*(const Vector2& v, const Matrix3& m)
{
	Vector2 temp = v;
	return (temp *= m);
}

Vector2& operator*=(Vector2& v, const Matrix3& m)
{
	Matrix<1, 3> temp = {};
	temp(0, 0) = v.x;
	temp(0, 1) = v.y;
	temp(0, 2) = 1;
	temp *= m;
	v.x = temp(0, 0) / temp(0, 2);
	v.y = temp(0, 1) / temp(0, 2);
	return v;
}

Matrix3 Matrix3::CreateRotationX(float radians)
{
	Matrix3 m = CreateIdentity();

	m(1, 1) = std::cosf(radians);
	m(2, 1) = -std::sinf(radians);

	m(1, 2) = std::sinf(radians);
	m(2, 2) = std::cosf(radians);

	return m;
}

Matrix3 Matrix3::CreateRotationY(float radians)
{
	Matrix3 m = CreateIdentity();

	m(0, 0) = std::cosf(radians);
	m(2, 0) = std::sinf(radians);

	m(0, 2) = -std::sinf(radians);
	m(2, 2) = std::cosf(radians);

	return m;
}

Matrix3 Matrix3::CreateRotationZ(float radians)
{
	Matrix3 m = CreateIdentity();

	m(0, 0) = std::cosf(radians);
	m(1, 0) = -std::sinf(radians);

	m(0, 1) = std::sinf(radians);
	m(1, 1) = std::cosf(radians);

	return m;
}

Matrix3 Matrix3::CreateTranslation(const Vector2& translation)
{
	Matrix3 m = CreateIdentity();

	m(2, 0) = translation.x;
	m(2, 1) = translation.y;

	return m;
}

Matrix3 Matrix3::CreateScale(const Vector2& scale)
{
	Matrix3 m = CreateIdentity();

	m(0, 0) = scale.x;
	m(1, 1) = scale.y;

	return m;
}
