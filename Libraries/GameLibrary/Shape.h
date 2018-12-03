#pragma once
#include "Vec2.h"
#include "Transform.h"

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
	Vec2 center;
	Vec2 size;

public:
	Bounds(const Vec2& pos, const Vec2& size);

public:
	// <オブジェクトX位置ゲット>
	float GetX(HorizontalSide side) const;

	// <オブジェクトY位置ゲット>
	float GetY(VerticalSide side) const;

	// <中心>
	Vec2 GetCenter() const;

	// <The extents of the Bounding Box. This is always half of the size of the Bounds.>
	Vec2 GetExtents() const;

	// <The maximal point of the box. This is always equal to center+extents.>
	Vec2 GetMax() const;

	// <The minimal point of the box. This is always equal to center-extents.>
	Vec2 GetMin() const;

	// <The total size of the box. This is always twice as large as the extents.>
	Vec2 GetSize() const;

	// <The closest point on the bounding box.>
	Vec2 ClosestPoint(const Vec2& point) const;

	// <Is point contained in the bounding box?>
	bool Contains(const Vec2& point) const;

	// <Expand the bounds by increasing its size by amount along each side.>
	Bounds Expand(const float amount) const;

	// <Expand the bounds by increasing its size by amount along each side.>
	Bounds Expand(const Vec2& amount) const;

	// <Transform>
	Bounds Transformed(const Transform& transform) const;

	// <上下衝突処理>
	VerticalSide CollisionVertical(const Bounds& obj, Connection connection, Edge edge);

	// <左右衝突処理>
	HorizontalSide CollisionHorizontal(const Bounds& obj, Connection connection, Edge edge);
};

class Box final : public Shape
{
public:
	Vec2 center;
	Vec2 size;
	float angle;

public:
	Box(const Vec2& center, const Vec2& size, float angle = 0);
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

class Circle final : public Shape
{
public:
	Vec2 center;
	float size;

public:
	Circle(const Vec2& center, float size);
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
	Vec2 p1;
	Vec2 p2;

public:
	Line(const Vec2& p1, const Vec2& p2);
	virtual ~Line() {}

public:
	inline ShapeType GetType() const override
	{
		return ShapeType::LINE;
	}

	Line Transformed(const Transform& transform) const;
};