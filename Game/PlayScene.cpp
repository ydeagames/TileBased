#include "PlayScene.h"
#include "GameMain.h"
#include "GameGlobal.h"
// <ƒV[ƒ“>

class Tile
{
public:
	Tile() = default;
	virtual ~Tile() = default;

public:
	void Render();
};

class TileTerrain
{
public:
	TileTerrain() = default;
	virtual ~TileTerrain() = default;

public:

};

class TileRenderer : public Component
{
private:
	std::shared_ptr<TileTerrain> terrain;

public:
	TileRenderer(const std::shared_ptr<TileTerrain>& terrain)
		: terrain(terrain) {}
	virtual ~TileRenderer() = default;
};


PlayScene::PlayScene()
	: Scene()
{
}

PlayScene::~PlayScene()
{

}

