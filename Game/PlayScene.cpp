#include "PlayScene.h"
#include "GameMain.h"
#include "GameGlobal.h"
// <ƒV[ƒ“>

class Camera : public Component
{
public:
	Matrix3 GetMatrix();

public:
	static std::shared_ptr<Camera> main();
};

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
	bool passable;

public:
	Tile(const Texture& texture, bool passable = true)
		: texture(texture)
		, passable(passable) {}
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

	void SetSpawn(const Vector2& pos);
};


PlayScene::PlayScene()
	: Scene()
{
	auto camera = GameObject::Create("MainCamera");
	camera->AddNewComponent<Camera>();

	auto terrain = GameObject::Create("Terrain");
	auto tileterrain = terrain->AddNewComponent<TileTerrain>();
	auto texture = std::make_shared<TextureResource>("Protected/Valkyrie_BG_mapChip.png");
	for (int i = 0; i < 42; i++)
	{
		std::shared_ptr<TextureResource> tiletexture = std::make_shared<TextureResource>(texture, Bounds::CreateFromSize(Vector2{18*(i % 14), 18*(i / 14) }, Vector2{ 20, 20 }).Expand(-2));
		tileterrain->RegisterTile(i, std::make_unique<Tile>(Texture{ tiletexture }, i != 40));
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
	m *= Matrix3::CreateTranslation(gameObject()->transform()->position);
	m *= gameObject()->GetComponent<Camera>()->GetMatrix();

	// TODO
	Matrix3 inv = m.Inverse();
	Vector2 lefttop = Screen::Bounds().GetMin() * inv;
	Vector2 rightbottom = Screen::Bounds().GetMax() * inv;

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

		if (!input.IsZero())
		{
			Vector2 target = target_pos + input;

			auto terrain = gameObject()->GetComponent<TileTerrain>();
			auto tile = terrain->GetTile(static_cast<int>(target.x), static_cast<int>(target.y));
			if (tile.passable)
				target_pos = target;
		}
	}

	pos = Vector2::TranslateTowards(pos, target_pos, blocks_per_sec * Time::deltaTime);

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

Matrix3 Camera::GetMatrix()
{
	Matrix3 m = Matrix3::CreateIdentity();
	//m *= Matrix3::CreateScale(Vector2::one * 2);
	m *= Matrix3::CreateTranslation(Screen::Bounds().GetExtents());
	return m;
}

std::shared_ptr<Camera> Camera::main()
{
	return GameObject::Find("MainCamera")->GetComponent<Camera>();
}
