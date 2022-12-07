#include "DxLib.h"
#include "math.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2B_09_�J�l�R�����E�^";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 720;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);



	//-----�Q�[�����[�v�Ŏg���ϐ��̐錾-----//
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


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		move.x = 0;
		move.y = 0;
		enemy.y += 2;
		length = enemy.y - player.y;

		//�ړ�
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

		//����t��
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

		//�W�����v
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

		//�ːi
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

		//��ʗ̈�
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

		//�G
		if (length >= 180) {
			isSeek = false;
		}

		if (isSeek == true) {
			//�����Ă����
			if (player.x > enemy.x) {
				isRight = true;
			}
			else {
				isRight = false;
			}
			//�ړ�
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

		//�����蔻��
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
			// �`�揈��
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
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
