#include "TitleScene.h"
#include "GameMain.h"
#include "GameGlobal.h"

// <シーン>

TitleScene::TitleScene()
	: Scene()
{
	SetMouseDispFlag(true);

	auto& font = GameGlobal::GetInstance().font;

	auto obj = GameObject::Create();
	obj->transform()->position = SCREEN.Expand(-200).GetCenter();
	obj->transform()->scale = SCREEN.Expand(-200).GetSize();
	auto renderer = std::make_shared<BoxRenderer>();
	renderer->material = Material{}.SetBase(Colors::Blue, .2f).SetBorder(Colors::White, 1.f, .5f);
	obj->AddComponent<BoxRenderer>(renderer);

	auto title = GameObject::Create("Title");
	title->transform()->position = SCREEN.GetCenter() + Vec2{ -250, -100 };
	title->AddNewComponent<FontTextRenderer>(GameGlobal::GetInstance().titlefont, "360°ブロック崩し");

	int deltay = 36;
	int posy = -deltay;

	auto text1 = GameObject::Create();
	text1->transform()->position = SCREEN.GetCenter() + Vec2{ -200, posy += deltay };
	text1->AddNewComponent<FontTextRenderer>(font, "矢印キーやWASDキーでパドル移動！");
	auto text2 = GameObject::Create();
	text2->transform()->position = SCREEN.GetCenter() + Vec2{ -200, posy += deltay };
	text2->AddNewComponent<FontTextRenderer>(font, "マウス横移動やQEキーでパドル回転！");
	auto text3 = GameObject::Create();
	text3->transform()->position = SCREEN.GetCenter() + Vec2{ -200, posy += deltay };
	text3->AddNewComponent<FontTextRenderer>(font, "パドルがブロックに触れると即死");
	auto text4 = GameObject::Create();
	text4->transform()->position = SCREEN.GetCenter() + Vec2{ -200, posy += deltay };
	text4->AddNewComponent<FontTextRenderer>(font, "30秒以内にスコアを稼げ！");
	auto text5 = GameObject::Create();
	text5->transform()->position = SCREEN.GetCenter() + Vec2{ -200, posy += deltay };
	text5->AddNewComponent<FontTextRenderer>(font, "クリックかスペースキーでスタート！");

	auto director = GameObject::Create("GameDirector");
	class GameDirector : public Component
	{
		void Update()
		{
			if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1) || InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_SPACE))
				SceneManager::GetInstance().RequestScene(SceneID::PLAY);
		}
	};
	director->AddNewComponent<GameDirector>();
}

TitleScene::~TitleScene()
{

}
