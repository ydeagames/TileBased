#include "PlayScene.h"
#include "GameMain.h"
#include "GameGlobal.h"
// <ƒV[ƒ“>

class TileEntity
{
public:

public:
	TileEntity() = default;
	virtual ~TileEntity() = default;

public:
};

class Tile
{
public:
	Texture texture;

public:
	Tile(const Texture& texture)
		: texture(texture) {}
	virtual ~Tile() = default;

public:
	void Render(const Quad& quad, const std::unique_ptr<TileEntity>& te) const;
};

class TileTerrain : public Component
{
public:
	std::unique_ptr<Tile> defaultTile = std::make_unique<Tile>(Texture{ TextureResource::GetMissingTexture() });
	std::unordered_map<int, std::unique_ptr<Tile>> tileRegistry;
	std::unordered_map<int, std::unordered_map<int, int>> tileMap;

public:
	TileTerrain() = default;
	virtual ~TileTerrain() = default;

public:
	const Tile& GetTile(int x, int y);
	void RegisterTile(int id, std::unique_ptr<Tile>&& tile);
};

class TileRenderer : public Component
{
public:
	Vector2 tileSize = { 48, 48 };
	Vector2 offset = {};

public:
	TileRenderer() = default;
	virtual ~TileRenderer() = default;

public:
	Matrix3 GetMatrix() const;
	void Render();
};

class Player : public Component
{
public:
	float blocks_per_sec = 4.f;

	Vector2 target_pos;
	Vector2 pos;
	Vector2 vel;

public:
	Player() = default;
	virtual ~Player() = default;

public:
	void Update();
	void Render();
};


PlayScene::PlayScene()
	: Scene()
{
	auto terrain = GameObject::Create("Terrain");
	auto tileterrain = terrain->AddNewComponent<TileTerrain>();
	std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("Protected/Valkyrie_BG_mapChip.png");
	for (int i = 0; i < 42; i++)
	{
		std::shared_ptr<TextureResource> tiletexture = std::make_shared<TextureResource>(texture, Bounds::CreateFromSize(Vector2{18*(i % 14), 18*(i / 14) }, Vector2{ 20, 20 }).Expand(-2));
		tileterrain->RegisterTile(i, std::make_unique<Tile>(Texture{ tiletexture }));
	}

	int map[16][16] = {
		{40,40,40,40,40,40,40,40,40,40,40,40,40,40,40, 0, },
		{40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,40, 0, 0, },
		{40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,40, 0, 0, },
		{40, 0, 0, 0, 0,36,37, 0, 0, 0, 0, 0, 0,40, 0, 0, },
		{40, 0, 0, 0, 0,38,39, 0, 0, 0, 0, 0, 0,40, 0, 0, },
		{40, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,40, 0, 0, },
		{40, 0,14,15,16, 0, 0, 0, 0, 0, 0, 0, 0,40, 0, 0, },
		{40, 0,17,18,19, 0, 0, 0, 0, 0, 0, 0, 0,40, 0, 0, },
		{40, 0,20,21,22, 0, 0, 0, 0, 0, 0, 0, 0,40, 0, 0, },
		{40, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{40,40,40,40,40,40,40,40,40,40,40,40,40,40, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 0,40,40,40,40,40,40,40,40,40,40,40,40,40, 0, 0, },
		{ 0,40,40,40,40,40,40,40,40,40,40,40,40,40, 0, 0, },
	};
	for (int iy = 0; iy < 16; iy++)
		for (int ix = 0; ix < 16; ix++)
			tileterrain->tileMap[iy][ix] = map[iy][ix];
	terrain->AddNewComponent<TileRenderer>();
	terrain->AddNewComponent<Player>();
}

PlayScene::~PlayScene()
{

}

void TileRenderer::Render()
{
	auto terrain = gameObject()->GetComponent<TileTerrain>();
	Matrix3 matrix = GetMatrix();

	for (int iy = 0; iy < 16; iy++)
		for (int ix = 0; ix < 16; ix++)
		{
			Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
			Matrix3 localMatrix = Matrix3::CreateIdentity();
			localMatrix *= Matrix3::CreateTranslation(Vector2{ ix, iy });
			terrain->GetTile(ix, iy).Render(quad * localMatrix * matrix, nullptr);
		}
}

void Tile::Render(const Quad& quad, const std::unique_ptr<TileEntity>& te) const
{
	texture.Render(quad);
}

Matrix3 TileRenderer::GetMatrix() const
{
	Matrix3 m = Matrix3::CreateIdentity();
	m *= Matrix3::CreateTranslation(offset);
	m *= Matrix3::CreateTranslation(-Vector2::one * .5f);
	m *= Matrix3::CreateScale(tileSize);
	m *= Matrix3::CreateTranslation(SCREEN.GetExtents());
	m *= Matrix3::CreateTranslation(gameObject()->transform()->position);

	// TODO
	Matrix3 inv = m.Inverse();
	Vector2 lefttop = SCREEN.GetMin() * inv;
	Vector2 rightbottom = SCREEN.GetMax() * inv;

	return m;
}

const Tile& TileTerrain::GetTile(int x, int y)
{
	auto& tile = tileRegistry[tileMap[y][x]];
	if (tile)
		return *tile;
	return *defaultTile;
}

void TileTerrain::RegisterTile(int id, std::unique_ptr<Tile>&& tile)
{
	tileRegistry[id] = std::move(tile);
}

void Player::Update()
{
	if (pos.Equals(target_pos))
	{
		Vector2 input = {};
		if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_UP))
			input += Vector2::up;
		if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_DOWN))
			input += Vector2::down;
		if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_LEFT))
			input += Vector2::left;
		if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_RIGHT))
			input += Vector2::right;
		target_pos += input;
	}

	Vector2 sub = target_pos - pos;
	Vector2 vel = sub.Normalized() * blocks_per_sec * Time::deltaTime;
	pos += (vel.LengthSquared() < sub.LengthSquared()) ? vel : sub;

	gameObject()->GetComponent<TileRenderer>()->offset = -pos;
}

void Player::Render()
{
	auto terrain = gameObject()->GetComponent<TileTerrain>();
	auto renderer = gameObject()->GetComponent<TileRenderer>();

	Matrix3 matrix = renderer->GetMatrix();

	Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
	Matrix3 localMatrix = Matrix3::CreateIdentity();
	localMatrix *= Matrix3::CreateTranslation(pos);
	terrain->tileRegistry[0]->Render(quad * localMatrix * matrix, nullptr);
}
