#pragma once
#include "Vec2.h"
#include "Transform.h"

// <���ʒu�֌W>
enum class HorizontalSide
{
	NONE,
	CENTER,						// X����
	LEFT,						// ��
	RIGHT,						// �E
};

// <�c�ʒu�֌W>
enum class VerticalSide
{
	NONE,
	CENTER,						// Y����
	TOP,						// ��
	BOTTOM,						// ��
};

// <���̈ʒu> 
enum class Edge
{
	CENTER,						// ���̏�
	OUTER,						// ���̊O��
	INNER,						// ���̓���
};

// <���[���h�̂Ȃ���>
enum class Connection
{
	NONE,						// �q����Ȃ��A�����Ȃ���ԂɈړ�
	BARRIER,					// �ǂ�����A�i�߂Ȃ�
	LOOP,						// ���Α�����o�Ă���
};

// <�I�u�W�F�N�g�̌`>
enum class ShapeType
{
	BOX,						// �����`
	CIRCLE,						// �~
	LINE,						// ��
};

// �`
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
	// <�I�u�W�F�N�gX�ʒu�Q�b�g>
	float GetX(HorizontalSide side) const;

	// <�I�u�W�F�N�gY�ʒu�Q�b�g>
	float GetY(VerticalSide side) const;

	// <���S>
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

	// <�㉺�Փˏ���>
	VerticalSide CollisionVertical(const Bounds& obj, Connection connection, Edge edge);

	// <���E�Փˏ���>
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

	// <�I�u�W�F�N�g�g>
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