#include "DxLib.h"
#include "math.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2B_09_カネコリョウタ";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

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



	//-----ゲームループで使う変数の宣言-----//
	typedef struct Box {
		int x;
		int y;
		int up;
		int down;
		int right;
		int left;
	};

	Box box{
		WIN_WIDTH / 2,
		WIN_HEIGHT / 2,
		100,
		100,
		125,
		125
	};

	typedef struct Player {
		float x;
		float y;
		int r;
		bool isJump;
	};

	Player player{
		550,
		420,
		10,
		false
	};

	typedef struct Enemy {
		float x;
		float y;
		int r;
	};

	Enemy enemy{
		700,
		430,
		16
	};

	typedef struct Move {
		float x;
		float y;
	};

	Move move{
		0,
		0
	};

	typedef struct StrVelo {
		float x;
		float y;
	};

	StrVelo strVelo{
		0,
		0
	};

	typedef struct BTN {
		float x;
		float y;
		int r;
	};

	BTN btn{
		740,
		455,
		4
	};

	int gravity = 4;
	bool isStrike = false;
	int jumpTime = 0;
	int jumpPower = 10;
	bool act = false;
	int sr = 50;
	bool isDecision = false;
	bool isStick = false;
	bool isSticked = false;
	int length = 0;
	bool Oncol = false;
	bool isSeek = true;
	bool isRight = false;


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
		move.x = 0;
		move.y = 0;
		enemy.y += 2;
		length = enemy.y - player.y;

		//移動
		if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 0 && isStrike == false && isDecision == false) {
			if (isSticked == false && isStick == false) {
				player.y += gravity;
			}
		}

		if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 && isStrike == false && isStick == false) {
			if (player.isJump == false) {
				player.isJump = true;
				if (act == false) {
					act = true;
				}
			}
		}
		else if (keys[KEY_INPUT_A] == 1 && isStrike == false && isStick == false) {
			move.x = -4;
			player.x += move.x;
		}
		else if (keys[KEY_INPUT_D] == 1 && isStrike == false && isStick == false) {
			move.x = 4;
			player.x += move.x;
		}

		//張り付き
		if (keys[KEY_INPUT_LSHIFT] == 1 && oldkeys[KEY_INPUT_LSHIFT] == 0) {
			if (isStick == false) {
				isStick = true;
			}
		}
		if (isStick == true) {
			player.y -= 12;
		}

		if (isSticked == true) {
			if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0) {
				isSticked = false;
			}
		}

		//ジャンプ
		if (player.isJump == true && isStick == false) {
			if (act == true) {
				player.y -= jumpPower;
				jumpPower -= 1;

				move.y = jumpPower;
				player.y -= move.y;

				jumpTime++;
				if (jumpTime == 8) {
					jumpTime = 0;
					jumpPower = 10;
					act = false;
				}
			}
		}

		//突進
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && isStick == false) {
			if (isStrike == false) {
				isStrike = true;
				sr = 50;
			}
			else {
				isStrike = false;
				isDecision = false;
			}
			if (player.y + player.r >= box.y + box.down) {
				player.y -= 4;
			}
		}

		if (isStrike == true && isStick == false) {
			if (keys[KEY_INPUT_W] == 1 && isDecision == false) {
				if (isDecision == false) {
					isDecision = true;
				}
				strVelo.y = -20;
			}
			else if (keys[KEY_INPUT_S] == 1 && isDecision == false) {
				if (isDecision == false) {
					isDecision = true;
				}
				strVelo.y = 20;
			}
			else if (keys[KEY_INPUT_A] == 1 && isDecision == false) {
				if (isDecision == false) {
					isDecision = true;
				}
				strVelo.x = -20;
			}
			else if (keys[KEY_INPUT_D] == 1 && isDecision == false) {
				if (isDecision == false) {
					isDecision = true;
				}
				strVelo.x = 20;
			}
		}

		if (isDecision == true) {
			player.x += strVelo.x;
			player.y += strVelo.y;
		}
		else {
			strVelo.x = 0;
			strVelo.y = 0;
		}

		if (isStrike == true) {
			sr -= 2;
			if (sr <= player.r) {
				sr = 50;
			}
		}

		//画面領域
		if (player.y + player.r > box.y + box.down) {
			player.y -= gravity;
			if (player.isJump == true) {
				player.isJump = false;
			}
			if (isStrike == true) {
				isStrike = false;
				isDecision = false;
				player.y -= 20;
			}
		}
		if (player.y - player.r < box.y - box.up) {
			player.y -= move.y;
			if (isStrike == true) {
				isStrike = false;
				isDecision = false;
				player.y += 20;
			}
			if (isStick == true) {
				player.y = box.y - box.up +player.r + 1;
				isStick = false;
				isSticked = true;
			}
		}
		if (player.x - player.r < box.x - box.left) {
			player.x -= move.x;
			if (isStrike == true) {
				isStrike = false;
				isDecision = false;
				player.x += 20;
			}
		}
		if (player.x + player.r > box.x + box.right) {
			player.x -= move.x;
			if (isStrike == true) {
				isStrike = false;
				isDecision = false;
				player.x -= 20;
			}
		}


		if (enemy.y + enemy.r > box.y + box.down) {
			enemy.y -= 2;
		}

		//敵
		if (length >= 180) {
			isSeek = false;
		}

		if (isSeek == true) {
			//向いている方
			if (player.x > enemy.x) {
				isRight = true;
			}
			else {
				isRight = false;
			}
			//移動
			if (enemy.x > player.x) {
				enemy.x -= 0.5;
			}
			else if (enemy.x <= player.x) {
				enemy.x += 0.5;
			}
		}
		if (isSeek == false) {
			if (length < 175) {
				if (isRight == true) {
					if (player.x > enemy.x) {
						isSeek = true;
					}
				}
				else {
					if (player.x < enemy.x) {
						isSeek = true;
					}
				}
			}
		}

		//当たり判定
		if (player.x + player.r+4 > btn.x - btn.r && btn.x + btn.r > player.x - player.r-4) {
			if (player.y + (player.r * 2) > btn.y - btn.r) {
				if (isDecision == true && strVelo.y == 20) {
					if (Oncol == false) {
						Oncol = true;
						box.down += 50;
					}
				}
			}
		}
			// 描画処理
		DrawCircle(player.x, player.y, player.r, GetColor(200, 0, 0), true);
		if (isStrike == true) {
			DrawCircle(player.x, player.y, sr, GetColor(200, 0, 0), false);
		}
		if (isStick == true) {
			DrawCircle(player.x, box.y - box.up, 4, GetColor(200, 0, 0), true);
			DrawLine(player.x, box.y - box.up, player.x, player.y, GetColor(255, 255, 255), true);
		}
		DrawCircle(enemy.x, enemy.y, enemy.r, GetColor(0, 0, 200), true);
		if (Oncol == false) {
			DrawBox(btn.x - btn.r, btn.y - btn.r, btn.x + btn.r, btn.y + btn.r, GetColor(255, 255, 0), true);
		}
		DrawBox(box.x - box.right, box.y - box.up, box.x + box.left, box.y + box.down, GetColor(255, 255, 255), false);
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
