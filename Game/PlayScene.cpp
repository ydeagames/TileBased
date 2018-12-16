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
	Vec2 tileSize = { 48, 48 };
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
	TileRenderer() = default;
	virtual ~TileRenderer() = default;

public:
	void Render();
};

class Player : public Component
{
public:
	Vec2 pos;

public:
	Player() = default;
	virtual ~Player() = default;

public:
	void Update();
};


PlayScene::PlayScene()
	: Scene()
{
	auto terrain = GameObject::Create("Terrain");
	auto tileterrain = terrain->AddNewComponent<TileTerrain>();
	std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("Protected/Valkyrie_BG_mapChip.png");
	for (int i = 0; i < 42; i++)
	{
		std::shared_ptr<TextureResource> tiletexture = std::make_shared<TextureResource>(texture, Bounds::CreateFromSize(Vec2{ 2 + (16 + 2)*(i % 14), 2 + (16 + 2)*(i / 14) }, Vec2{ 16, 16 }));
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
	Vec2 pos = gameObject()->GetComponent<Player>()->pos;
	auto terrain = gameObject()->GetComponent<TileTerrain>();
	for (int iy = 0; iy < 16; iy++)
		for (int ix = 0; ix < 16; ix++)
		{
			Quad quad = { Bounds::CreateFromSize(Vec2{ix, iy}, Vec2::one) };
			quad *= Matrix::CreateScale(terrain->tileSize);
			quad *= Matrix::CreateTranslation(gameObject()->transform()->position);
			quad *= Matrix::CreateTranslation(-pos);
			terrain->GetTile(ix, iy).Render(quad, nullptr);
		}
}

void Tile::Render(const Quad& quad, const std::unique_ptr<TileEntity>& te) const
{
	texture.Render(quad);
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
	Vec2 vel = {};
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_UP))
		vel += Vec2::up;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_DOWN))
		vel += Vec2::down;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_LEFT))
		vel += Vec2::left;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_RIGHT))
		vel += Vec2::right;
	pos += vel;
}
