#include "Camera.h"

Matrix3 Camera::GetMatrix()
{
	Matrix3 m = Matrix3::CreateIdentity();
	m *= Matrix3::CreateTranslation(offset);
	m *= Matrix3::CreateScale(Vector2::one * Screen::GetBounds().GetSize().y / 480);

	// テストコード
	m *= Matrix3::CreateScale(Vector2::one * scale);
	m *= Matrix3::CreateRotationZ(rotation);

	m *= Matrix3::CreateTranslation(Screen::GetBounds().GetExtents());
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
		rotation += MathUtils::ToRadians(1);
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_D))
		rotation -= MathUtils::ToRadians(1);

	wheel_target += InputManager::GetInstance().mouse->GetDeltaWheel();
	float lastwheel = wheel;
	float sub = wheel_target - wheel;
	wheel = wheel_target - sub * .8f;
	float deltawheel = wheel - lastwheel;

	scale = std::powf(1.1f, wheel);

	//{
	//	Matrix3 matrix_mul = GetMatrix();
	//	Matrix3 matrix_div = matrix_mul.Inverse();
	//	Vector2 mouse_pos1 = InputManager::GetInstance().mouse->GetPosition();
	//	Vector2 mouse_pos2 = mouse_pos1 * matrix_div;
	//	Vector2 mouse_pos3 = mouse_pos2 * deltawheel;
	//	offset += mouse_pos3;
	//}
	//offset = mouse_pos;

	if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1))
	{
		drag_start = InputManager::GetInstance().mouse->GetPosition();
		offset_start = offset;
		dragged = true;
	}
	if (dragged)
	{
		auto sub = InputManager::GetInstance().mouse->GetPosition() - drag_start;
		offset = offset_start + sub / scale;
	}
	if (!InputManager::GetInstance().mouse->GetButton(MOUSE_INPUT_1))
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
	DrawFormatStringF(10, 25, Colors::White, "offset (x = %.2f, y = %.2f)", offset.x, offset.y);
	DrawFormatStringF(10, 40, Colors::White, "scale (%.2f)", scale);
	Vector2 screen_mouse = InputManager::GetInstance().mouse->GetPosition();
	Vector2 world_mouse = GetWorldFromScreenPosition(screen_mouse);
	DrawFormatStringF(10, 55, Colors::White, "cursor (x = %.2f, y = %.2f)", world_mouse.x, world_mouse.y);

	Matrix3 m1 = GetMatrix();
	Matrix3 m2 = m1.Inverse();
	Matrix3 m3 = m2.Inverse();

	DrawMatrix(10 + 200 * 0, 70, m1);
	DrawMatrix(10 + 200 * 1, 70, m2);
	DrawMatrix(10 + 200 * 2, 70, m3);
}

std::shared_ptr<Camera> Camera::main()
{
	return GameObject::Find("MainCamera")->GetComponent<Camera>();
}
