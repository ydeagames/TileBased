#include "PlayScene.h"
#include "GameMain.h"
#include "GameGlobal.h"
#include "Camera.h"
#include "Tile.h"
#include "Entity.h"
#include "WorldRenderer.h"
#include "TileTerrainEditor.h"
#include "EntityPlacer.h"

PlayScene::PlayScene()
	: Scene()
{
	InputManager::GetInstance().mouse->Consume(MOUSE_INPUT_1);

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
	elist->entityRegistry->RegisterEntity(0, []() {
			return std::make_shared<Entity>();
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
