#include "Shape.h"
#include "MathUtils.h"

using namespace MathUtils;

Bounds::Bounds(const Vector2& center, const Vector2& size) :
	center(center),
	size(size)
{
}

// <オブジェクトXオフセット>
float Bounds::GetX(HorizontalSide side) const
{
	float offset = 0;
	switch (side)
	{
	case HorizontalSide::LEFT:
		offset = -(size.x / 2.f);
		break;
	case HorizontalSide::RIGHT:
		offset = (size.x / 2.f);
		break;
	}
	return center.x + offset;
}

// <オブジェクトY位置ゲット>
float Bounds::GetY(VerticalSide side) const
{
	float offset = 0;
	switch (side)
	{
	case VerticalSide::TOP:
		offset = -(size.y / 2.f);
		break;
	case VerticalSide::BOTTOM:
		offset = (size.y / 2.f);
		break;
	}
	return center.y + offset;
}

// <中心>
Vector2 Bounds::GetCenter() const
{
	return center;
}

// <The extents of the Bounding Box. This is always half of the size of the Bounds.>
Vector2 Bounds::GetExtents() const
{
	return GetSize() / 2;
}

// <The maximal point of the box. This is always equal to center+extents.>
Vector2 Bounds::GetMax() const
{
	return GetCenter() + GetExtents();
}

// <The minimal point of the box. This is always equal to center-extents.>
Vector2 Bounds::GetMin() const
{
	return GetCenter() - GetExtents();
}

// <The total size of the box. This is always twice as large as the extents.>
Vector2 Bounds::GetSize() const
{
	return size;
}

// <The closest point on the bounding box.>
Vector2 Bounds::ClosestPoint(const Vector2& point) const
{
	return{
		Clamp(point.x, GetMin().x, GetMax().x),
		Clamp(point.y, GetMin().y, GetMax().y),
	};
}

// <Is point contained in the bounding box?>
bool Bounds::Contains(const Vector2& point) const
{
	return (
		GetMin().x < point.x && point.x < GetMax().x &&
		GetMin().y < point.y && point.y < GetMax().y
		);
}

// <Expand the bounds by increasing its size by amount along each side.>
Bounds Bounds::Expand(const float amount) const
{
	return Expand(Vector2::one * amount);
}

// <Expand the bounds by increasing its size by amount along each side.>
Bounds Bounds::Expand(const Vector2& amount) const
{
	return{
		center,
		size + amount * 2,
	};
}

// <Transform>
Bounds Bounds::Transformed(const Transform& transform) const
{
	return{
		center + transform.position,
		size * transform.scale,
	};
}

// <上下衝突処理>
VerticalSide Bounds::CollisionVertical(const Bounds& field, Connection connection, Edge edge)
{
	// ヒットサイド
	VerticalSide side_hit = VerticalSide::NONE;

	// 上下壁当たり判定
	{
		// 縁に応じてパディングを調整
		Bounds padding = field;
		switch (edge)
		{
		case Edge::INNER:
			padding = padding.Expand(-GetSize());
			break;
		case Edge::OUTER:
			padding = padding.Expand(GetSize());
			break;
		}

		// 当たり判定
		if (center.y < padding.GetY(VerticalSide::TOP))
			side_hit = VerticalSide::TOP;
		else if (padding.GetY(VerticalSide::BOTTOM) <= center.y)
			side_hit = VerticalSide::BOTTOM;

		// フィールドのつながり
		switch (connection)
		{
		case Connection::BARRIER:
			// 壁にあたったら調整
			center.y = Clamp(center.y, padding.GetY(VerticalSide::TOP), padding.GetY(VerticalSide::BOTTOM));
			break;
		case Connection::LOOP:
			// 壁にあたったらループ
			center.y = Loop(center.y, padding.GetY(VerticalSide::TOP), padding.GetY(VerticalSide::BOTTOM));
			break;
		}
	}

	return side_hit;
}

// <左右衝突処理>
HorizontalSide Bounds::CollisionHorizontal(const Bounds& field, Connection connection, Edge edge)
{
	// ヒットサイド
	HorizontalSide side_hit = HorizontalSide::NONE;

	// 左右壁当たり判定
	{
		// 縁に応じてパディングを調整
		Bounds padding = field;
		switch (edge)
		{
		case Edge::INNER:
			padding = padding.Expand(-GetSize());
			break;
		case Edge::OUTER:
			padding = padding.Expand(GetSize());
			break;
		}

		// 当たり判定
		if (center.x < padding.GetX(HorizontalSide::LEFT))
			side_hit = HorizontalSide::LEFT;
		else if (padding.GetX(HorizontalSide::RIGHT) <= center.x)
			side_hit = HorizontalSide::RIGHT;

		// フィールドのつながり
		switch (connection)
		{
		case Connection::BARRIER:
			// 壁にあたったら調整
			center.x = Clamp(center.x, padding.GetX(HorizontalSide::LEFT), padding.GetX(HorizontalSide::RIGHT));
			break;
		case Connection::LOOP:
			// 壁にあたったらループ
			center.x = Loop(center.x, padding.GetX(HorizontalSide::LEFT), padding.GetX(HorizontalSide::RIGHT));
			break;
		}
	}

	return side_hit;
}

Bounds Bounds::CreateFromPosition(const Vector2& a, const Vector2& b)
{
	return{ (a + b) / 2, (a - b).Abs() };
}

Bounds Bounds::CreateFromSize(const Vector2& lefttop, const Vector2 & size)
{
	return{ lefttop + size / 2, size };
}

Bounds Bounds::CreateFromCenter(const Vector2& center, const Vector2 & size)
{
	return{ center, size };
}

Bounds Bounds::CreateFromPosition(float x1, float y1, float x2, float y2)
{
	return CreateFromPosition(Vector2{ x1, y1 }, Vector2{ x2, y2 });
}

Box::Box(const Vector2& center, const Vector2& size, float angle)
	: center(center)
	, size(size)
	, angle(angle)
{
}

// <オブジェクト枠>
Bounds Box::GetBounds() const
{
	return{
		center,
		size,
	};
}

Box Box::Transformed(const Transform& t) const
{
	return{ center + t.position, size/* * t.scale*/, angle + t.rotation };
}

Circle::Circle(const Vector2 & center, float size)
	: center(center)
	, size(size)
{
}

Circle Circle::Transformed(const Transform & t) const
{
	return{ center + t.position, size/* * MathUtils::GetMin(t.scale.x, t.scale.y)*/ };
}

Line::Line(const Vector2 & p1, const Vector2 & p2)
	: p1(p1)
	, p2(p2)
{
}

Line Line::Transformed(const Transform & t) const
{
	Vector2 center = (p1 + p2) / 2;
	Vector2 q1 = p1 - center;
	Vector2 q2 = p2 - center;
	//q1 *= t.scale;
	//q2 *= t.scale;
	q1 = q1.Rotate(t.rotation);
	q2 = q2.Rotate(t.rotation);
	q1 += t.position;
	q2 += t.position;
	return{ q1 + center, q2 + center };
}

Quad::Quad(const Bounds& bounds)
{
	vertices[0] = bounds.GetCenter() + -bounds.GetExtents();
	vertices[1] = bounds.GetCenter() + bounds.GetExtents() / Vector2{ 1, -1 };
	vertices[2] = bounds.GetCenter() + bounds.GetExtents();
	vertices[3] = bounds.GetCenter() + bounds.GetExtents() / Vector2{ -1, 1 };
}

Quad Quad::Transformed(const Transform& transform) const
{
	Matrix3 m = transform.GetMatrix();
	return *this * m;
}

Quad Quad::operator*(const Matrix3& matrix) const
{
	Quad quad = *this;
	return (quad *= matrix);
}

Quad& Quad::operator*=(const Matrix3& matrix)
{
	for (auto& vertex : vertices)
		vertex *= matrix;
	return *this;
}
