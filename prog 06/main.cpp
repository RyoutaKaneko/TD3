#include "DxLib.h"
#include "Vector3.h"

//�֐��v���g�^�C�v�錾
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);
//�����̕`��
int DrawLine3D(const Vector3& pos1, const Vector3& pos2,const unsigned int color);
//�J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒����_
	const Vector3& cameraUp			//�J�����̏�̌���
);


// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2A_09_�J�l�R�����E�^";

// �E�B���h�E����
const int WIN_WIDTH = 1024;

// �E�B���h�E�c��
const int WIN_HEIGHT = 576;

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
	SetBackgroundColor(0x00, 0x00, 0x64);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�N���b�v��
	SetCameraNearFar(1.0f, 1000.0f);	//�J�����̗L���͈͂̐ݒ�
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);	//��ʂ̒��S�ɃJ���������킹��
	Vector3 cameraPosition(0.0f, 10.0f, 30.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);

	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,		//�ʒu
		cameraTarget,		//�����_
		cameraUp			//��̌���
	);

	Vector3 A(3, -1, 2);
	Vector3 B(1, 5, -4);
	Vector3 C(-1, 7, 6);

	Vector3 AB = B - A;
	Vector3 BC = C - B;

	Vector3 n = AB.cross(BC);
	n.normalize();
	
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

		Vector3 v = cameraPosition - cameraTarget;
		v.normalize();

		unsigned color = GetColor(255, 255, 255);

		if (v.dot(n) < 0) {
			color = GetColor(255, 0, 0);
		}

		// -------------------�`�揈��---------------------
		DrawLine3D(A, B, color);
		DrawLine3D(B, C, color);
		DrawLine3D(C, A, color);

		DrawLine3D(A, A + n * 10, GetColor(0, 255, 0));
		DrawLine3D(B, B + n * 10, GetColor(0, 255, 0));
		DrawLine3D(C, C + n * 10, GetColor(0, 255, 0));

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


//�I�[�o�[���[�h�֐�
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag) {
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };
	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

//�����̕`��
int DrawLine3D(const Vector3& pos1, const Vector3& pos2, const unsigned int color) {
	VECTOR p1 = { pos1.x,pos1.y,pos1.z };
	VECTOR p2 = { pos2.x,pos2.y,pos2.z };

	return DrawLine3D(p1, p2, color);
}


//�J�����̈ʒu�Ǝp��
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒����_
	const Vector3& cameraUp			//�J�����̏�̌���
) {
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}
