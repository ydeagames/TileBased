#pragma once
#include "Shape.h"
#include "Component.h"

class CollisionResult
{
public:
	bool hit;
	float time;
	float normal;

public:
	CollisionResult(bool hit, float time, float normal)
		: hit(hit)
		, time(time)
		, normal(normal) {}

	CollisionResult()
		: CollisionResult(false, 0, 0) {}
};

class Collider;

class BoxCollider;
class CircleCollider;
class LineCollider;

class Collider : public Component
{
public:
	bool isTrigger;

public:
	Collider(bool isTrigger = false)
		: isTrigger(isTrigger) {}
	~Collider() = default;

public:
	virtual ShapeType GetType() const = 0;
	virtual Vector2 GetVelocity() const;
	virtual void Apply(const CollisionResult& result) const = 0;

public:
	virtual CollisionResult Collide(const Collider& other) const = 0;
	virtual CollisionResult Collide(const BoxCollider& other) const = 0;
	virtual CollisionResult Collide(const CircleCollider& other) const = 0;
	virtual CollisionResult Collide(const LineCollider& other) const = 0;
};

template <class T>
class AbstractCollider : public Collider
{
public:
	T shape;

public:
	AbstractCollider(const T& shape, bool isTrigger = false)
		: Collider(isTrigger)
		, shape(shape) {}
	~AbstractCollider() = default;

	virtual ShapeType GetType() const
	{
		return shape.GetType();
	}

	virtual T GetShape(const Transform& transform) const
	{
		return shape.Transformed(transform);
	}
};

class BoxCollider final : public AbstractCollider<Box>
{
public:
	BoxCollider(const Box& shape, bool isTrigger = false)
		: AbstractCollider(shape, isTrigger) {}

public:
	void Apply(const CollisionResult& result) const override;

public:
	CollisionResult Collide(const Collider& other) const override;
	CollisionResult Collide(const BoxCollider& other) const override;
	CollisionResult Collide(const CircleCollider& other) const override;
	CollisionResult Collide(const LineCollider& other) const override;
};

class CircleCollider final : public AbstractCollider<Circle>
{
public:
	CircleCollider(const Circle& shape, bool isTrigger = false)
		: AbstractCollider(shape, isTrigger) {}

public:
	void Apply(const CollisionResult& result) const override;

public:
	CollisionResult Collide(const Collider& other) const override;
	CollisionResult Collide(const BoxCollider& other) const override;
	CollisionResult Collide(const CircleCollider& other) const override;
	CollisionResult Collide(const LineCollider& other) const override;
};

class LineCollider final : public AbstractCollider<Line>
{
public:
	LineCollider(const Line& shape, bool isTrigger = false)
		: AbstractCollider(shape, isTrigger) {}

public:
	void Apply(const CollisionResult& result) const override;

public:
	CollisionResult Collide(const Collider& other) const override;
	CollisionResult Collide(const BoxCollider& other) const override;
	CollisionResult Collide(const CircleCollider& other) const override;
	CollisionResult Collide(const LineCollider& other) const override;
};
