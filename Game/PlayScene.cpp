#include "PlayScene.h"
#include "GameMain.h"
#include "GameGlobal.h"
#include "Camera.h"
#include "Tile.h"
#include "Entity.h"
#include "WorldRenderer.h"
#include "TileTerrainEditor.h"
#include "EntityPlacer.h"
#include "EntityAttacker.h"
#include "EntityBomb.h"
#include "EntityLaser.h"

PlayScene::PlayScene()
	: Scene()
{
	InputManager::GetInstance().mouse->Consume(MOUSE_INPUT_1);

	class Background : public Component
	{
		Texture texture = GameGlobal::GetInstance().background;

		void Update()
		{
			gameObject()->transform()->position.x = (std::sinf(Time::time) - 1) * 10;
		}

		void Render()
		{
			static const Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
			texture.Render(quad * gameObject()->transform()->GetMatrix());
		}
	};
	auto bg = GameObject::Create();
	bg->transform()->scale = Screen::GetBounds().Expand(Vector2::one * 20).GetSize();
	bg->AddNewComponent<Background>();

	auto terrain = GameObject::Create("Terrain");
	auto tileterrain = terrain->AddNewComponent<TileTerrain>();
	auto tileloader = TileLoader{ "Resources/Blocks" };
	auto tiles = tileloader.LoadAll();
	for (auto& tile : tiles)
	{
		tileterrain->tileRegistry->RegisterTile(tile->id, std::move(tile));
	}

	tileterrain->LoadChunk(ChunkPos{ 0, 0 });
	tileterrain->LoadChunk(ChunkPos{ 1, 0 });

	terrain->AddNewComponent<WorldRenderer>();

	auto& elist = terrain->AddNewComponent<EntityList>();
	auto attackertexture = Texture{ std::make_shared<TextureResource>("attacker.png") };
	elist->entityRegistry->RegisterEntity(0, [attackertexture](const TilePos& pos) {
		return std::make_shared<EntityAttacker>(attackertexture, pos);
		});
	auto bombtexture = Texture{ std::make_shared<TextureResource>("bomb.png") };
	elist->entityRegistry->RegisterEntity(1, [bombtexture](const TilePos& pos) {
		return std::make_shared<EntityBomb>(bombtexture, pos);
		});
	auto lasertexture = Texture{ std::make_shared<TextureResource>("laser.png") };
	elist->entityRegistry->RegisterEntity(2, [lasertexture](const TilePos& pos) {
		return std::make_shared<EntityLaser>(lasertexture, pos);
	});

	auto editor = GameObject::Create("TerrainEditor");
	editor->AddNewComponent<TileTerrainEditor>();

	auto placer = GameObject::Create("EntityPlacer");
	placer->AddNewComponent<EntityPlacer>();

	auto camera = GameObject::Create("MainCamera");
	camera->AddNewComponent<Camera>();
}

PlayScene::~PlayScene()
{

}
