#include "LogoScene.h"
#include "GameMain.h"
#include "GameGlobal.h"

// <ƒV[ƒ“>

LogoScene::LogoScene()
	: Scene()
{
	class Background : public Component
	{
		Texture texture = GameGlobal::GetInstance().movie;

		Timer timer;

		void Start()
		{
			timer = Timer{}.Start(3);
			PlayMovieToGraph(texture.texture->GetResource());
		}

		void Update()
		{
			if (timer.IsFinished() || (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1) || InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_SPACE)))
			{
				PlaySoundMem(GameGlobal::GetInstance().se01->GetResource(), DX_PLAYTYPE_BACK);
				SceneManager::GetInstance().RequestScene(SceneID::TITLE);
			}
		}

		void Render()
		{
			static const Quad quad = { Bounds::CreateFromSize(Vector2::zero, Vector2::one) };
			texture.Render(quad * gameObject()->transform()->GetMatrix());
		}
	};
	auto bg = GameObject::Create();
	bg->transform()->scale = Screen::GetBounds().Expand(Vector2::one).GetSize();
	bg->AddNewComponent<Background>();
}

LogoScene::~LogoScene()
{
}
