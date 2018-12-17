#include "Game\GameMain.h"
#include "Resources\Icon\Icon.h"

// <�E�B���h�E�n���h��>
static HWND hWnd;

// <�J�����g�f�B���N�g���̏C��>
static void UpdateCurrentDir(void)
{
	TCHAR m_Path[MAX_PATH];
	TCHAR m_Path2[MAX_PATH];

	if (GetModuleFileName(NULL, m_Path, MAX_PATH))    //���s�t�@�C���̃t���p�X���擾
	{   //�擾�ɐ���
		TCHAR* ptmp = _tcsrchr(m_Path, _T('\\')); // \�̍Ō�̏o���ʒu���擾
		if (ptmp != NULL)
		{   //�t�@�C�������폜
			*ptmp = _T('\0');

			sprintf_s(m_Path2, MAX_PATH, "%s\\Resources", m_Path);
			if (!PathFileExists(m_Path2) || !PathIsDirectory(m_Path2))
			{
				TCHAR* ptmp = _tcsrchr(m_Path, _T('\\')); // \�̍Ō�̏o���ʒu���擾
				if (ptmp != NULL)
				{   //�t�@�C�������폜
					*ptmp = _T('\0');
				}
			}
			sprintf_s(m_Path2, MAX_PATH, "%s\\Resources", m_Path);
			if (PathFileExists(m_Path2) && PathIsDirectory(m_Path2))
				SetCurrentDirectory(m_Path);
		}
	}
}

// <�v���O�����̏I���|�C���g>
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CLOSE:
		if (GetWindowModeFlag())
		{
			ShowWindow(hWnd, SW_MINIMIZE);
			Sleep(500);
		}
		break;
	}

	return 0;
}

// �v���O�����̃G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	UpdateCurrentDir();

#if defined(_DEBUG)
	// �������[���[�N���o�@�\�̃Z�b�g�A�b�v
	SetUpMemoryLeakDetector();
#endif

	// �f�o�b�O���p���O�t�@�C���̏o�̗͂}��
	SetOutApplicationLogValidFlag(false);

	// �N�����[�h�̐ݒ�
#if defined(_DEBUG)
// �E�C���h�E���[�h�Ŏ��s
	ChangeWindowMode(true);
	// �E�C���h�E�A�C�R���̐ݒ�
	SetWindowIconID(IDI_ICON1);
#else
// �t���X�N���[���Ŏ��s
	ChangeWindowMode(false);
#endif

	// �ő剻�{�^�������݂���E�C���h�E���[�h�ɕύX
	SetWindowStyleMode(8);

	// ��ʃT�C�Y���f�X�N�g�b�v�̃T�C�Y�Ɠ����ɂ���
	Screen::SetScreenSize(Screen::GetDisplaySize());

	// ��ʃT�C�Y
	Screen::SetSize(Vector2{640, 480});

	// �E�B���h�E�N���X��
	SetMainWindowClassName("YdeaGames");

	// �^�C�g��
	Screen::SetTitle("�}�b�v�`�b�v");

	// �T�C�Y�ύX���\�ɂ���
	SetWindowSizeChangeEnableFlag(true, false);

	// ��Ɏ��s
	SetAlwaysRunFlag(true);

	// ���d�N���\
	SetDoubleStartValidFlag(true);

	// �I���t�b�N
	SetHookWinProc(WndProc);

	// DX���C�u�����̏���������
	if (DxLib_Init() == -1)
		return -1;

	// �E�B���h�E�擾
	hWnd = GetMainWindowHandle();

	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[���̏���

	// �Q�[���̏���������
	Game* game = new Game;

	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{
		// �Q�[���̍X�V����
		game->Update();
		// �Q�[���̕`�揈��
		game->Render();

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
		// ����ʂ̏���
		ClearDrawScreen();
	}

	// �Q�[���̏I������
	delete game;

	// DX���C�u�����̏I������
	DxLib_End();

	return 0;
}
