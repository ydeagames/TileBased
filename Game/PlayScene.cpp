#include "PlayScene.h"
#include "GameMain.h"
#include "GameGlobal.h"

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
	void Render(const Matrix3& matrix, const std::unique_ptr<TileEntity>& te) const;
};

class TileRegistry
{
public:
	std::unique_ptr<Tile> defaultTile = std::make_unique<Tile>(Texture{ TextureResource::GetMissingTexture() });
	std::unordered_map<int, std::unique_ptr<Tile>> tiles;

public:
	void RegisterTile(int id, std::unique_ptr<Tile>&& tile);

public:
	const Tile& GetTile(int id);
};

class TileChunk
{
public:
	static const int ChunkSize = 16;

public:
	std::array<std::array<int, ChunkSize>, ChunkSize> data;

public:
	int& GetTile(int x, int y);
	void Render(const std::unique_ptr<TileRegistry>& registry, const Matrix3& matrix) const;
};

class TileTerrain : public Component
{
public:
	std::unique_ptr<TileRegistry> tileRegistry;
	std::unordered_map<int, std::unordered_map<int, TileChunk>> tileMap;

public:
	TileTerrain();
	virtual ~TileTerrain() = default;

public:
	int& GetTile(int x, int y);
	TileChunk& GetChunk(int x, int y);
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

	int direction;
	Vector2 pos;
	Vector2 vel;

public:
	Player() = default;
	virtual ~Player() = default;

public:
	void Update();
	void Render();

	void SetSpawn(const Vector2& newpos);
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
		std::shared_ptr<TextureResource> tiletexture = std::make_shared<TextureResource>(texture, Bounds::CreateFromSize(Vector2{ 18 * (i % 14), 18 * (i / 14) }, Vector2{ 20, 20 }).Expand(-2));
		tileterrain->tileRegistry->RegisterTile(i, std::make_unique<Tile>(Texture{ tiletexture }, i != 40));
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
			tileterrain->GetTile(ix, iy) = map[iy][ix];

	terrain->AddNewComponent<TileRenderer>();
	terrain->AddNewComponent<Player>()->SetSpawn(Vector2{ 5, 5 });
}

PlayScene::~PlayScene()
{

}

void TileRenderer::Render()
{
	auto terrain = gameObject()->GetComponent<TileTerrain>();
	Matrix3 matrix = GetMatrix();

	for (int iy = 0; iy < 16; iy += TileChunk::ChunkSize)
		for (int ix = 0; ix < 16; ix += TileChunk::ChunkSize)
		{
			Matrix3 localMatrix = Matrix3::CreateIdentity();
			localMatrix *= Matrix3::CreateTranslation(Vector2{ ix, iy });
			terrain->GetChunk(ix, iy).Render(terrain->tileRegistry, localMatrix * matrix);
		}
}

void Tile::Render(const Matrix3& matrix, const std::unique_ptr<TileEntity>& te) const
{
	static const Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
	texture.Render(quad * matrix);
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
	Vector2 lefttop = Screen::GetBounds().GetMin() * inv;
	Vector2 rightbottom = Screen::GetBounds().GetMax() * inv;

	return m;
}

const Tile& TileRegistry::GetTile(int id)
{
	auto& tile = tiles[id];
	if (tile)
		return *tile;
	return *defaultTile;
}

void TileRegistry::RegisterTile(int id, std::unique_ptr<Tile>&& tile)
{
	tiles[id] = std::move(tile);
}

// テストコード
static float scale = 1;
static float rotation = 0;

void Player::Update()
{
	// テストコード
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_W))
		scale *= 1.001f;
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_S))
		scale /= 1.001f;
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_A))
		rotation += MathUtils::ToRadians(1);
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_D))
		rotation -= MathUtils::ToRadians(1);

	/*
	static bool XFlag = false;
	Vector2 input = {};
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_UP))
		input += Vector2::up;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_DOWN))
		input += Vector2::down;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_LEFT))
		input += Vector2::left;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_RIGHT))
		input += Vector2::right;
	if (XFlag)
	{
		if (pos.IsSnappedX() && !input.IsZeroX())
		{
			auto terrain = gameObject()->GetComponent<TileTerrain>();

			Vector2 next;
			next = (target_pos + input).Snap();
			if (!terrain->tileRegistry->GetTile(terrain->GetTile(next.X(), target_pos.Y())).passable)
				input.x = 0;
			next = (target_pos + input).Snap();
			target_pos = next;
		}
		if (!input.IsZeroY())
		{
			XFlag = false;
		}

	}
	else
	{
		if (pos.IsSnappedY() && !input.IsZeroY())
		{
			auto terrain = gameObject()->GetComponent<TileTerrain>();

			Vector2 next;
			next = (target_pos + input).Snap();
			if (!terrain->tileRegistry->GetTile(terrain->GetTile(target_pos.X(), next.Y())).passable)
				input.y = 0;
			next = (target_pos + input).Snap();
			target_pos = next;
		}
		if (!input.IsZeroX())
		{
			XFlag = true;
		}

	}

	if (!input.IsZeroX())
		pos = Vector2::TranslateTowards(pos, target_pos, blocks_per_sec * Time::deltaTime);
	else if (!input.IsZeroY())
		pos = Vector2::TranslateTowards(pos, target_pos, blocks_per_sec * Time::deltaTime);

	/**/

	auto terrain = gameObject()->GetComponent<TileTerrain>();

	const Direction* direction = &Directions::None;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_UP))
		direction += Directions::North;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_DOWN))
		direction += Directions::South;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_LEFT))
		direction += Directions::West;
	if (InputManager::GetInstance().joypad->GetButton(PAD_INPUT_RIGHT))
		direction += Directions::East;

	Vector2 vel = direction->pos;
	Vector2 grid_min = (pos + vel).Snap(std::floor);
	Vector2 grid_max = (pos + vel).Snap(std::ceil);
	if (direction->has(Directions::North))
	{
		bool hit1 = terrain->tileRegistry->GetTile(terrain->GetTile(grid_min.X(), grid_min.Y())).passable;
		bool hit2 = terrain->tileRegistry->GetTile(terrain->GetTile(grid_max.X(), grid_min.Y())).passable;
		if (hit1 && hit2)
		{
			pos.y = grid_max.y + 1;
			vel.y = 0;
		}
	}

	pos += vel;
	gameObject()->GetComponent<TileRenderer>()->offset = -pos;
}

void Player::Render()
{
	DrawFormatStringF(10, 25, Colors::White, "pos (x = %.2f, y = %.2f)", pos.x, pos.y);

		auto terrain = gameObject()->GetComponent<TileTerrain>();
	auto renderer = gameObject()->GetComponent<TileRenderer>();

	Matrix3 matrix = renderer->GetMatrix();

	Matrix3 localMatrix = Matrix3::CreateIdentity();
	localMatrix *= Matrix3::CreateTranslation(pos);
	terrain->tileRegistry->GetTile(0).Render(localMatrix * matrix, nullptr);
}

void Player::SetSpawn(const Vector2 & newpos)
{
	pos = newpos;
	//target_pos = newpos.Snap();
}

Matrix3 Camera::GetMatrix()
{
	Matrix3 m = Matrix3::CreateIdentity();
	m *= Matrix3::CreateScale(Vector2::one * Screen::GetBounds().GetSize().y / 480);

	// テストコード
	m *= Matrix3::CreateScale(Vector2::one * scale);
	m *= Matrix3::CreateRotationZ(rotation);

	m *= Matrix3::CreateTranslation(Screen::GetBounds().GetExtents());
	return m;
}

std::shared_ptr<Camera> Camera::main()
{
	return GameObject::Find("MainCamera")->GetComponent<Camera>();
}

int& TileChunk::GetTile(int x, int y)
{
	return data[((y % ChunkSize) + ChunkSize) % ChunkSize][((x % ChunkSize) + ChunkSize) % ChunkSize];
}

void TileChunk::Render(const std::unique_ptr<TileRegistry>& registry, const Matrix3 & matrix) const
{
	int iy = 0;
	for (auto& line : data)
	{
		int ix = 0;
		for (auto& tile : line)
		{
			registry->tiles[tile]->Render(Matrix3::CreateTranslation(Vector2{ ix,iy }) * matrix, nullptr);
			ix++;
		}
		iy++;
	}
}

TileTerrain::TileTerrain()
	: tileRegistry(std::make_unique<TileRegistry>())
{
}

int& TileTerrain::GetTile(int x, int y)
{
	return GetChunk(x, y).GetTile(x, y);
}

TileChunk& TileTerrain::GetChunk(int x, int y)
{
	return tileMap[y / TileChunk::ChunkSize][x / TileChunk::ChunkSize];
}
