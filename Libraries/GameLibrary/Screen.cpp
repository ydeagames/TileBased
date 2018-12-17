#include "Screen.h"

void Screen::SetTitle(const std::string & newtitle)
{
	SetMainWindowText(newtitle.c_str());
}

Vector2 Screen::GetSize()
{
	int WindowW, WindowH;
	GetWindowSize(&WindowW, &WindowH);
	return { WindowW, WindowH };
}

void Screen::SetSize(const Vector2 & newsize)
{
	SetWindowSize(static_cast<int>(newsize.x), static_cast<int>(newsize.y));
}

Vector2 Screen::GetDisplaySize()
{
	int DesktopW, DesktopH;
	GetDefaultState(&DesktopW, &DesktopH, nullptr);
	return { DesktopW, DesktopH };
}

void Screen::SetScreenSize(const Vector2 & newsize)
{
	SetGraphMode(static_cast<int>(newsize.x), static_cast<int>(newsize.y), 32);
}

void Screen::SetLocation(const Vector2 & newsize)
{
	SetWindowPosition(static_cast<int>(newsize.x), static_cast<int>(newsize.y));
}

void Screen::SetLocationRelativeTo()
{
	SetLocation((GetDisplaySize() - GetSize()) / 2);
}

Bounds Screen::GetBounds()
{
	return Bounds::CreateFromSize(Vector2::zero, GetSize());
}
