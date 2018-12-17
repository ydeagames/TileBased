#pragma once
#include "Vector2.h"

// <横位置関係>
enum class HorizontalSide
{
	NONE,
	CENTER,						// X中央
	LEFT,						// 左
	RIGHT,						// 右
};

// <縦位置関係>
enum class VerticalSide
{
	NONE,
	CENTER,						// Y中央
	TOP,						// 上
	BOTTOM,						// 下
};

// <縁の位置> 
enum class Edge
{
	CENTER,						// 縁の上
	OUTER,						// 縁の外側
	INNER,						// 縁の内側
};

// <ワールドのつながり>
enum class Connection
{
	NONE,						// 繋がりなし、見えない空間に移動
	BARRIER,					// 壁があり、進めない
	LOOP,						// 反対側から出てくる
};

// <オブジェクトの形>
enum class ShapeType
{
	BOX,						// 長方形
	CIRCLE,						// 円
	LINE,						// 線
};

// 形
class Shape
{
public:
	virtual ~Shape() {}

public:
	virtual ShapeType GetType() const = 0;
};

class Bounds
{
private:
	Vector2 center;
	Vector2 size;

public:
	Bounds(const Vector2& pos, const Vector2& size);

public:
	// <オブジェクトX位置ゲット>
	float GetX(HorizontalSide side) const;

	// <オブジェクトY位置ゲット>
	float GetY(VerticalSide side) const;

	// <中心>
	Vector2 GetCenter() const;

	// <The extents of the Bounding Box. This is always half of the size of the Bounds.>
	Vector2 GetExtents() const;

	// <The maximal point of the box. This is always equal to center+extents.>
	Vector2 GetMax() const;

	// <The minimal point of the box. This is always equal to center-extents.>
	Vector2 GetMin() const;

	// <The total size of the box. This is always twice as large as the extents.>
	Vector2 GetSize() const;

	// <The closest point on the bounding box.>
	Vector2 ClosestPoint(const Vector2& point) const;

	// <Is point contained in the bounding box?>
	bool Contains(const Vector2& point) const;

	// <Expand the bounds by increasing its size by amount along each side.>
	Bounds Expand(const float amount) const;

	// <Expand the bounds by increasing its size by amount along each side.>
	Bounds Expand(const Vector2& amount) const;

	// <Transform>
	Bounds Transformed(const Transform& transform) const;

	// <上下衝突処理>
	VerticalSide CollisionVertical(const Bounds& obj, Connection connection, Edge edge);

	// <左右衝突処理>
	HorizontalSide CollisionHorizontal(const Bounds& obj, Connection connection, Edge edge);

public:
	static Bounds CreateFromPosition(const Vector2& a, const Vector2& b);

	static Bounds CreateFromSize(const Vector2& lefttop, const Vector2& size);

	static Bounds CreateFromCenter(const Vector2& center, const Vector2& size);

	static Bounds CreateFromPosition(float x1, float y1, float x2, float y2);
};

class Box final : public Shape
{
public:
	Vector2 center;
	Vector2 size;
	float angle;

public:
	Box(const Vector2& center, const Vector2& size, float angle = 0);
	virtual ~Box() {}

public:
	inline ShapeType GetType() const override
	{
		return ShapeType::BOX;
	}

	// <オブジェクト枠>
	Bounds GetBounds() const;

	Box Transformed(const Transform& transform) const;
};

class Quad final : public Shape
{
public:
	std::array<Vector2, 4> vertices;

public:
	Quad(const std::array<Vector2, 4>& vertices)
		: vertices(vertices) {}
	Quad(const Bounds& bounds);
	virtual ~Quad() {}

public:
	inline ShapeType GetType() const override
	{
		return ShapeType::BOX;
	}

	Quad Transformed(const Transform& transform) const;

	Quad operator*(const Matrix3& matrix) const;
	Quad& operator*=(const Matrix3& matrix);
};

class Circle final : public Shape
{
public:
	Vector2 center;
	float size;

public:
	Circle(const Vector2& center, float size);
	virtual ~Circle() {}

public:
	inline ShapeType GetType() const override
	{
		return ShapeType::CIRCLE;
	}

	Circle Transformed(const Transform& transform) const;
};

class Line final : public Shape
{
public:
	Vector2 p1;
	Vector2 p2;

public:
	Line(const Vector2& p1, const Vector2& p2);
	virtual ~Line() {}

public:
	inline ShapeType GetType() const override
	{
		return ShapeType::LINE;
	}

	Line Transformed(const Transform& transform) const;
};