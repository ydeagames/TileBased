#pragma once

namespace Screen
{
	void SetTitle(const std::string& newtitle);

	Vector2 GetSize();
	void SetSize(const Vector2& newsize);
	Vector2 GetDisplaySize();
	void SetScreenSize(const Vector2& newsize);

	void SetLocation(const Vector2& newsize);
	void SetLocationRelativeTo();

	Bounds GetBounds();
}