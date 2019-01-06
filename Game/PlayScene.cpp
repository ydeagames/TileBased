#include "PlayScene.h"
#include "GameMain.h"
#include "GameGlobal.h"

class Camera : public Component
{
public:
	float wheel_target = 0;
	float wheel = 0;
	float scale = 1;
	float rotation = 0;
	Vector2 offset = {};
	Vector2 offset_start = {};
	Vector2 drag_start = {};
	bool dragged = false;

public:
	static std::shared_ptr<Camera> main();

public:
	Matrix3 GetMatrix();

	void Update();
	void Render();
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

public:
	TileRenderer() = default;
	virtual ~TileRenderer() = default;

public:
	Matrix3 GetMatrix() const;
	void Render();
};

class Entity
{
public:
	float blocks_per_sec = 4.f;

	Vector2 target_pos;
	Vector2 pos;
	Vector2 vel;

public:
	Entity() = default;
	virtual ~Entity() = default;

public:
	void Update();
	void Render(const Matrix3& matrix);
};

class EntityList : public Component
{
public:
	std::vector<std::shared_ptr<Entity>> entities;

public:
	EntityList() = default;
	virtual ~EntityList() = default;

public:
	void AddEntity(const std::shared_ptr<Entity>& entity);

	void Update();
	void Render();
};


PlayScene::PlayScene()
	: Scene()
{
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
	auto& elist = terrain->AddNewComponent<EntityList>();
	auto entity = std::make_shared<Entity>();
	entity->pos = Vector2{ 5, 5 };
	elist->AddEntity(entity);

	auto camera = GameObject::Create("MainCamera");
	camera->AddNewComponent<Camera>();
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
			Matrix3 localMatrix = Matrix3::CreateTranslation(Vector2{ ix, iy });
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

void EntityList::AddEntity(const std::shared_ptr<Entity>& entity)
{
	entities.push_back(entity);
}

void EntityList::Update()
{
	for (auto& entity : entities)
		entity->Update();
}

void EntityList::Render()
{
	auto renderer = gameObject()->GetComponent<TileRenderer>();

	Matrix3 matrix = renderer->GetMatrix();

	for (auto& entity : entities)
		entity->Render(matrix);
}

void Entity::Update()
{

}

void Entity::Render(const Matrix3& matrix)
{
	static const Quad quad =
	{ {
		Vector2{ .5f, 0.f },
		Vector2{ 1.f, .5f },
		Vector2{ .5f, 1.f },
		Vector2{ 0.f, .5f },
	} };
	Matrix3 localMatrix = Matrix3::CreateTranslation(pos);
	Graphics::DrawQuad(quad * localMatrix * matrix, Colors::Blue, true);
}

Matrix3 Camera::GetMatrix()
{
	Matrix3 m = Matrix3::CreateIdentity();
	m *= Matrix3::CreateTranslation(offset);
	m *= Matrix3::CreateScale(Vector2::one * Screen::GetBounds().GetSize().y / 480);

	// �e�X�g�R�[�h
	m *= Matrix3::CreateScale(Vector2::one * scale);
	m *= Matrix3::CreateRotationZ(rotation);

	m *= Matrix3::CreateTranslation(Screen::GetBounds().GetExtents());
	return m;
}

void Camera::Update()
{
	// �e�X�g�R�[�h
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_A))
		rotation += MathUtils::ToRadians(1);
	if (InputManager::GetInstance().key->GetButton(KEY_INPUT_D))
		rotation -= MathUtils::ToRadians(1);

	wheel_target += InputManager::GetInstance().mouse->GetDeltaWheel();
	float sub = wheel_target - wheel;
	wheel = wheel_target - sub * .8f;

	scale = std::powf(1.1f, wheel);

	if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1))
	{
		drag_start = InputManager::GetInstance().mouse->GetPosition();
		offset_start = offset;
		dragged = true;
	}
	if (dragged)
	{
		auto sub = InputManager::GetInstance().mouse->GetPosition() - drag_start;
		offset = offset_start + sub;
	}
	if (!InputManager::GetInstance().mouse->GetButton(MOUSE_INPUT_1))
	{
		dragged = false;
	}
}

void Camera::Render()
{
	DrawFormatStringF(10, 25, Colors::White, "offset (x = %.2f, y = %.2f)", offset.x, offset.y);
	DrawFormatStringF(10, 40, Colors::White, "scale (%.2f)", scale);
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
