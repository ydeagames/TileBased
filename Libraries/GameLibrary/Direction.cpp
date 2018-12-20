#include "Direction.h"
#include "MathUtils.h"

const Direction Directions::Values[9] =
{
	{ 0, Vector2::up, &Directions::South },
	{ 1, Vector2::up + Vector2::right, &Directions::SouthWest },
	{ 2, Vector2::right, &Directions::West },
	{ 3, Vector2::down + Vector2::right, &Directions::NorthWest },
	{ 4, Vector2::down, &Directions::North },
	{ 5, Vector2::down + Vector2::left, &Directions::NorthEast },
	{ 6, Vector2::left, &Directions::East },
	{ 7, Vector2::up + Vector2::left, &Directions::SouthEast },
	{ -1, Vector2::zero, nullptr },
};

const Direction& Directions::North		= Directions::Values[0];
const Direction& Directions::NorthEast	= Directions::Values[1];
const Direction& Directions::East		= Directions::Values[2];
const Direction& Directions::SouthEast	= Directions::Values[3];
const Direction& Directions::South		= Directions::Values[4];
const Direction& Directions::SouthWest	= Directions::Values[5];
const Direction& Directions::West		= Directions::Values[6];
const Direction& Directions::NorthWest	= Directions::Values[7];
const Direction& Directions::None		= Directions::Values[8];

const Direction& Direction::operator+(const Direction& other) const
{
	if (id == -1)
		return other;
	if (other.id == -1)
		return *this;
	int diff = MathUtils::Loop(other.id - id, -3, 5);
	if (diff == 4)
		return Directions::None;
	int newid = MathUtils::Loop(id + diff / 2, 8);
	return Directions::Values[newid];
}
