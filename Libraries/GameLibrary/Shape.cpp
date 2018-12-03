#include "Shape.h"
#include "MathUtils.h"

using namespace MathUtils;

Bounds::Bounds(const Vec2& center, const Vec2& size) :
	center(center),
	size(size)
{
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
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

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
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

// <���S>
Vec2 Bounds::GetCenter() const
{
	return center;
}

// <The extents of the Bounding Box. This is always half of the size of the Bounds.>
Vec2 Bounds::GetExtents() const
{
	return GetSize() / 2;
}

// <The maximal point of the box. This is always equal to center+extents.>
Vec2 Bounds::GetMax() const
{
	return GetCenter() + GetExtents();
}

// <The minimal point of the box. This is always equal to center-extents.>
Vec2 Bounds::GetMin() const
{
	return GetCenter() - GetExtents();
}

// <The total size of the box. This is always twice as large as the extents.>
Vec2 Bounds::GetSize() const
{
	return size;
}

// <The closest point on the bounding box.>
Vec2 Bounds::ClosestPoint(const Vec2& point) const
{
	return{
		GetClamp(point.x, GetMin().x, GetMax().x),
		GetClamp(point.y, GetMin().y, GetMax().y),
	};
}

// <Is point contained in the bounding box?>
bool Bounds::Contains(const Vec2& point) const
{
	return (
		GetMin().x < point.x && point.x < GetMax().x &&
		GetMin().y < point.y && point.y < GetMax().y
		);
}

// <Expand the bounds by increasing its size by amount along each side.>
Bounds Bounds::Expand(const float amount) const
{
	return{
		center,
		size + Vec2{amount, amount},
	};
}

// <Expand the bounds by increasing its size by amount along each side.>
Bounds Bounds::Expand(const Vec2& amount) const
{
	return{
		center,
		size + amount,
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

// <�㉺�Փˏ���>
VerticalSide Bounds::CollisionVertical(const Bounds& field, Connection connection, Edge edge)
{
	// �q�b�g�T�C�h
	VerticalSide side_hit = VerticalSide::NONE;

	// �㉺�Ǔ����蔻��
	{
		// ���ɉ����ăp�f�B���O�𒲐�
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

		// �����蔻��
		if (center.y < padding.GetY(VerticalSide::TOP))
			side_hit = VerticalSide::TOP;
		else if (padding.GetY(VerticalSide::BOTTOM) <= center.y)
			side_hit = VerticalSide::BOTTOM;

		// �t�B�[���h�̂Ȃ���
		switch (connection)
		{
		case Connection::BARRIER:
			// �ǂɂ��������璲��
			center.y = GetClamp(center.y, padding.GetY(VerticalSide::TOP), padding.GetY(VerticalSide::BOTTOM));
			break;
		case Connection::LOOP:
			// �ǂɂ��������烋�[�v
			center.y = GetLoopRange(center.y, padding.GetY(VerticalSide::TOP), padding.GetY(VerticalSide::BOTTOM));
			break;
		}
	}

	return side_hit;
}

// <���E�Փˏ���>
HorizontalSide Bounds::CollisionHorizontal(const Bounds& field, Connection connection, Edge edge)
{
	// �q�b�g�T�C�h
	HorizontalSide side_hit = HorizontalSide::NONE;

	// ���E�Ǔ����蔻��
	{
		// ���ɉ����ăp�f�B���O�𒲐�
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

		// �����蔻��
		if (center.x < padding.GetX(HorizontalSide::LEFT))
			side_hit = HorizontalSide::LEFT;
		else if (padding.GetX(HorizontalSide::RIGHT) <= center.x)
			side_hit = HorizontalSide::RIGHT;

		// �t�B�[���h�̂Ȃ���
		switch (connection)
		{
		case Connection::BARRIER:
			// �ǂɂ��������璲��
			center.x = GetClamp(center.x, padding.GetX(HorizontalSide::LEFT), padding.GetX(HorizontalSide::RIGHT));
			break;
		case Connection::LOOP:
			// �ǂɂ��������烋�[�v
			center.x = GetLoopRange(center.x, padding.GetX(HorizontalSide::LEFT), padding.GetX(HorizontalSide::RIGHT));
			break;
		}
	}

	return side_hit;
}

Box::Box(const Vec2& center, const Vec2& size, float angle)
	: center(center)
	, size(size)
	, angle(angle)
{
}

// <�I�u�W�F�N�g�g>
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

Circle::Circle(const Vec2 & center, float size)
	: center(center)
	, size(size)
{
}

Circle Circle::Transformed(const Transform & t) const
{
	return{ center + t.position, size/* * MathUtils::GetMin(t.scale.x, t.scale.y)*/ };
}

Line::Line(const Vec2 & p1, const Vec2 & p2)
	: p1(p1)
	, p2(p2)
{
}

Line Line::Transformed(const Transform & t) const
{
	Vec2 center = (p1 + p2) / 2;
	Vec2 q1 = p1 - center;
	Vec2 q2 = p2 - center;
	//q1 *= t.scale;
	//q2 *= t.scale;
	q1 = q1.Rotate(t.rotation);
	q2 = q2.Rotate(t.rotation);
	q1 += t.position;
	q2 += t.position;
	return{ q1 + center, q2 + center };
}
