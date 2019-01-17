#pragma once

class Camera : public Component
{
public:
	float wheel_target = 0;
	float wheel = 0;
	float scale = 1;
	float rotation = 0;
	Vector2 offset = {};
	Vector2 offset_start = {};
	Vector2 drag_start = {};
	bool dragged = false;

public:
	static std::shared_ptr<Camera> main();

public:
	Matrix3 GetMatrix();
	Vector2 GetWorldFromScreenPosition(const Vector2& screen_point);

	void Update();
	void Render();
};
