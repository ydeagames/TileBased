#include "Game\GameMain.h"
#include "Resources\Icon\Icon.h"

// <ウィンドウハンドル>
static HWND hWnd;

// <カレントディレクトリの修正>
static void UpdateCurrentDir(void)
{
	TCHAR m_Path[MAX_PATH];
	TCHAR m_Path2[MAX_PATH];

	if (GetModuleFileName(NULL, m_Path, MAX_PATH))    //実行ファイルのフルパスを取得
	{   //取得に成功
		TCHAR* ptmp = _tcsrchr(m_Path, _T('\\')); // \の最後の出現位置を取得
		if (ptmp != NULL)
		{   //ファイル名を削除
			*ptmp = _T('\0');

			sprintf_s(m_Path2, MAX_PATH, "%s\\Resources", m_Path);
			if (!PathFileExists(m_Path2) || !PathIsDirectory(m_Path2))
			{
				TCHAR* ptmp = _tcsrchr(m_Path, _T('\\')); // \の最後の出現位置を取得
				if (ptmp != NULL)
				{   //ファイル名を削除
					*ptmp = _T('\0');
				}
			}
			sprintf_s(m_Path2, MAX_PATH, "%s\\Resources", m_Path);
			if (PathFileExists(m_Path2) && PathIsDirectory(m_Path2))
				SetCurrentDirectory(m_Path);
		}
	}
}

// <プログラムの終了ポイント>
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

// プログラムのエントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 未使用引数の警告対策
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	UpdateCurrentDir();

#if defined(_DEBUG)
	// メモリーリーク検出機構のセットアップ
	SetUpMemoryLeakDetector();
#endif

	// デバッグ情報用ログファイルの出力の抑制
	SetOutApplicationLogValidFlag(false);

	// 起動モードの設定
#if defined(_DEBUG)
// ウインドウモードで実行
	ChangeWindowMode(true);
	// ウインドウアイコンの設定
	SetWindowIconID(IDI_ICON1);
#else
// フルスクリーンで実行
	ChangeWindowMode(false);
#endif

	// 最大化ボタンが存在するウインドウモードに変更
	SetWindowStyleMode(8);

	// 画面サイズをデスクトップのサイズと同じにする
	Screen::SetScreenSize(Screen::GetDisplaySize());

	// 画面サイズ
	Screen::SetSize(Vector2{640, 480});

	// ウィンドウクラス名
	SetMainWindowClassName("YdeaGames");

	// タイトル
	Screen::SetTitle("マップチップ");

	// サイズ変更を可能にする
	SetWindowSizeChangeEnableFlag(true, false);

	// 常に実行
	SetAlwaysRunFlag(true);

	// 多重起動可能
	SetDoubleStartValidFlag(true);

	// 終了フック
	SetHookWinProc(WndProc);

	// DXライブラリの初期化処理
	if (DxLib_Init() == -1)
		return -1;

	// ウィンドウ取得
	hWnd = GetMainWindowHandle();

	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームの処理

	// ゲームの初期化処理
	Game* game = new Game;

	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{
		// ゲームの更新処理
		game->Update();
		// ゲームの描画処理
		game->Render();

		// 裏画面の内容を表画面に反映
		ScreenFlip();
		// 裏画面の消去
		ClearDrawScreen();
	}

	// ゲームの終了処理
	delete game;

	// DXライブラリの終了処理
	DxLib_End();

	return 0;
}
