#pragma once

namespace AspectUtils
{
	Vector2 Raw(Vector2 size, Vector2 maxsize);
	Vector2 Max(Vector2 size, Vector2 maxsize);
	Vector2 Width(Vector2 size, Vector2 maxsize);
	Vector2 Height(Vector2 size, Vector2 maxsize);
	Vector2 Inner(Vector2 size, Vector2 maxsize);
	Vector2 Outer(Vector2 size, Vector2 maxsize);
	Vector2 WidthLimit(Vector2 size, Vector2 maxsize);
	Vector2 HeightLimit(Vector2 size, Vector2 maxsize);
	Vector2 Limit(Vector2 size, Vector2 maxsize);
}