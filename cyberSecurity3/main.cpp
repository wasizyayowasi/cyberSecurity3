#include "DxLib.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneTitle.h"
#include "InputState.h"
#include "game.h"
#include <cassert>
#include <array>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//windowモードの設定
	ChangeWindowMode(Game::kWindowMode);

	//window名設定
	SetMainWindowText(Game::kTitleText);

	//画面サイズの設定
	SetGraphMode(Game::kScreenWidth,Game::kScreenHeight, Game::kScreenDepth);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	InputState input;
	SceneManager sceneManager;
	sceneManager.changeScene(new SceneTitle(sceneManager));


	while (ProcessMessage() == 0) {

		LONGLONG time = GetNowHiPerformanceCount();
		//画面のクリア
		ClearDrawScreen();

		input.update();

		sceneManager.update(input);

		sceneManager.draw();

		//裏画面を表画面に切り替える
		ScreenFlip();

		//escを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;

		//fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667) {

		}

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}