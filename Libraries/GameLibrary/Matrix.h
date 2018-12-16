#pragma once

class Matrix
{
public:
	Matrix(int, int);
	Matrix();
	~Matrix();
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);

	inline float& operator()(int x, int y) { return p[x][y]; }

	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(float);
	Matrix& operator/=(float);

	Matrix operator^(int) const;
	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix operator*(float) const;
	Matrix operator/(float) const;

	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	friend std::istream& operator >> (std::istream&, Matrix&);

	void swapRows(int, int);
	Matrix transpose();

	static Matrix createIdentity(int);
	static Matrix solve(Matrix, Matrix);
	static Matrix bandSolve(Matrix, Matrix, int);

	// functions on vectors
	static float dotProduct(Matrix, Matrix);

	// functions on augmented matrices
	static Matrix augment(Matrix, Matrix);
	Matrix gaussianEliminate();
	Matrix rowReduceFromGaussian();
	void readSolutionsFromRREF(std::ostream& os);
	Matrix inverse();

	static Matrix CreateRotationX(float radians);
	static Matrix CreateRotationY(float radians);
	static Matrix CreateRotationZ(float radians);

	static Matrix CreateTranslation(const Vec2& translation);
	static Matrix CreateScale(const Vec2& scale);

private:
	int rows_, cols_;
	float **p;

	void allocSpace();
	Matrix expHelper(const Matrix&, int) const;
};

Matrix operator*(float, const Matrix&);

Vec2 operator*(const Vec2&, const Matrix&);
Vec2& operator*=(Vec2&, const Matrix&);
