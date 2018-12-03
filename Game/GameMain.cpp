#include "GameMain.h"
#include <cmath>
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

// <Game�N���X>

// �Q�[���̏���������
Game::Game() :
	m_frame_timer(new FrameTimer)
{
	SceneManager& scene_manager = SceneManager::GetInstance();

	scene_manager.AddScene<TitleScene>(SceneID::LOGO);
	scene_manager.AddScene<TitleScene>(SceneID::TITLE);
	scene_manager.AddScene<PlayScene>(SceneID::PLAY);
	scene_manager.AddScene<ResultScene>(SceneID::RESULT);

	scene_manager.SetStartScene(SceneID::LOGO);
}

// �Q�[���̏I������
Game::~Game()
{
	delete m_frame_timer;
}

// �Q�[���̍X�V����
void Game::Update(void)
{
	m_frame_timer->Update();

	InputManager::GetInstance().Update();

	SceneManager::GetInstance().UpdateActiveScene();
}

// �Q�[���̕`�揈��
void Game::Render(void)
{
	//DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());

	SceneManager::GetInstance().RenderActiveScene();
}
