#include "WorldRenderer.h"
#include "Camera.h"
#include "Tile.h"
#include "Entity.h"

Matrix3 WorldRenderer::GetMatrix() const
{
	Matrix3 m = Matrix3::CreateIdentity();
	m *= Matrix3::CreateTranslation(-Vector2::one * .5f);
	m *= Matrix3::CreateScale(tileSize);
	m *= Matrix3::CreateTranslation(gameObject()->transform()->position);
	m *= Camera::main()->GetMatrix();

	// TODO
	Matrix3 inv = m.Inverse();
	Vector2 lefttop = Screen::GetBounds().GetMin() * inv;
	Vector2 rightbottom = Screen::GetBounds().GetMax() * inv;

	return m;
}

void WorldRenderer::Render()
{
	Matrix3 world = GetMatrix();
	auto tile = gameObject()->GetComponent<TileTerrain>();
	tile->Render(world);
	auto entity = gameObject()->GetComponent<EntityList>();
	entity->Render(world);
}
