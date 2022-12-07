#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1C_10_�J�l�R�����E�^";

// �E�B���h�E����
const int WIN_WIDTH = 800;

// �E�B���h�E�c��
const int WIN_HEIGHT = 800;

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
	SetBackgroundColor(0x256, 0x256, 0x256);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);




	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int blockGraph = LoadGraph("block.png");



	//�u���b�N���Ƃ̃T�C�Y
	const int BLOCK_SIZE = 32;


	// �}�b�v�`�b�v
	int map[25][25] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
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


	//map�̍s�Ɨ񐔂��擾
	const int MAP_COUNT_WIDTH = sizeof(map[0]) / sizeof(map[0][0]);
	const int MAP_COUNT_HEIGHT = sizeof(map) / sizeof(map[0]);


	//�u���b�N�̒�`
	enum mapInfo {

		NONE,//0
		BLOCK//1
	};


	//�v���C���[
	const int PLAYER_R = 16;
	int playerWorldX = 48, playerWorldY = 48;
	int playerSpeedX = 0, playerSpeedY = 0;

	//���̈ړ��p�ϐ�
	int playerSpeedTmp = 2;


	//4�p�̍��W��p��
	int leftTopX = 0, leftBottomX = 0, rightTopX = 0, rightBottomX = 0;
	int leftTopY = 0, leftBottomY = 0, rightTopY = 0, rightBottomY = 0;


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



		//�}�b�v��̌��݈ʒu��ϐ��ɑ��
		leftTopX = (playerWorldX - PLAYER_R) / BLOCK_SIZE;
		leftTopY = (playerWorldY - PLAYER_R) / BLOCK_SIZE;
		leftBottomX = (playerWorldX - PLAYER_R) / BLOCK_SIZE;
		leftBottomY = (playerWorldY + PLAYER_R - 1) / BLOCK_SIZE;

		rightTopX = (playerWorldX + PLAYER_R - 1) / BLOCK_SIZE;
		rightTopY = (playerWorldY - PLAYER_R) / BLOCK_SIZE;
		rightBottomX = (playerWorldX + PLAYER_R - 1) / BLOCK_SIZE;
		rightBottomY = (playerWorldY + PLAYER_R - 1) / BLOCK_SIZE;




		//�v���C���[�̈ړ�����
		//���t���[���X�s�[�h��0��
		playerSpeedX = 0, playerSpeedY = 0;
		//���ړ����x��2��
		playerSpeedTmp = 2;



		//��
		if (keys[KEY_INPUT_UP] == 1) {

			leftTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
			rightTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;

			//�ォ��
			if (keys[KEY_INPUT_LEFT] == 1) {

				leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				rightTopX = (playerWorldX - playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

				//��ɉ����Ȃ���΂��̂܂܏��
				if (map[leftTopY][leftTopX] == NONE && map[rightTopY][rightTopX] == NONE) {
					playerSpeedY = -2;
				}
				else {

					playerSpeedTmp = 1;

					leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					rightTopX = (playerWorldX - playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftBottomX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftBottomY = (playerWorldY - playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

					//���ɂ����i�߂�Ȃ瑬�x�𗎂Ƃ�
					if (map[leftTopY + 1][leftTopX] == NONE && map[rightTopY + 1][rightTopX] == NONE) {
						if (playerWorldY - PLAYER_R >= (leftTopY + 1) * BLOCK_SIZE) {
							playerSpeedX = -1;
						}
					}
					//���肫�������΍�
					else {
						if (map[leftTopY][leftTopX + 1] == NONE && map[leftBottomY][leftBottomX + 1] == NONE) {
							playerSpeedY = -1;
						}
					}
				}
				//���ɉ����Ȃ���΂��̂܂܍���
				if (map[leftTopY][leftTopX] == NONE && map[leftBottomY][leftBottomX] == NONE) {
					playerSpeedX = -2;
				}
				else {

					playerSpeedTmp = 1;

					leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftBottomX = (playerWorldX - playerSpeedTmp- PLAYER_R) / BLOCK_SIZE;
					leftBottomY = (playerWorldY - playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightTopX = (playerWorldX - playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;

					//�ゾ���i�߂�Ȃ瑬�x�𗎂Ƃ�
					if (map[leftTopY][leftTopX + 1] == NONE && map[leftBottomY][leftBottomX + 1] == NONE) {
						if (playerWorldY - PLAYER_R < (leftTopY + 1) * BLOCK_SIZE) {
							playerSpeedY = -1;
						}
					}
					//���肫�������΍�
					else {
						if (map[leftTopY + 1][leftTopX] == NONE && map[rightTopY + 1][rightTopX] == NONE) {
							playerSpeedX = -1;
						}
					}
				}
			}


			//�ォ�E
			else if (keys[KEY_INPUT_RIGHT] == 1) {

				leftTopX = (playerWorldX + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				rightTopX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

				//��ɉ����Ȃ���΂��̂܂܏��
				if (map[leftTopY][leftTopX] == NONE && map[rightTopY][rightTopX] == NONE) {
					playerSpeedY = -2;
				}
				else {

					playerSpeedTmp = 1;

					leftTopX = (playerWorldX + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					rightTopX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					rightBottomX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightBottomY = (playerWorldY + playerSpeedTmp+ PLAYER_R - 1) / BLOCK_SIZE;

					//�E�ɂ����i�߂�Ȃ瑬�x�𗎂Ƃ�
						if (map[rightTopY + 1][rightTopX] == NONE && map[leftTopY + 1][rightTopX] == NONE) {
							if (playerWorldY + PLAYER_R >= (rightTopY + 1) * BLOCK_SIZE) {
								playerSpeedX = 1;
							}
						}
				}

				//�E�ɉ����Ȃ���΂��̂܂܉E��
				if (map[rightTopY][rightTopX] == NONE && map[rightBottomY][rightBottomX] == NONE) {
					playerSpeedX = 2;
				}
				else {

					playerSpeedTmp = 1;

					rightTopX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightTopY = (playerWorldY - playerSpeedTmp + PLAYER_R) / BLOCK_SIZE;
					leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					rightBottomX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
	
					//�ゾ���i�߂�Ȃ瑬�x�𗎂Ƃ�
						if (map[rightTopY][rightTopX + 1] == NONE && map[rightBottomY][rightBottomX + 1]) {
							if (playerWorldY + PLAYER_R < (rightTopY + 1) * BLOCK_SIZE) {
								playerSpeedY = -1;
							}
						}
				}
			}

			//��{�̏�ړ�
			else {
				leftTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				rightTopY = (playerWorldY - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;

				if (map[leftTopY][leftTopX] == NONE && map[rightTopY][rightTopX] == NONE) {
					playerSpeedY = -2;
				}
			}
		}


		//��
		else if (keys[KEY_INPUT_DOWN] == 1) {

			//������
			if (keys[KEY_INPUT_LEFT] == 1) {
				leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				leftBottomX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				leftBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
				leftTopY = (playerWorldY + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				rightBottomX = (playerWorldX - playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
				rightBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

				//���ɉ����Ȃ���΂��̂܂܉���
				if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == NONE) {
					playerSpeedY = 2;
				}

				//���ɉ����Ȃ���΂��̂܂܍���
				if (map[leftTopY][leftTopX] == NONE && map[leftBottomY][leftBottomX] == NONE) {
					playerSpeedX = -2;
				}

				else {

					playerSpeedTmp = 1;

					leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftTopY = (playerWorldY + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					rightBottomX = (playerWorldX - playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					leftBottomX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

					//���ɂ����i�߂�Ȃ瑬�x�𗎂Ƃ�
					if (playerWorldY + PLAYER_R > (leftTopX + 1) * BLOCK_SIZE) {
						if (map[leftTopY][leftTopX] == NONE) {
							playerSpeedX = -1;
						}
					}
					//���ɂ����i�߂�Ȃ瑬�x�𗎂Ƃ�
					if (map[rightBottomY][rightBottomX] == NONE) {
						playerSpeedY = 1;
					}


				}
			}

			//�����E
			else if (keys[KEY_INPUT_RIGHT] == 1) {

				leftBottomX = (playerWorldX + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				leftBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
				rightTopX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
				rightTopY = (playerWorldY + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
				rightBottomX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
				rightBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;


				//���ɉ����Ȃ���΂��̂܂܉���
				if (map[rightBottomY][rightBottomX] == NONE && map[leftBottomY][leftBottomX] == NONE) {
					playerSpeedY = 2;
				}

				//�E�ɉ����Ȃ���΂��̂܂܉E��
				if (map[rightBottomY][rightBottomX] == NONE && map[rightTopY][rightTopX] == NONE) {
					playerSpeedX = 2;
				}
				else {

					playerSpeedTmp = 1;

					rightTopX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightTopY = (playerWorldY + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftBottomX = (playerWorldX + playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
					leftBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightBottomX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
					rightBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

					//�E�ɂ����i�߂�Ȃ瑬�x�𗎂Ƃ�
					if (playerWorldY - PLAYER_R >= (rightTopX)*BLOCK_SIZE) {
						if (map[rightTopY][rightTopX] == NONE) {
							playerSpeedX = 1;
						}
					}

					//���ɂ����i�߂�Ȃ瑬�x�𗎂Ƃ�
					if (map[leftBottomY][leftBottomX] == NONE) {
						playerSpeedY = 1;
					}
				}
			}

			//��{�̉��ړ�
			else {
				leftBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
				rightBottomY = (playerWorldY + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

				if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == NONE) {
					playerSpeedY = 2;
				}
			}

		}


		//��
		else if (keys[KEY_INPUT_LEFT] == 1) {
			leftTopX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;
			leftBottomX = (playerWorldX - playerSpeedTmp - PLAYER_R) / BLOCK_SIZE;

			if (map[leftBottomY][leftBottomX] == NONE && map[leftTopY][leftTopX] == NONE) {
				playerSpeedX = -2;
			}
		}


		//�E
		else if (keys[KEY_INPUT_RIGHT] == 1) {
			rightTopX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;
			rightBottomX = (playerWorldX + playerSpeedTmp + PLAYER_R - 1) / BLOCK_SIZE;

			if (map[rightBottomY][rightBottomX] == NONE && map[rightTopY][rightTopX] == NONE) {
				playerSpeedX = 2;
			}
		}


		//��ɍ��W�ɃX�s�[�h�𑫂�������
		playerWorldX += playerSpeedX;
		playerWorldY += playerSpeedY;






		// �`�揈��


		//�}�b�v�̕`��
		//�s(��)
		for (int y = 0; y < MAP_COUNT_HEIGHT; y++) {
			//��(�c)
			for (int x = 0; x < MAP_COUNT_WIDTH; x++) {

				//1�Ȃ�u���b�N��`��
				if (map[y][x] == BLOCK) {
					DrawGraph(x * BLOCK_SIZE, y * BLOCK_SIZE, blockGraph, true);
				}
			}
		}


		//�v���C���[�̕`��
		DrawBox(playerWorldX - PLAYER_R, playerWorldY - PLAYER_R, playerWorldX + PLAYER_R, playerWorldY + PLAYER_R,
			GetColor(128, 128, 128), true);
		DrawCircle(playerWorldX, playerWorldY, PLAYER_R, GetColor(255, 0, 0), true);

		//4�p�̍��W��\��
		DrawFormatString(60, 352, GetColor(255, 255, 255), "����[%d]", leftTopX);
		DrawFormatString(120, 352, GetColor(255, 255, 255), "[%d]", leftTopY);
		DrawFormatString(60, 384, GetColor(255, 255, 255), "����[%d]", leftBottomX);
		DrawFormatString(120, 384, GetColor(255, 255, 255), "[%d]", leftBottomY);

		DrawFormatString(240, 352, GetColor(255, 255, 255), "�E��[%d]", rightTopX);
		DrawFormatString(300, 352, GetColor(255, 255, 255), "[%d]", rightTopY);
		DrawFormatString(240, 384, GetColor(255, 255, 255), "�E��[%d]", rightBottomX);
		DrawFormatString(300, 384, GetColor(255, 255, 255), "[%d]", rightBottomY);

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
