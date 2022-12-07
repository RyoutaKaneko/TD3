#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1B_09_カネコリョウタ";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;

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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言

	//プレイヤー
	float playerX = 300.0f;
	float playerY = 300.0f;
	const int PLAYER_R = 16;

	//ジャンプ
	int isJump = 0;
	int jumpMode = 0;
	float jumpPower = 4.0f;
	float gravity = 4.0f;
	int jumpTime = 0;

	//重力ジャンプに使う
	float startSpeed = 4.0f;
	int flame = 0;
	float g = 9.8f;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

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

		// 更新処理

		//飛んでないとき,重力を加える
		if (isJump == 0) {
			playerY += gravity;
		}

		//地面に立っていたら飛べるようにする
		if (playerY > 300) { 
			playerY -= gravity;
			jumpPower = 0.0f;
			flame = 0;

			if (isJump == 1) {
				isJump = 0;
			}
		}

		//ジャンプモード切替
		if (keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {

			if (jumpMode == 0) {
				jumpMode = 1;
			}
			else if(jumpMode == 1) {
				jumpMode = 2;
			}
			else {
				jumpMode = 0;
			}
		}

		//ジャンプ処理
			//2値ジャンプ
			if (jumpMode == 0) {
				//押した瞬間フラグを立てる
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					if (isJump == 0) {
						isJump = 1;
					}
				}
				//長押ししている間タイマー加算
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1) {
					jumpTime++;
					//1秒立ったらフラグを消す
					if (jumpTime == 50) {
						jumpTime = 0;
						isJump = 0;
					}
				}
				//離したとき元に戻す
				else if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 1) {

					if (isJump == 1) {
						isJump = 0;
					}

					jumpTime = 0;
				}

				//フラグが立っているなら座標を変える
				if (isJump == 1) {
					playerY = 200;
				}
				//そうでなければ元に戻す
				else {
					playerY = 300;
				}
			}
			//等速ジャンプ
			if (jumpMode == 1) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					//フラグが0なら1にする
					if (isJump == 0) {
						isJump = 1;
						jumpPower = 4.0f;
					}
				}

				//ジャンプフラグが1かつモード1のときジャンプさせる
				if (isJump == 1) {
					jumpTime++;
					playerY -= jumpPower;

					//右へ
					if (keys[KEY_INPUT_RIGHT] == 1) {
						playerX += 2;
					}
					//左へ
					if (keys[KEY_INPUT_LEFT] == 1) {
						playerX -= 2;
					}

					if (jumpTime == 30) {
						jumpTime = 0;
						isJump = 0;
					}
				}
			}

			//重力ジャンプ
			if (jumpMode == 2) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					if (isJump == 0) {
						//初速度を設定
						startSpeed = 6.0f;
						isJump = 1;
					}
				}

				if (isJump == 1) {
					//初速度から重力加速度分引く
					jumpPower = startSpeed - g * (static_cast<float>(flame) / 50.0f);
					//Yに速度を加える
					playerY -= jumpPower;
					//フレーム加算
					flame++;
				}
			}
		

		// 描画処理
		//ジャンプモード
		DrawFormatString(0, 0, GetColor(255, 255, 255), "ジャンプモード:%d  [jで切替]", jumpMode);

		DrawFormatString(0, 30, GetColor(255, 255, 255), "%d", flame);
		//自機
		DrawCircle(playerX, playerY, PLAYER_R, GetColor(255, 255, 255), true);

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
