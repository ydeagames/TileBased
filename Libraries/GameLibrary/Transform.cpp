#include "Transform.h"

Transform::Transform(const Vec2& position, float rotation, const Vec2& scale)
	: position(position)
	, rotation(rotation)
	, scale(scale)
{
}

Transform::Transform()
	: Transform(Vec2{}, 0, Vec2{ 1, 1 })
{
}

Matrix Transform::GetMatrix() const
{
	Matrix m = Matrix::CreateScale(scale);
	m *= Matrix::CreateRotationZ(rotation);
	m *= Matrix::CreateTranslation(position);
	return m;
}

/*
Transform Transform::Transformed() const
{
	Transform transform;
	if (auto ptransform = parent.lock())
		transform = ptransform->Transformed();
	transform.scale *= scale;
	transform.position += position.Rotate(transform.rotation);
	transform.rotation += rotation;
	return transform;
}
/**/