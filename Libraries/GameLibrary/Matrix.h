#pragma once
#include "Vec2.h"

template<int rows_, int cols_>
class Matrix;

using Matrix3 = Matrix<3, 3>;

template<int rows_, int cols_>
class Matrix
{
protected:
	float p[rows_][cols_];

public:
	Matrix()
	{
		for (int i = 0; i < rows_; ++i)
			for (int j = 0; j < cols_; ++j)
				p[i][j] = 0;
	}

public:
	inline float& operator()(int x, int y) { return p[x][y]; }
	inline const float& operator()(int x, int y) const { return p[x][y]; }

public:
	template<int rows_2, int cols_2>
	Matrix& operator+=(const Matrix<rows_2, cols_2>& m)
	{
		for (int i = 0; i < rows_; ++i)
			for (int j = 0; j < cols_; ++j)
				p[i][j] += m(i, j);
		return *this;
	}

	template<int rows_2, int cols_2>
	Matrix& operator-=(const Matrix<rows_2, cols_2>& m)
	{
		for (int i = 0; i < rows_; ++i)
			for (int j = 0; j < cols_; ++j)
				p[i][j] -= m(i, j);
		return *this;
	}

	template<int rows_2, int cols_2>
	Matrix& operator*=(const Matrix<rows_2, cols_2>& m)
	{
		Matrix<rows_, cols_2> temp = {};
		for (int i = 0; i < rows_; ++i)
			for (int j = 0; j < cols_2; ++j)
				for (int k = 0; k < cols_; ++k)
					temp(i, j) += (p[i][k] * m(k, j));
		return (*this = temp);
	}

	Matrix& operator*=(float num)
	{
		for (int i = 0; i < rows_; ++i)
			for (int j = 0; j < cols_; ++j)
				p[i][j] *= num;
		return *this;
	}

	Matrix& operator/=(float num)
	{
		for (int i = 0; i < rows_; ++i)
			for (int j = 0; j < cols_; ++j)
				p[i][j] /= num;
		return *this;
	}

	template<int rows_2, int cols_2>
	Matrix operator+(const Matrix<rows_2, cols_2>& m) const
	{
		Matrix temp = *this;
		return (temp += m);
	}

	template<int rows_2, int cols_2>
	Matrix operator-(const Matrix<rows_2, cols_2>& m) const
	{
		Matrix temp = *this;
		return (temp -= m);
	}

	template<int rows_2, int cols_2>
	Matrix operator*(const Matrix<rows_2, cols_2>& m) const
	{
		Matrix temp = *this;
		return (temp *= m);
	}

	friend Matrix operator*(float num, const Matrix& m)
	{
		return (m * num);
	}

	Matrix operator*(float num) const
	{
		Matrix temp = *this;
		return (temp *= num);
	}

	Matrix operator/(float num) const
	{
		Matrix temp = *this;
		return (temp /= num);
	}

public:
	static Matrix CreateIdentity()
	{
		Matrix temp = {};
		for (int i = 0; i < rows_; ++i)
			for (int j = 0; j < cols_; ++j)
				temp(i, j) = (i == j) ? 1.f : 0.f;
		return temp;
	}

public:
	Matrix3 Inverse() const;

public:
	friend Vec2 operator*(const Vec2& v, const Matrix3& m);
	friend Vec2& operator*=(Vec2& v, const Matrix3& m);

public:
	static Matrix3 CreateRotationX(float radians);
	static Matrix3 CreateRotationY(float radians);
	static Matrix3 CreateRotationZ(float radians);

	static Matrix3 CreateTranslation(const Vec2& translation);
	static Matrix3 CreateScale(const Vec2& scale);
};
