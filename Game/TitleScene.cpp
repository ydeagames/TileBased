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
	obj->transform()->position = Screen::Bounds().Expand(-100).GetCenter();
	obj->transform()->scale = Screen::Bounds().Expand(-100).GetSize();
	auto renderer = std::make_shared<BoxRenderer>();
	renderer->material = Material{}.SetBase(Colors::Blue, .2f).SetBorder(Colors::White, 1.f, .5f);
	obj->AddComponent<BoxRenderer>(renderer);

	auto title = GameObject::Create("Title");
	title->transform()->position = Screen::Bounds().GetCenter() + Vector2{ -100, -50 };
	title->AddNewComponent<FontTextRenderer>(GameGlobal::GetInstance().titlefont, "タイル");

	auto text5 = GameObject::Create();
	text5->transform()->position = Screen::Bounds().GetCenter() + Vector2{ -200, 50 };
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
