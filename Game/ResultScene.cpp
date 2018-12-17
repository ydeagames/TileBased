#include "ResultScene.h"
#include "GameMain.h"
#include "GameGlobal.h"

// <シーン>

ResultScene::ResultScene()
	: Scene()
{
	SetMouseDispFlag(true);

	auto& font = GameGlobal::GetInstance().font;

	auto obj = GameObject::Create();
	obj->transform()->position = Screen::Bounds().Expand(-200).GetCenter();
	obj->transform()->scale = Screen::Bounds().Expand(-200).GetSize();
	auto renderer = std::make_shared<BoxRenderer>();
	renderer->material = Material{}.SetBase(Colors::Blue, .2f).SetBorder(Colors::White, 1.f, .5f);
	obj->AddComponent<BoxRenderer>(renderer);

	auto title = GameObject::Create("Title");
	title->transform()->position = Screen::Bounds().GetCenter() + Vector2{ -250, -100 };
	title->AddNewComponent<FontTextRenderer>(GameGlobal::GetInstance().titlefont, "リザルト");

	auto director = GameObject::Create("GameDirector");
	class GameDirector : public Component
	{
		void Update()
		{
			if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1) || InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_SPACE))
				SceneManager::GetInstance().RequestScene(SceneID::TITLE);
		}
	};
	director->AddNewComponent<GameDirector>();
}

ResultScene::~ResultScene()
{

}
