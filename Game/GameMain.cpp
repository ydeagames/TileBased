#include "GameMain.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

// <Gameクラス>

// ゲームの初期化処理
Game::Game() :
	m_frame_timer(new FrameTimer)
{
	Time::GetInstance().InitializeTime();

	SceneManager& scene_manager = SceneManager::GetInstance();

	scene_manager.AddScene<LogoScene>(SceneID::LOGO);
	scene_manager.AddScene<TitleScene>(SceneID::TITLE);
	scene_manager.AddScene<PlayScene>(SceneID::PLAY);
	scene_manager.AddScene<ResultScene>(SceneID::RESULT);

	scene_manager.SetStartScene(SceneID::LOGO);
}

// ゲームの終了処理
Game::~Game()
{
	delete m_frame_timer;
}

// ゲームの更新処理
void Game::Update(void)
{
	m_frame_timer->Update();
	Timer::Tick();
	Time::GetInstance().UpdateTime();

	InputManager::GetInstance().Update();

	SceneManager::GetInstance().UpdateActiveScene();
}

// ゲームの描画処理
void Game::Render(void)
{
	SceneManager::GetInstance().RenderActiveScene();

#ifdef _DEBUG
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());
#endif
}
