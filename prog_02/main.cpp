#include "Spring.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2A_08_�J�l�R�����E�^";

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
	SetBackgroundColor(0x0, 0x0, 0x0);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);




	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
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

		// �`�揈��
		if (isFound == 1) {
			s1[0].Draw(mouseX, mouseY);

			for (int i = 1; i < sNum; i++) {
				s1[i].Draw(s1[i - 1].transform.x, s1[i - 1].transform.y);
			}
		}
		


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
