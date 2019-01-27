#include "TitleScene.h"
#include "GameMain.h"
#include "GameGlobal.h"

// <シーン>

TitleScene::TitleScene()
	: Scene()
{
	SetMouseDispFlag(true);

	auto& font = GameGlobal::GetInstance().font;

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
	bg->transform()->scale = Screen::GetBounds().Expand(Vector2::one *20).GetSize();
	bg->AddNewComponent<Background>();

	auto obj = GameObject::Create();
	obj->transform()->position = Screen::GetBounds().Expand(-100).GetCenter();
	obj->transform()->scale = Screen::GetBounds().Expand(-100).GetSize();
	auto renderer = std::make_shared<BoxRenderer>();
	renderer->material = Material{}.SetBase(Colors::Blue, .2f).SetBorder(Colors::White, 1.f, .5f);
	obj->AddComponent<BoxRenderer>(renderer);

	class Icon : public Component
	{
		Texture texture = GameGlobal::GetInstance().icon;

		void Render()
		{
			static const Quad quad = { Bounds::CreateFromSize(Vector2{ -.5f, -1.f }, Vector2::one) };
			texture.Render(quad * gameObject()->transform()->GetMatrix());
		}
	};
	auto icon = GameObject::Create();
	icon->transform()->position = Screen::GetBounds().GetCenter() + Vector2{ 0, -50 };
	icon->transform()->scale = Vector2::one * 300;
	icon->AddNewComponent<Icon>();

	auto title = GameObject::Create("Title");
	title->transform()->position = Screen::GetBounds().GetCenter() + Vector2{ -100, -50 };
	title->AddNewComponent<FontTextRenderer>(GameGlobal::GetInstance().titlefont, "鉄壁城");

	auto text4 = GameObject::Create();
	text4->transform()->position = Screen::GetBounds().GetCenter() + Vector2{ -200, 50 };
	text4->AddNewComponent<FontTextRenderer>(font, "右ドラッグで視界移動\n左クリックでオブジェクト選択/配置");

	auto text5 = GameObject::Create();
	text5->transform()->position = Screen::GetBounds().GetCenter() + Vector2{ -200, 150 };
	text5->AddNewComponent<FontTextRenderer>(font, "クリックかスペースキーでスタート！");

	auto director = GameObject::Create("GameDirector");
	class GameDirector : public Component
	{
		void Update()
		{
			if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1) || InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_SPACE))
			{
				PlaySoundMem(GameGlobal::GetInstance().se01->GetResource(), DX_PLAYTYPE_BACK);
				SceneManager::GetInstance().RequestScene(SceneID::PLAY);
			}
		}
	};
	director->AddNewComponent<GameDirector>();
}

TitleScene::~TitleScene()
{

}
