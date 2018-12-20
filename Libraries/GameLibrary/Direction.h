#pragma once

class Directions;

class Direction final
{
public:
	const int id;
	const Vector2 pos;
	const Direction* opposite;

private:
	Direction(int id, const Vector2& pos, const Direction* opposite)
		: id(id)
		, pos(pos)
		, opposite(opposite) {}
	friend class Directions;

private:
	Direction(const Direction &) = delete;
	Direction& operator=(const Direction &) = delete;
	Direction(Direction &&) = delete;
	Direction& operator=(Direction &&) = delete;

public:
	bool has(const Direction& other) const;
	const Direction& operator+(const Direction& other) const;
	friend const Direction& operator+=(const Direction*& base, const Direction& other) { return *(base = &(*base + other)); };
	inline const Direction& operator-() const { return *opposite; }
	inline const bool operator==(const Direction& other) const { return id == other.id; }
};

class Directions final
{
private:
	friend class Direction;

private:
	static const Direction Values[9];

public:
	static const Direction& None;
	static const Direction& North;
	static const Direction& NorthEast;
	static const Direction& East;
	static const Direction& SouthEast;
	static const Direction& South;
	static const Direction& SouthWest;
	static const Direction& West;
	static const Direction& NorthWest;
};