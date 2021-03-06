#include "ResultScene.h"
#include "GameMain.h"
#include "GameGlobal.h"

// <シーン>

ResultScene::ResultScene()
	: Scene()
{
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
	bg->transform()->scale = Screen::GetBounds().Expand(Vector2::one * 20).GetSize();
	bg->AddNewComponent<Background>();

	auto obj = GameObject::Create();
	obj->transform()->position = Screen::GetBounds().Expand(-200).GetCenter();
	obj->transform()->scale = Screen::GetBounds().Expand(-200).GetSize();
	auto renderer = std::make_shared<BoxRenderer>();
	renderer->material = Material{}.SetBase(Colors::Blue, .2f).SetBorder(Colors::White, 1.f, .5f);
	obj->AddComponent<BoxRenderer>(renderer);

	auto title = GameObject::Create("Title");
	title->transform()->position = Screen::GetBounds().GetCenter() + Vector2{ -350, -100 };
	title->AddNewComponent<FontTextRenderer>(GameGlobal::GetInstance().titlefont, "クリアおめでとうございます！");

	auto text5 = GameObject::Create();
	text5->transform()->position = Screen::GetBounds().GetCenter() + Vector2{ -350, 50 };
	text5->AddNewComponent<FontTextRenderer>(font, "(エディットモード: F3キーを押せばマップを編集することができます。)");

	auto director = GameObject::Create("GameDirector");
	class GameDirector : public Component
	{
		void Update()
		{
			if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1) || InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_SPACE))
			{
				PlaySoundMem(GameGlobal::GetInstance().se01->GetResource(), DX_PLAYTYPE_BACK);
				SceneManager::GetInstance().RequestScene(SceneID::TITLE);
			}
		}
	};
	director->AddNewComponent<GameDirector>();
}

ResultScene::~ResultScene()
{

}
