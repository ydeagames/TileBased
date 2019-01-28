#include "Camera.h"

Matrix3 Camera::GetMatrix()
{
	Matrix3 m = Matrix3::CreateIdentity();
	m *= Matrix3::CreateTranslation(Vector2::one);
	m *= Matrix3::CreateScale(Vector2::one * Screen::GetBounds().GetSize().y / 480);
	m *= world;
	return m;
}

Vector2 Camera::GetWorldFromScreenPosition(const Vector2 & screen_point)
{
	return screen_point * GetMatrix().Inverse();
}

void Camera::Update()
{
	// テストコード
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_A))
		world *= Matrix3::CreateRotationZ(MathUtils::ToRadians(1));
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_D))
		world *= Matrix3::CreateRotationZ(MathUtils::ToRadians(-1));

	wheel_target += InputManager::GetInstance().mouse->GetDeltaWheel();
	float lastwheel = wheel;
	float sub = wheel_target - wheel;
	wheel = wheel_target - sub * .8f;
	float deltawheel = wheel - lastwheel;

	auto mouse = InputManager::GetInstance().mouse->GetPosition();
	world *= Matrix3::CreateTranslation(-mouse);
	world *= Matrix3::CreateScale(Vector2::one * std::powf(1.1f, deltawheel));
	world *= Matrix3::CreateTranslation(mouse);

	if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_2)
		|| InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_3))
	{
		drag_start = mouse;
		dragged = true;
	}
	if (dragged)
	{
		auto sub = mouse - drag_start;
		drag_start = mouse;
		world *= Matrix3::CreateTranslation(sub);
	}
	if (!(InputManager::GetInstance().mouse->GetButton(MOUSE_INPUT_2)
		|| InputManager::GetInstance().mouse->GetButton(MOUSE_INPUT_3)))
	{
		dragged = false;
	}
}

static void DrawMatrix(float x, float y, const Matrix3& m)
{
	DrawFormatStringF(x, y + 15 * 0, Colors::White, "%.2f %.2f %.2f", m(0, 0), m(1, 0), m(2, 0));
	DrawFormatStringF(x, y + 15 * 1, Colors::White, "%.2f %.2f %.2f", m(0, 1), m(1, 1), m(2, 1));
	DrawFormatStringF(x, y + 15 * 2, Colors::White, "%.2f %.2f %.2f", m(0, 2), m(1, 2), m(2, 2));
}

void Camera::Render()
{
#ifdef DEBUG
	Vector2 screen_mouse = InputManager::GetInstance().mouse->GetPosition();
	Vector2 world_mouse = GetWorldFromScreenPosition(screen_mouse);
	DrawFormatStringF(10, 55, Colors::White, "cursor (x = %.2f, y = %.2f)", world_mouse.x, world_mouse.y);

	Matrix3 m1 = GetMatrix();
	Matrix3 m2 = m1.Inverse();
	Matrix3 m3 = m2.Inverse();

	DrawMatrix(10 + 200 * 0, 70, m1);
	DrawMatrix(10 + 200 * 1, 70, m2);
	DrawMatrix(10 + 200 * 2, 70, m3);
#endif
}

std::shared_ptr<Camera> Camera::main()
{
	return GameObject::Find("MainCamera")->GetComponent<Camera>();
}
