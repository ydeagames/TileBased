#include "AspectUtils.h"

namespace AspectUtils
{
	Vector2 Raw(Vector2 size, Vector2 maxsize) {
		return size;
	}

	Vector2 Max(Vector2 size, Vector2 maxsize) {
		return maxsize;
	}

	Vector2 Width(Vector2 size, Vector2 maxsize) {
		return{ maxsize.x, size.y*maxsize.x / size.x };
	}

	Vector2 Height(Vector2 size, Vector2 maxsize) {
		return{ size.x*maxsize.y / size.y, maxsize.y };
	}

	Vector2 Inner(Vector2 size, Vector2 maxsize) {
		if (size.x < 0)
			maxsize.x *= -1;
		if (size.y < 0)
			maxsize.y *= -1;
		boolean b = size.x / maxsize.x > size.y / maxsize.y;
		return{ b ? maxsize.x : size.x*maxsize.y / size.y, b ? size.y*maxsize.x / size.x : maxsize.y };
	}

	Vector2 Outer(Vector2 size, Vector2 maxsize) {
		if (size.x < 0)
			maxsize.x *= -1;
		if (size.y < 0)
			maxsize.y *= -1;
		boolean b = size.x / maxsize.x < size.y / maxsize.y;
		return{ b ? maxsize.x : size.x*maxsize.y / size.y, b ? size.y*maxsize.x / size.x : maxsize.y };
	}

	Vector2 WidthLimit(Vector2 size, Vector2 maxsize) {
		if (size.x < maxsize.x)
			return size;
		else
			return{ maxsize.x, maxsize.x*size.y / size.x };
	}

	Vector2 HeightLimit(Vector2 size, Vector2 maxsize) {
		if (size.y < maxsize.y)
			return size;
		else
			return{ maxsize.y*size.x / size.y, maxsize.y };
	}

	Vector2 Limit(Vector2 size, Vector2 maxsize) {
		if (size.x > size.y)
			if (size.x < maxsize.x)
				return size;
			else
				return{ maxsize.x, maxsize.x*size.y / size.x };
		else if (size.y < maxsize.y)
			return size;
		else
			return{ maxsize.y*size.x / size.y, maxsize.y };
	}
}