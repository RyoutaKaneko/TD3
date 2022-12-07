#include "DxLib.h"


//���@����̍\����
typedef struct TransForm {
	float x;
	float y;
	int r;
};


//player���܂�Jump�\����
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


//�W�����v�֐�
void PlayerJump(jump& p, char* keys, char* oldkeys) {

	//��O����
	if (keys == nullptr || oldkeys == nullptr) {
		return;
	}


	//���łȂ��Ƃ�,�d�͂�������
	if (p.isAlive == 0) {
		p.player.y += p.gravity;
	}

	//�n�ʂɗ����Ă������ׂ�悤�ɂ���
	if (p.player.y > 300) {
		p.player.y -= p.gravity;
		p.power = 0.0f;
		p.flame = 0;

		if (p.isAlive == 1) {
			p.isAlive = 0;
		}
	}

	//�W�����v���[�h�ؑ�
	if (keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {

		//2�l
		if (p.mode == 0) {
			p.mode = 1;
		}
		//����
		else if (p.mode == 1) {
			p.mode = 2;
		}
		//�d��
		else {
			p.mode = 0;
		}
	}

	//�W�����v����
		//--------2�l�W�����v--------
	if (p.mode == 0) {
		//�������u�ԃt���O�𗧂Ă�
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			if (p.isAlive == 0) {
				p.isAlive = 1;
			}
		}
		//���������Ă���ԃ^�C�}�[���Z
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1) {
			p.time++;
			//1�b��������t���O������
			if (p.time == 50) {
				p.time = 0;
				p.isAlive = 0;
			}
		}
		//�������Ƃ����ɖ߂�
		else if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 1) {

			if (p.isAlive == 1) {
				p.isAlive = 0;
			}

			p.time = 0;
		}

		//�t���O�������Ă���Ȃ���W��ς���
		if (p.isAlive == 1) {
			p.player.y = 200;
		}
		//�����łȂ���Ό��ɖ߂�
		else {
			p.player.y = 300;
		}
	}


	//-----------�����W�����v-----------
	if (p.mode == 1) {
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			//�t���O��0�Ȃ�1�ɂ���
			if (p.isAlive == 0) {
				p.isAlive = 1;
				p.power = 4.0f;
			}
		}

		//�W�����v�t���O��1�����[�h1�̂Ƃ��W�����v������
		if (p.isAlive == 1) {
			p.time++;
			p.player.y -= p.power;

			//�E��
			if (keys[KEY_INPUT_RIGHT] == 1) {
				p.player.x += 2;
			}
			//����
			if (keys[KEY_INPUT_LEFT] == 1) {
				p.player.x -= 2;
			}

			//����
			if (p.time == 30) {
				p.time = 0;
				p.isAlive = 0;
			}
		}
	}

	//---------------�d�̓W�����v-------------
	if (p.mode == 2) {
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			if (p.isAlive == 0) {
				//�����x��ݒ�
				p.startSpeed = 6.0f;
				p.isAlive = 1;
			}
		}

		if (p.isAlive == 1) {
			//�����x����d�͉����x������
			p.power = p.startSpeed - p.g * (static_cast<float>(p.flame) / 50.0f);
			//Y�ɑ��x��������
			p.player.y -= p.power;
			//�t���[�����Z
			p.flame++;
		}
	}

}

//���@�`��֐�
void DrawMe(jump& p) {
	//���@
	DrawCircle(p.player.x, p.player.y, p.player.r, GetColor(255, 255, 255), true);
	//�W�����v���[�h
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�W�����v���[�h:%d  [j�Őؑ�]", p.mode);
}


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

	//�\���̂�������
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

		//����֐����g�p
		PlayerJump(jump,keys,oldkeys);



		// �`�揈��
		//���@
		DrawMe(jump);

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
