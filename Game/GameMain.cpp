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
	Time::GetInstance().InitializeTime();

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
	Timer::Tick();
	Time::GetInstance().UpdateTime();

	InputManager::GetInstance().Update();

	SceneManager::GetInstance().UpdateActiveScene();
}

// �Q�[���̕`�揈��
void Game::Render(void)
{
	SceneManager::GetInstance().RenderActiveScene();

#ifdef _DEBUG
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());
#endif
}

Screen::Screen()
	: title("")
	, size(Vector2{})
{
	SetTitle("�}�b�v�`�b�v");
	SetSize(Vector2(640, 480));
}

void Screen::SetTitle(const std::string & newtitle)
{
	SetMainWindowText(newtitle.c_str());
	title = newtitle;
}

void Screen::SetSize(const Vector2 & newsize)
{
	SetWindowSize(static_cast<int>(newsize.x), static_cast<int>(newsize.y));
	size = newsize;
}
