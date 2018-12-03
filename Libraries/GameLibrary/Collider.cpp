#include "Collider.h"
#include "MathUtils.h"

Vec2 Collider::GetVelocity() const
{
	auto rigidbody = gameObject()->GetComponent<Rigidbody>();
	if (rigidbody)
		return rigidbody->vel;
	return Vec2{};
}

// Utils
static CollisionResult CollisionSegment(const Vec2& _p1, const Vec2& _p2, const Vec2& _p3, const Vec2& _p4) {
	float _time = -1;

	//交差判定
	float d1 = (_p4 - _p3).Cross(_p1 - _p3);
	float d2 = (_p4 - _p3).Cross(_p2 - _p3);
	float d3 = (_p2 - _p1).Cross(_p3 - _p1);
	float d4 = (_p2 - _p1).Cross(_p4 - _p1);
	if (d1*d2 > 0.f || d3 * d4 > 0.f) {
		return{};
	}
	//線分が一直線上にあるかの確認
	if (MathUtils::FloatEquals(d1, 0.f) && MathUtils::FloatEquals(d2, 0.f) && MathUtils::FloatEquals(d3, 0.f) && MathUtils::FloatEquals(d4, 0.f)) {
		float dot1 = (_p1 - _p3).Dot(_p2 - _p3);
		float dot2 = (_p1 - _p4).Dot(_p2 - _p4);
		if (dot1 <= 0.f || dot2 <= 0.f) {
			_time = 0.f;
			return{ true, _time, 0 };
		}
		return{};
	}
	d1 = fabsf(d1);
	d2 = fabsf(d2);
	_time = d1 / (d1 + d2);

	return{ true, _time, 0 };
}

static CollisionResult CollisionRayCircle(const Vec2& _ray_pos, const Vec2& _ray_vec, const Vec2& _circle_pos, const float _radius) {
	float _time;

	//エラーチェック
	if (_radius < 0.f) {
		return{};
	}
	if (MathUtils::FloatEquals(_ray_vec.x, 0.f) && MathUtils::FloatEquals(_ray_vec.y, 0.f)) {
		return{};
	}

	//オフセットの計算
	Vec2 ray_pos = _ray_pos - _circle_pos;

	//レイの方向ベクトルの正規化
	Vec2 ray_vec = _ray_vec.Normalized();

	// 係数を算出
	float dot = ray_pos.Dot(ray_vec);
	float s = dot * dot - ray_pos.Dot(ray_pos) + _radius * _radius;

	//誤差の修正
	if (MathUtils::FloatEquals(s, 0.f)) {
		s = 0.f;
	}
	if (s < 0.0f) {
		return{};
	}

	//衝突するまでの時間
	_time = -dot - sqrtf(s);

	return{ true, _time, 0 };
}

static CollisionResult CollisionCircleSegment(const Circle& _circle, const Vec2& _circle_vel, const Vec2& _p1, const Vec2& _p2) {
	float _time = -1;

	//衝突したかの判定
	bool is_collision = false;

	//位置関係の把握
	float cross = (_circle.center - _p1).Cross(_p2 - _p1);

	//円に近い線分の計算
	Vec2 p3, p4, translate;
	if (cross >= 0) {
		translate = Vec2::right.Rotate((_p2 - _p1).Angle() - DX_PI_F / 2) * (_circle.size + 1);
	}
	else {
		translate = Vec2::right.Rotate((_p2 - _p1).Angle() + DX_PI_F / 2) * (_circle.size + 1);
	}
	p3 = _p1 + translate;
	p4 = _p2 + translate;

	//DrawLineAA(p3.x, p3.y, p4.x, p4.y, COLOR_BLUE, 3);

	//バグ対策の線分との衝突判定
	CollisionResult result1 = CollisionSegment(_circle.center, _circle.center + _circle_vel, _p1, _p2);
	if (result1.hit) {
		is_collision = true;
		_time = result1.time;
	}

	//近い線分との衝突判定
	CollisionResult result2 = CollisionSegment(_circle.center, _circle.center + _circle_vel, p3, p4);
	if (result2.hit) {
		if (!is_collision || result2.time < _time) {
			is_collision = true;
			_time = result2.time;
		}
	}

	//始点との衝突判定
	CollisionResult result3 = CollisionRayCircle(_circle.center, _circle_vel, _p1, _circle.size);
	if (result3.hit) {
		if (result3.time <= 1.f && result3.time >= 0.f) {
			if (!is_collision || result3.time < _time) {
				is_collision = true;
				_time = result3.time;
			}
		}
	}

	//終点との衝突判定
	CollisionResult result4 = CollisionRayCircle(_circle.center, _circle_vel, _p2, _circle.size);
	if (result4.hit) {
		if (result4.time <= 1.f && result4.time >= 0.f) {
			if (!is_collision || result4.time < _time) {
				is_collision = true;
				_time = result4.time;
			}
		}
	}

	if (is_collision)
		return{ is_collision, _time, 0 };
	return{};
}


// Box

void BoxCollider::Apply(const CollisionResult & result) const
{
	auto transform = gameObject()->transform();
	transform->position += GetVelocity() * result.time;
	float rotate = DX_PI_F / 2 - result.normal;
	float rotate_angle = transform->rotation + rotate;
	if (sinf(rotate_angle) < 0) {
		transform->rotation = MathUtils::GetLoop(-rotate_angle - rotate, DX_TWO_PI_F);
	}
	auto rigidbody = gameObject()->GetComponent<Rigidbody>();
	if (rigidbody)
		rigidbody->vel = Vec2::right.Rotate(transform->rotation) * (1.f - result.time);
}

CollisionResult BoxCollider::Collide(const Collider& other) const
{
	return other.Collide(*this);
}

CollisionResult BoxCollider::Collide(const BoxCollider& other) const
{
	const Box _rect1 = GetShape(*gameObject()->transform());
	const Box _rect2 = other.GetShape(*other.gameObject()->transform());

	//各頂点座標の計算
	Vec2 vertex1[4];
	Vec2 vertex2[4];
	for (int i = 0; i < 4; ++i) {
		Vec2 c = { (i == 0 || i == 3) ? -1 : 1, (i < 2) ? -1 : 1 };
		vertex1[i] = (_rect1.size / 2 * c).Rotate(_rect1.angle) + _rect1.center;
		vertex2[i] = (_rect2.size / 2 * c).Rotate(_rect2.angle) + _rect2.center;
	}

	//線分の交差判定
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			CollisionResult result = CollisionSegment(vertex1[i], vertex1[(i + 1) % 4], vertex2[j], vertex2[(j + 1) % 4]);
			if (result.hit)
				return result;
		}
	}
	return{};
}

CollisionResult BoxCollider::Collide(const CircleCollider& other) const
{
	const Box _rect = GetShape(*gameObject()->transform());
	const Circle _circle = other.GetShape(*other.gameObject()->transform());
	const auto _rigid1 = gameObject()->GetComponent<Rigidbody>();
	const auto _rigid2 = other.gameObject()->GetComponent<Rigidbody>();

	float _time;
	float _ref_normal;

	//オフセットの計算
	const Vec2& rect_rotate_pos = _rect.center;
	const Vec2& circle_pos = _circle.center;

	//相対速度の計算
	Vec2 vel = (_rigid2 != nullptr ? _rigid2->vel : Vec2{}) - (_rigid1 != nullptr ? _rigid1->vel : Vec2{});

	//各線分との衝突するまでの時間
	float t_a, t_b;
	t_a = t_b = -1.f;

	//衝突状態
	bool is_collision = false;

	//各頂点座標との距離の計算
	Vec2 vertex[4];
	float vertex_distance[4];
	int min_distance_index = 0;
	for (int i = 0; i < 4; ++i) {
		Vec2 c = { (i == 0 || i == 3) ? -1 : 1, (i < 2) ? -1 : 1 };
		vertex[i] = (_rect.size / 2 * c).Rotate(_rect.angle) + rect_rotate_pos;
		vertex_distance[i] = circle_pos.LengthSquaredTo(vertex[i]);
		if (vertex_distance[i] < vertex_distance[min_distance_index]) {
			min_distance_index = i;
		}
	}

	//回転矩形の左側に近い場合
	if (vertex_distance[0] < vertex_distance[1]) {
		CollisionResult result = CollisionCircleSegment(_circle, vel, vertex[0], vertex[3]);
		if (result.hit) {
			t_a = result.time;
			_time = result.time;
			_ref_normal = _rect.angle + DX_PI_F;
			is_collision = true;
		}
	}
	//回転矩形の右側に近い場合
	else {
		CollisionResult result = CollisionCircleSegment(_circle, vel, vertex[1], vertex[2]);
		if (result.hit) {
			t_a = result.time;
			_time = result.time;
			_ref_normal = _rect.angle;
			is_collision = true;
		}
	}

	//回転矩形の上側に近い場合
	if (vertex_distance[1] < vertex_distance[2]) {
		CollisionResult result = CollisionCircleSegment(_circle, vel, vertex[0], vertex[1]);
		if (result.hit) {
			t_b = result.time;
			if (!is_collision || t_b < t_a) {
				_time = result.time;
				_ref_normal = _rect.angle + DX_PI_F * 3 / 2;
				is_collision = true;
			}
		}
	}
	//回転矩形の下側に近い場合
	else {
		CollisionResult result = CollisionCircleSegment(_circle, vel, vertex[2], vertex[3]);
		if (result.hit) {
			t_b = result.time;
			if (!is_collision || t_b < t_a) {
				_time = result.time;
				_ref_normal = _rect.angle + DX_PI_F / 2;
				is_collision = true;
			}
		}
	}

	//角に当たった場合
	if (is_collision && MathUtils::FloatEquals(t_a, t_b)) {
		_ref_normal = _rect.angle + DX_PI_F * 5 / 4 + DX_PI_F / 2 * min_distance_index;
	}

	if (is_collision)
		return{ is_collision, _time, _ref_normal };
	return{};
}

CollisionResult BoxCollider::Collide(const LineCollider& other) const
{
	return CollisionResult();
}

// Circle

void CircleCollider::Apply(const CollisionResult & result) const
{
	auto transform = gameObject()->transform();
	Vec2 vel = GetVelocity();
	transform->position += vel * result.time;
	if (!vel.IsZero())
		transform->rotation = vel.Angle();
	float rotate = DX_PI_F / 2 - result.normal;
	float rotate_angle = transform->rotation + rotate;
	if (sinf(rotate_angle) < 0) {
		transform->rotation = MathUtils::GetLoop(-rotate_angle - rotate, DX_TWO_PI_F);
	}
	auto rigidbody = gameObject()->GetComponent<Rigidbody>();
	if (rigidbody)
		rigidbody->vel = Vec2::right.Rotate(transform->rotation) * vel.Length()/* * (1.f - result.time)*/;
}

CollisionResult CircleCollider::Collide(const Collider& other) const
{
	return other.Collide(*this);
}

CollisionResult CircleCollider::Collide(const BoxCollider& other) const
{
	return other.Collide(*this);
}

CollisionResult CircleCollider::Collide(const CircleCollider& other) const
{
	return CollisionResult();
}

CollisionResult CircleCollider::Collide(const LineCollider& other) const
{
	const Line _line = other.GetShape(*other.gameObject()->transform());
	const Circle _circle = GetShape(*gameObject()->transform());
	const auto _rigid1 = gameObject()->GetComponent<Rigidbody>();
	const auto _rigid2 = other.gameObject()->GetComponent<Rigidbody>();

	//相対速度の計算
	Vec2 vel = (_rigid2 != nullptr ? _rigid2->vel : Vec2{}) - (_rigid1 != nullptr ? _rigid1->vel : Vec2{});

	CollisionResult result = CollisionCircleSegment(_circle, vel, _line.p1, _line.p2);
	if (result.hit) {
		float _ref_normal = (_line.p2 - _line.p1).Angle();
		return { true, result.time, _ref_normal };
	}
	return {};
}

// Line

void LineCollider::Apply(const CollisionResult & result) const
{
}

CollisionResult LineCollider::Collide(const Collider& other) const
{
	return other.Collide(*this);
}

CollisionResult LineCollider::Collide(const BoxCollider& other) const
{
	return other.Collide(*this);
}

CollisionResult LineCollider::Collide(const CircleCollider& other) const
{
	return other.Collide(*this);
}

CollisionResult LineCollider::Collide(const LineCollider& other) const
{
	return CollisionResult();
}
