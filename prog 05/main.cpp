#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1B_09_�J�l�R�����E�^";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;

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

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	//�v���C���[
	float playerX = 300.0f;
	float playerY = 300.0f;
	const int PLAYER_R = 16;

	//�W�����v
	int isJump = 0;
	int jumpMode = 0;
	float jumpPower = 4.0f;
	float gravity = 4.0f;
	int jumpTime = 0;

	//�d�̓W�����v�Ɏg��
	float startSpeed = 4.0f;
	int flame = 0;
	float g = 9.8f;

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

		//���łȂ��Ƃ�,�d�͂�������
		if (isJump == 0) {
			playerY += gravity;
		}

		//�n�ʂɗ����Ă������ׂ�悤�ɂ���
		if (playerY > 300) { 
			playerY -= gravity;
			jumpPower = 0.0f;
			flame = 0;

			if (isJump == 1) {
				isJump = 0;
			}
		}

		//�W�����v���[�h�ؑ�
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

		//�W�����v����
			//2�l�W�����v
			if (jumpMode == 0) {
				//�������u�ԃt���O�𗧂Ă�
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					if (isJump == 0) {
						isJump = 1;
					}
				}
				//���������Ă���ԃ^�C�}�[���Z
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1) {
					jumpTime++;
					//1�b��������t���O������
					if (jumpTime == 50) {
						jumpTime = 0;
						isJump = 0;
					}
				}
				//�������Ƃ����ɖ߂�
				else if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 1) {

					if (isJump == 1) {
						isJump = 0;
					}

					jumpTime = 0;
				}

				//�t���O�������Ă���Ȃ���W��ς���
				if (isJump == 1) {
					playerY = 200;
				}
				//�����łȂ���Ό��ɖ߂�
				else {
					playerY = 300;
				}
			}
			//�����W�����v
			if (jumpMode == 1) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					//�t���O��0�Ȃ�1�ɂ���
					if (isJump == 0) {
						isJump = 1;
						jumpPower = 4.0f;
					}
				}

				//�W�����v�t���O��1�����[�h1�̂Ƃ��W�����v������
				if (isJump == 1) {
					jumpTime++;
					playerY -= jumpPower;

					//�E��
					if (keys[KEY_INPUT_RIGHT] == 1) {
						playerX += 2;
					}
					//����
					if (keys[KEY_INPUT_LEFT] == 1) {
						playerX -= 2;
					}

					if (jumpTime == 30) {
						jumpTime = 0;
						isJump = 0;
					}
				}
			}

			//�d�̓W�����v
			if (jumpMode == 2) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					if (isJump == 0) {
						//�����x��ݒ�
						startSpeed = 6.0f;
						isJump = 1;
					}
				}

				if (isJump == 1) {
					//�����x����d�͉����x������
					jumpPower = startSpeed - g * (static_cast<float>(flame) / 50.0f);
					//Y�ɑ��x��������
					playerY -= jumpPower;
					//�t���[�����Z
					flame++;
				}
			}
		

		// �`�揈��
		//�W�����v���[�h
		DrawFormatString(0, 0, GetColor(255, 255, 255), "�W�����v���[�h:%d  [j�Őؑ�]", jumpMode);

		DrawFormatString(0, 30, GetColor(255, 255, 255), "%d", flame);
		//���@
		DrawCircle(playerX, playerY, PLAYER_R, GetColor(255, 255, 255), true);

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
