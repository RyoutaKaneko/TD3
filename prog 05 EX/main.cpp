#include "DxLib.h"


//自機周りの構造体
typedef struct TransForm {
	float x;
	float y;
	int r;
};


//playerを含むJump構造体
typedef struct Jump {
	TransForm player;
	int isAlive;
	int mode;
	float power;
	int time;
	float startSpeed;
	int flame;
	float g;
	float gravity;
}jump;


//ジャンプ関数
void PlayerJump(jump& p, char* keys, char* oldkeys) {

	//例外処理
	if (keys == nullptr || oldkeys == nullptr) {
		return;
	}


	//飛んでないとき,重力を加える
	if (p.isAlive == 0) {
		p.player.y += p.gravity;
	}

	//地面に立っていたら飛べるようにする
	if (p.player.y > 300) {
		p.player.y -= p.gravity;
		p.power = 0.0f;
		p.flame = 0;

		if (p.isAlive == 1) {
			p.isAlive = 0;
		}
	}

	//ジャンプモード切替
	if (keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {

		//2値
		if (p.mode == 0) {
			p.mode = 1;
		}
		//等速
		else if (p.mode == 1) {
			p.mode = 2;
		}
		//重力
		else {
			p.mode = 0;
		}
	}

	//ジャンプ処理
		//--------2値ジャンプ--------
	if (p.mode == 0) {
		//押した瞬間フラグを立てる
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			if (p.isAlive == 0) {
				p.isAlive = 1;
			}
		}
		//長押ししている間タイマー加算
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1) {
			p.time++;
			//1秒立ったらフラグを消す
			if (p.time == 50) {
				p.time = 0;
				p.isAlive = 0;
			}
		}
		//離したとき元に戻す
		else if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 1) {

			if (p.isAlive == 1) {
				p.isAlive = 0;
			}

			p.time = 0;
		}

		//フラグが立っているなら座標を変える
		if (p.isAlive == 1) {
			p.player.y = 200;
		}
		//そうでなければ元に戻す
		else {
			p.player.y = 300;
		}
	}


	//-----------等速ジャンプ-----------
	if (p.mode == 1) {
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			//フラグが0なら1にする
			if (p.isAlive == 0) {
				p.isAlive = 1;
				p.power = 4.0f;
			}
		}

		//ジャンプフラグが1かつモード1のときジャンプさせる
		if (p.isAlive == 1) {
			p.time++;
			p.player.y -= p.power;

			//右へ
			if (keys[KEY_INPUT_RIGHT] == 1) {
				p.player.x += 2;
			}
			//左へ
			if (keys[KEY_INPUT_LEFT] == 1) {
				p.player.x -= 2;
			}

			//落下
			if (p.time == 30) {
				p.time = 0;
				p.isAlive = 0;
			}
		}
	}

	//---------------重力ジャンプ-------------
	if (p.mode == 2) {
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			if (p.isAlive == 0) {
				//初速度を設定
				p.startSpeed = 6.0f;
				p.isAlive = 1;
			}
		}

		if (p.isAlive == 1) {
			//初速度から重力加速度分引く
			p.power = p.startSpeed - p.g * (static_cast<float>(p.flame) / 50.0f);
			//Yに速度を加える
			p.player.y -= p.power;
			//フレーム加算
			p.flame++;
		}
	}

}

//自機描画関数
void DrawMe(jump& p) {
	//自機
	DrawCircle(p.player.x, p.player.y, p.player.r, GetColor(255, 255, 255), true);
	//ジャンプモード
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ジャンプモード:%d  [jで切替]", p.mode);
}


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

	//構造体を初期化
	Jump jump{
		//player
			{
			300.0f,300.0f,16
		},
		0,
		0,
		4.0f,
		0,
		4.0f,
		0,
		9.8f,
		4.0f
	};

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

		//自作関数を使用
		PlayerJump(jump,keys,oldkeys);



		// 描画処理
		//自機
		DrawMe(jump);

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
