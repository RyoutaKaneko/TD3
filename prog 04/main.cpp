#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1C_10_カネコリョウタ";

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
	SetBackgroundColor(0x256, 0x256, 0x256);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);




	// 画像などのリソースデータの変数宣言と読み込み
	int blockGraph = LoadGraph("block.png");



	//ブロックごとのサイズ
	const int BLOCK_SIZE = 32;


	// マップチップ
	int map[25][25] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};


	//mapの行と列数を取得
	const int MAP_COUNT_WIDTH = sizeof(map[0]) / sizeof(map[0][0]);
	const int MAP_COUNT_HEIGHT = sizeof(map) / sizeof(map[0]);


	//ブロックの定義
	enum mapInfo {

		NONE,//0
		BLOCK//1
	};


	//プレイヤー
	const int PLAYER_R = 16;
	int playerWorldX = 48, playerWorldY = 48;
	int playerSpeedX = 0, playerSpeedY = 0;

	//--------------ワールド座標------------//
	int playerScreenX = 0;
	int playerScreenY = 0;
	int scrollX = 0;
	int scrollY = 0;

	//仮の移動用変数
	int playerSpeedTmp = 2;


	//4角の座標を用意
	int leftTopX = 0, leftBottomX = 0, rightTopX = 0, rightBottomX = 0;
	int leftTopY = 0, leftBottomY = 0, rightTopY = 0, rightBottomY = 0;


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



		//マップ上の現在位置を変数に代入
		leftTopX = (playerWorldX - PLAYER_R) / BLOCK_SIZE;
		leftTopY = (playerWorldY - PLAYER_R) / BLOCK_SIZE;
		leftBottomX = (playerWorldX - PLAYER_R) / BLOCK_SIZE;
		leftBottomY = (playerWorldY + PLAYER_R - 1) / BLOCK_SIZE;

		rightTopX = (playerWorldX + PLAYER_R - 1) / BLOCK_SIZE;
		rightTopY = (playerWorldY - PLAYER_R) / BLOCK_SIZE;
		rightBottomX = (playerWorldX + PLAYER_R - 1) / BLOCK_SIZE;
		rightBottomY = (playerWorldY + PLAYER_R - 1) / BLOCK_SIZE;




		//プレイヤーの移動処理
		//毎フレームスピードを0に
		playerSpeedX = 0, playerSpeedY = 0;
		//仮移動速度を2に
		playerSpeedTmp = 2;



		//上
		if (keys[KEY_INPUT_UP] == 1) {

			leftTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
			rightTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;

			
			//基本の上移動

				if (map[leftTopY][leftTopX] == NONE && map[rightTopY][rightTopX] == NONE) {
					playerSpeedY = -2;
				}
			
		}


		//下
		if (keys[KEY_INPUT_DOWN] == 1) {

			
				leftBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
				rightBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

				if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == NONE) {
					playerSpeedY = 2;
				}
			

		}


		//左
		if (keys[KEY_INPUT_LEFT] == 1) {
			leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
			leftBottomX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;

			if (map[leftBottomY][leftBottomX] == NONE && map[leftTopY][leftTopX] == NONE) {
				playerSpeedX = -2;
			}

			//--------------------スクロールしていたなら値を引く-------------------
			if (scrollX > 0) {
				scrollX -= 2;
			}
		}


		//右
		if (keys[KEY_INPUT_RIGHT] == 1) {
			rightTopX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
			rightBottomX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

			if (map[rightBottomY][rightBottomX] == NONE && map[rightTopY][rightTopX] == NONE) {
				playerSpeedX = 2;
			}

			//-----------------------画面の半分を超えたらスクロールの値を増やす--------------------------
			if (playerWorldX > WIN_WIDTH / 2) {
				scrollX += playerSpeedX;
			}
		}


		//常に座標にスピードを足し続ける
		playerWorldX += playerSpeedX;
		playerWorldY += playerSpeedY;


		//-------------------------モニター座標を代入----------------------
		playerScreenX = playerWorldX - scrollX;
		playerScreenY = playerWorldY - scrollY;




		// 描画処理


		//マップの描画
		//行(横)
		for (int y = 0; y < MAP_COUNT_HEIGHT; y++) {
			//列(縦)
			for (int x = 0; x < MAP_COUNT_WIDTH; x++) {

				//1ならブロックを描画
				if (map[y][x] == BLOCK) {
					DrawGraph((x * BLOCK_SIZE)- scrollX, y * BLOCK_SIZE, blockGraph, true);
				}
			}
		}


		//プレイヤーの描画

		//-------------------------ワールド座標で描画------------------------
		DrawBox(playerScreenX - PLAYER_R, playerScreenY - PLAYER_R, playerScreenX + PLAYER_R, playerScreenY + PLAYER_R,
			GetColor(128, 128, 128), true);
		DrawCircle(playerScreenX, playerScreenY, PLAYER_R, GetColor(255, 0, 0), true);

		//4角の座標を表示
		DrawFormatString(60, 352, GetColor(255, 255, 255), "左上[%d]", leftTopX);
		DrawFormatString(120, 352, GetColor(255, 255, 255), "[%d]", leftTopY);
		DrawFormatString(60, 384, GetColor(255, 255, 255), "左下[%d]", leftBottomX);
		DrawFormatString(120, 384, GetColor(255, 255, 255), "[%d]", leftBottomY);

		DrawFormatString(240, 352, GetColor(255, 255, 255), "右上[%d]", rightTopX);
		DrawFormatString(300, 352, GetColor(255, 255, 255), "[%d]", rightTopY);
		DrawFormatString(240, 384, GetColor(255, 255, 255), "右下[%d]", rightBottomX);
		DrawFormatString(300, 384, GetColor(255, 255, 255), "[%d]", rightBottomY);

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
