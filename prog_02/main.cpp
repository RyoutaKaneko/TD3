#include "Spring.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2A_08_カネコリョウタ";

// ウィンドウ横幅
const int WIN_WIDTH = 800;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x0, 0x0, 0x0);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);




	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};


	const int sNum = 3;
	Spring s1[sNum];

	int mouseX = 400;
	int mouseY = 400;
	int mouse;
	int mouseNum = 0;
	int isClick = 0;
	int isFound = 0;
	for (int i = 1; i < 3; i++) {
		s1[i].gravity = s1[i].gravity + s1[i - 1].gravity;
	}
	

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
			{
				oldkeys[i] = keys[i];
			}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		GetMousePoint(&mouseX, &mouseY);
		mouse = GetMouseInput();
		if (mouse & MOUSE_INPUT_LEFT) {
			mouseNum++;
		}
		else {
			mouseNum = 0;
		}

		if (isClick == 0) {
			if (mouseNum == 1) {
				isClick = 1;
				for (int i = 0; i < sNum; i++) {
					s1[i].transform.x = mouseX;
					s1[i].transform.y = mouseY;
				}
				if (isFound == 0) {
					isFound = 1;
				}
			}
		}
		else {
			isClick = 0;
		}

		if (isFound == 1) {
			s1[0].Update(mouseX, mouseY, 0);
			for (int i = 1; i < sNum; i++) {
				s1[i].Update(s1[i - 1].transform.x, s1[i - 1].transform.y, s1[i - 1].gravity);
			}
		}

		// 描画処理
		if (isFound == 1) {
			s1[0].Draw(mouseX, mouseY);

			for (int i = 1; i < sNum; i++) {
				s1[i].Draw(s1[i - 1].transform.x, s1[i - 1].transform.y);
			}
		}
		


		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();


	// 正常終了
	return 0;
}
