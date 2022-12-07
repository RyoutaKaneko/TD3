#include <DxLib.h>
#include <time.h>
#include "boss.h"
#include "bullet.h"
#include "math.h"
#include "collision.h"

//define PI 3.141519

const float PI = 3.141592f;

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "ONE SHOT";

// �E�B���h�E����
const int WIN_WIDTH = 720;

// �E�B���h�E�c��
const int WIN_HEIGHT = 960;

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
	int eyeGraph[3];
	LoadDivGraph("resource/eye.png", 3, 3, 1, 48, 52, eyeGraph);
	int bossPartGraph[3];
	LoadDivGraph("resource/bossPart.png", 3, 3, 1, 64, 64, bossPartGraph);
	int playerBulletGraph = LoadGraph("resource/bullet.png");
	int backGraph = LoadGraph("resource/back.png");
	int flameGraph = LoadGraph("resource/flame.png");
	int barrierGraph[2];
	LoadDivGraph("resource/barrier.png", 2, 2, 1, 32, 16, barrierGraph);

	int playerGraph[2];
	LoadDivGraph("resource/player.png", 2, 2, 1, 48, 64, playerGraph);
	int bombGraph[5];
	LoadDivGraph("resource/bomb.png", 5, 5, 1, 64, 64, bombGraph);
	int titleGraph = LoadGraph("resource/title.png");
	int spaceGraph = LoadGraph("resource/pushSpace.png");
	int resultGraph[3];
	LoadDivGraph("resource/resultMess.png", 3, 3, 1, 720, 960, resultGraph);
	int startGraph = LoadGraph("resource/startText.png");
	int deadCountGraph = LoadGraph("resource/deadCount.png");
	int numberGraph[10];
	LoadDivGraph("resource/numbers.png", 10, 10, 1, 72, 144, numberGraph);
	int retryGraph[2];
	LoadDivGraph("resource/retry.png", 2, 2, 1, 256, 128, retryGraph);
	int overGraph[2];
	LoadDivGraph("resource/over.png", 2, 2, 1, 256, 128, overGraph);
	int thxGraph = LoadGraph("resource/thanks.png");


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//����
	srand(time(NULL));
	//�{�X

	//�{�X�̃^�C�}�[�̏������Ɏg��
	int timer0 = 30;
	int timer1 = 300;
	int timer2 = 300;
	int timer3 = 500;	//(-200)
	int timer4 = 500;	//(-100)
	int timer5 = 1000;	//(-200)
	int timer6 = 400;
	int timer8 = 3000;
	int timer11 = 500;
	int timer12 = 50;

	BOSS boss = {
		300.0f,		//X���W
		200.0f,		//Y���W
		150,		//���a
		0.0f,		//�{�X�̒��̉摜�̉�]
		2.0f,		//X����
		0.5f,		//Y����
		0,			//���E�ړ�(0�Ȃ�E�A1�Ȃ獶)
		0,			//�㉺�ړ�(0�Ȃ��A1�Ȃ牺)
		0,			//�U�����(0�Ȃ�ҋ@�A����ȊO�Ȃ�Ή������s��)
		250,		//�U���̃^�C�}�[�Ǘ�
		false		//���݂��Ă��邩(true�Ȃ瑶�݂���Afalse�Ȃ瑶�݂��Ȃ�)
	};

	//�{�X(�o������\���̂�)
	double bossPartX[4]{ 0.0f,0.0f,0.0f,0.0f };
	double bossPartY[4]{ 0.0f,0.0f,0.0f,0.0f };
	double bossCenterX = 350.0f;
	double bossCenterY = 200.0f;
	double bossRadius[4]{ 0.0f,0.0f,0.0f,0.0f };
	double bossLength = 128.0f;
	double bossPartAngle[4]{ 45.0f,135.0f,225.0f,315.0f };
	double bossAddX[4];
	double bossAddY[4];
	double bossAngleSpeed = 2.0f;
	double bossCenterR = 22.0f;
	int bossMoveTime = 0;
	int bossMoveCount = 0;
	int eyeState = 0;
	int partState = 0;
	int barrierState = 0;

	//�{�X�o���A
	double bossBarrierX[2]{ 0.0f };
	double bossBarrierY[2]{ 0.0f };
	float bossBarrierR = 32.0f;
	double barrierNum = 1.5f;

	bool isBarrierOpen = 0;
	int openTime = 64;


	//�{�X�̒e
	const int BOSS_BULLET_CONST = 1000;
	BOSS_BULLET bossBullet[BOSS_BULLET_CONST];

	for (int i = 0; i < BOSS_BULLET_CONST; i++) {
		bossBullet[i] = {
			boss.x,		//X���W
			boss.y,		//Y���W
			16,			//���a
			false,		//���݂��Ă��邩(true�Ȃ瑶�݂���Afalse�Ȃ瑶�݂��Ȃ�)
			0,			//�e�̋����̎��
			0,			//�e�̗�����ۑ�
			0
		};
	}

	//�\����
	const int LINE_CONST = 10;
	LINE line[LINE_CONST];

	for (int i = 0; i < LINE_CONST; i++) {
		line[i] = {
			0,		//x���W
			0,		//y���W
			false	//���݂��Ă��邩
		};
	}

	//�\���~
	const int CIRCLE_CONST = 20;
	CIRCLE circle[CIRCLE_CONST];
	int circleNumber = 0;

	for (int i = 0; i < CIRCLE_CONST; i++) {
		circle[i] = {
			0,		//x���W
			0,		//y���W
			false	//���݂��Ă��邩
		};
	}
	//cace6:�ݒu�e�̃V�[���ؑ�
	bool trap = false;
	//�r�[���̊Ǘ�
	const int BEAM_CONST = 6;
	BEAM beam[BEAM_CONST];
	const int BEAM_TIME1_2 = 70;
	const int BEAM_TIME2_0 = 10;
	int beamRand = 0;
	int oldBeam = -1;
	int oldBeam2_1 = -1;
	int oldBeam2_2 = -1;

	for (int i = 0; i < BEAM_CONST; i++) {
		beam[i] = {
			0,		//�r�[���̏��(0�Ȃ疳�A1�Ȃ�\���A2�Ȃ甭��)
			0		//�^�C�}�[
		};
	}

	//50F�x�点�Ď��@���W���擾���邽�߂̕ϐ�

	const int OLD_PLAYER_MAX = 50;
	int oldPlayerX[50];
	int oldPlayerY[50];

	for (int i = 0; i < OLD_PLAYER_MAX; i++) {
		oldPlayerX[i] = 0;
		oldPlayerY[i] = 0;
	}

	//�V�[���ؑ�

	int scene = 0;

	bool isRetry = 1;
	bool isFaled = 0;
	bool isDead = 0;
	bool isPlay = 0;
	bool isStart = 0;
	int sceneCount = 0;
	int trapEx = -1;
	int oldSceneType = 0;

	bool isDebug = false;

	int sceneTime = 0;
	int alpha = 0;//�Ö��Ɏg�����
	int lineAlpha = 0;
	bool isLimit = 0;

	//�w�i
	int backY = 0;
	int randX = 0;
	bool isShake = 0;

	//���Z�b�g
	bool isReset = 0;

	//�v���C���[�̕ϐ�
	float playerX = 350.0f;
	float playerY = 1000.0f;
	const int PLAYER_R = 24;
	const float PLAYER_SPEED = 4.5f;
	float playerSlowSpeed = 1.0f;//�΂߈ړ��Ȃ߂炩�ɂ���
	double playerAngle = 0.0f;

	int playerLife = 1;

	int playerBombCount = 0;
	//�v���C���[�̒e
	const int BULLET_R = 8;

	bool isShot = 0;
	double bulletX = 0.0f;
	double bulletY = 0.0f;
	float bulletSpeed = 0;

	//���ˉ��o�Ɏg�����

	float playerTmpX = 350.0f;
	float playerTmpY = 650.0f;
	float bulletTmpX = 0.0f;
	float bulletTmpY = 0.0f;

	float bulletLineX = 0.0f;
	float bulletLineY = 0.0f;
	float bossCenterTmpX = 0.0f;
	float bossCenterTmpY = 0.0f;

	int bulletLineColor = 255;

	//�������o
	int bossPartXTmp[4]{ 520,520,200,200 };
	int bossPartYTmp[4]{ 220,540,220,540 };

	int bossCenterXTmp = 360;
	int bossCenterYTmp = 380;

	float bulletSpeedTmp = 0.0f;

	int bossBombCount[10]{ 0 };
	int bossBombTime[10]{ 0 };
	bool isBossBomb[10]{ 0 };
	bool isBossBye[2]{ 0 };

	//���S��
	int deadCount = 0;
	int countAlpha = 255;

	//�p�b�h����
	int pad;
	int InputX;
	int InputY;
	GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_KEY_PAD1);
	pad = GetJoypadInputState(DX_INPUT_PAD1);

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		//�z��Ȃ̂�oldkey - keys;�̂悤�ɂł��Ȃ��B�v�f���P���R�s�[

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		char eachNumber[3];
		sprintf_s(eachNumber, sizeof(eachNumber), "%d", deadCount);


		switch (scene) {

			case 0:
				//�Q�[����
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || pad & PAD_INPUT_2) {
					if (isPlay == 0) {
						bulletY = 970.0f;
						bulletX = 360.0f;
						bulletLineX = 360.0f;
						bulletLineY = 1000.0f;
						isPlay = 1;
					}
				}

				//debug���[�h�N��
				if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0) {
					isDebug = true;
					scene = 1;
					isReset = 1;
				}

				if (isPlay == 1) {
					sceneTime++;

					playerY -= PLAYER_SPEED;

					if (sceneTime == 50) {
						sceneTime = 0;
						isReset = 1;
						scene = 1;
					}
				}
				break;

				//�v���C���
			case 1:
				//�w�i�ړ�(---�V�[��1----)
				backY++;
				if (backY == 960) {
					backY = 0;
				}

				//�ŏ��̉��o
				if (isStart == 0) {
					sceneTime++;
					bossLength += 2.0f;

					if (sceneTime == 64) {
						sceneTime = 0;
						isStart = 1;
					}
				}

				//debug���[�h�N��
				if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0) {
					if (isDebug == false) {
						isDebug = true;
					}
					else {
						isDebug = false;
					}
				}

				//�΂߈ړ����Ȃ߂炩��
				if ((keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1) || (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1)) {
					if ((keys[KEY_INPUT_W] == 1 || keys[KEY_INPUT_UP] == 1) || (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN] == 1)) {
						//�΂߈ړ��Ȃ�0.71�|����(0.71�����������炵��)
						playerSlowSpeed = 0.71f;
					}
					else {
						//��������Ȃ���Γ��{
						playerSlowSpeed = 1.0f;
					}
				}
				else if ((keys[KEY_INPUT_W] == 1 || keys[KEY_INPUT_UP] == 1) || (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN] == 1)) {
					//��������Ȃ���Γ��{
					playerSlowSpeed = 1.0f;
				}

				//�ړ�-----------------------WASD�ƃA���[�L�[�ǂ����ł������܂�------------------------
				if (isDead == 0) {
					//��
					if (keys[KEY_INPUT_W] == 1 || keys[KEY_INPUT_UP] == 1) {
						playerY -= PLAYER_SPEED * playerSlowSpeed;

						//�ォ�E
						if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1) {
							playerX += PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 45 * (PI / 180.0);
						}

						//�ォ��
						else if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1) {
							playerX -= PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 325 * (PI / 180.0);
						}

						//�㉺
						else if (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN] == 1) {
							playerY += PLAYER_SPEED * playerSlowSpeed;
						}
						else {
							playerAngle = 0.0f;
						}
					}

					//��
					else if (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN] == 1) {
						playerY += PLAYER_SPEED * playerSlowSpeed;

						//�����E
						if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1) {
							playerX += PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 135 * (PI / 180.0);
						}

						//������
						else if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1) {
							playerX -= PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 225 * (PI / 180.0);
						}
						else {
							playerAngle = 180 * (PI / 180.0);
						}
					}

					//��
					else if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1) {
						playerX -= PLAYER_SPEED * playerSlowSpeed;
						playerAngle = 270 * (PI / 180.0);
						if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1) {
							playerX += PLAYER_SPEED * playerSlowSpeed;
						}
					}

					//�E
					else if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1) {
						playerX += PLAYER_SPEED * playerSlowSpeed;
						playerAngle = 90 * (PI / 180.0);
					}
				}

				//---------------------PAD����---------------------
				if (InputX > 0 || InputX < 0) {
					if (InputY > 0 || InputY < 0) {
						playerSlowSpeed = 0.7f;
					}
					else {
						playerSlowSpeed = 1.0f;
					}
				}
				else if (InputY > 0 || InputY < 0) {
					playerSlowSpeed = 1.0f;
				}

				//�ړ�
				if (isDead == 0) {
					//��
					if (InputY < 0) {
						playerY -= PLAYER_SPEED * playerSlowSpeed;
						if (InputX >= 100) {
							playerX += PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 45 * (PI / 180.0);
						}
						else if (InputX <= -100) {
							playerX -= PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 325 * (PI / 180.0);
						}
						else {
							playerAngle = 0.0f;
						}
					}
					//��
					else if (InputY > 0) {
						playerY += PLAYER_SPEED * playerSlowSpeed;

						if (InputX >= 100) {
							playerX += PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 135 * (PI / 180.0);
						}
						else if (InputX <= -100) {
							playerX -= PLAYER_SPEED * playerSlowSpeed;
							playerAngle = 225 * (PI / 180.0);
						}
						else {
							playerAngle = 180 * (PI / 180.0);
						}

					}
					//�E
					else if (InputX > 0) {
						playerX += PLAYER_SPEED * playerSlowSpeed;
						playerAngle = 90 * (PI / 180.0);
					}
					//��
					else if (InputX < 0) {
						playerX -= PLAYER_SPEED * playerSlowSpeed;
						playerAngle = 270 * (PI / 180.0);
					}
				}

				//��ʒ[�A���E��
				if (playerX < 16 + 32) {
					playerX += PLAYER_SPEED * playerSlowSpeed;
				}
				if (playerX > 704 - 32) {
					playerX -= PLAYER_SPEED * playerSlowSpeed;
				}
				if (playerY < 420 + 32) {
					playerY += PLAYER_SPEED * playerSlowSpeed;
					lineAlpha -= 8;
				}
				if (playerY > 960 - 32) {
					playerY -= PLAYER_SPEED * playerSlowSpeed;
				}


				//�e����
				if (isStart == 1) {
					if (isShot == 0 && isFaled == 0 && boss.isAlive == 0 && isDead == 0) {
						bulletX = playerX;
						bulletY = playerY;

						//�t���O���Ăĉ��o�ɐؑ�
						if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || pad & PAD_INPUT_2) {
							isShot = 1;
							bulletTmpX = playerTmpX;
							bulletTmpY = playerTmpY;
							bulletLineX = playerX;
							bulletLineY = playerY;
							bulletSpeed = 4.5f;
							scene = 2;
						}
					}
				}

				//���ˌ�
				if (isShot == 1) {
					bulletY -= bulletSpeed;
					//�e���̐F�𔖂�
					bulletLineColor -= 8;

					//�O���@���@���j���s���o��
					if (bulletY < 0 && boss.isAlive == 0) {
						isFaled = 1;
					}

					bulletSpeed += 2.5f;
				}

				//�{�X1�̍��E�ړ�
				if (isStart == 1 && boss.isAlive == 0) {
					//�E�Ɉړ�
					if (boss.moveTypeX == 0) {
						bossCenterX += boss.speedX;
					}
					//���Ɉړ�
					else {
						bossCenterX -= boss.speedX;
					}
					//��Ɉړ�
					if (boss.moveTypeY == 0) {
						bossCenterY -= boss.speedY;
					}
					else {
						bossCenterY += boss.speedY;
					}
				}

				//�{�X�̃o���A�̈ʒu
				for (int i = 0; i < 2; i++) {
					bossBarrierX[0] = bossCenterX - 32;
					bossBarrierX[1] = bossCenterX + 32;
					bossBarrierY[i] = bossCenterY + 40;

					//�o���A�̃I���I�t
					if (isBarrierOpen == 1) {
						if (openTime > 0) {
							openTime--;
							if (openTime % 4 == 0) {
								barrierNum -= 0.1f;
							}
						}
					}
					else {
						if (openTime < 60) {
							openTime++;
							if (openTime % 4 == 0) {
								barrierNum += 0.1f;
							}
						}
					}
				}

				if (keys[KEY_INPUT_B] == 1 && oldkeys[KEY_INPUT_B] == 0) {
					if (isBarrierOpen == 0) {
						isBarrierOpen = 1;
					}
					else {
						isBarrierOpen = 0;
					}
				}

				//�{�X����ʊO�ɍs���Ȃ��悤�ɂ���
				//���ɍs���߂��Ȃ��悤�ɂ���
				if (bossCenterX - boss.r <= 32) {
					if (boss.moveTypeX == 1) {
						boss.moveTypeX = 0;
					}
				}

				//�E�ɍs���߂��Ȃ��悤�ɂ���
				if (bossCenterX + boss.r >= 688) {
					if (boss.moveTypeX == 0) {
						boss.moveTypeX = 1;
					}
				}

				//��ɍs���߂��Ȃ��悤�ɂ���
				if (bossCenterY - boss.r <= 50) {
					if (boss.moveTypeY == 0) {
						boss.moveTypeY = 1;
					}
				}

				//���ɍs���߂��Ȃ��悤�ɂ���
				if (bossCenterY + boss.r >= 400) {
					if (boss.moveTypeY == 1) {
						boss.moveTypeY = 0;
					}
				}

				//�{�X��]

				for (int i = 0; i < 4; i++) {
					//�p�x���擾
					bossRadius[i] = bossPartAngle[i] * (PI / 180.0f);

					//���S�_�Ƃ̋������v�Z
					bossAddX[i] = cos(bossRadius[i]) * bossLength;
					bossAddY[i] = sin(bossRadius[i]) * bossLength;

					//���ꂼ��̍��W�Ɍv�Z���ʂ���
					bossPartX[i] = (bossCenterX + bossAddX[i]);
					bossPartY[i] = (bossCenterY + bossAddY[i]);

					//��鑬�x
					if (boss.isAlive == 0) {
						bossPartAngle[i] += bossAngleSpeed;
					}


					//360�x�𒴂�����360����
					if (bossPartAngle[i] > 360) {
						bossPartAngle[i] -= 360;
					}



					//------------------------�{�X�����蔻��-------------------

					//����̃u���b�N
					if (isShot == 1) {
						if ((bossPartX[i] - 32) < (bulletX + BULLET_R) && (bulletX - BULLET_R) < (bossPartX[i] + 32)) {
							if ((bossPartY[i] - 32) < (bulletY + BULLET_R) && (bulletY - BULLET_R) < (bossPartY[i] + 32)) {
								if (isFaled == 0) {
									isFaled = 1;
									isShot = 0;
								}
							}
						}

						////��_
						if ((bulletX - bossCenterX) * (bulletX - bossCenterX) + (bulletY - bossCenterY) * (bulletY - bossCenterY) <= (BULLET_R + bossCenterR) * (BULLET_R + bossCenterR)) {
							if (isBarrierOpen == 1) {
								boss.isAlive = 1;
								isShot = 0;
								scene = 4;

								bossCenterTmpX = bossCenterX;
								bossCenterTmpY = bossCenterY;

								bossCenterX = 350.0f;
								bossCenterY = 480.0f;
								bossLength = 256.0f;

								bulletTmpX = 360;
								bulletTmpY = 960;
								bulletLineX = 360;
								bulletLineY = 960;
								bulletSpeedTmp = 4.5f;
							}
							else {
								isFaled = 1;
								isShot = 0;
							}
						}
					}
				}


				//�o���A
				if (isShot == 1 && isBarrierOpen == 0) {
					if ((bossBarrierX[0]) < (bulletX + BULLET_R) && (bulletX - BULLET_R) < (bossBarrierX[0] + bossBarrierR)) {
						if ((bossBarrierY[0]) < (bulletY + BULLET_R) && (bulletY - BULLET_R) < (bossBarrierY[0] + 16)) {
							if (isFaled == 0) {
								isFaled = 1;
								isShot = 0;
							}
						}
					}

					else if ((bossBarrierX[1] - bossBarrierR) < (bulletX + BULLET_R) && (bulletX - BULLET_R) < (bossBarrierX[1])) {
						if ((bossBarrierY[1]) < (bulletY + BULLET_R) && (bulletY - BULLET_R) < (bossBarrierY[1] + 16)) {
							if (isFaled == 0) {
								isFaled = 1;
								isShot = 0;
							}
						}
					}
				}

				//��ɍs������E�̃��C��
				if (playerY < 550 - PLAYER_R) {
					if (isLimit == 0) {
						isLimit = 1;
					}
					if (isLimit == 1 && playerY > 420 + PLAYER_R) {
						if (keys[KEY_INPUT_UP] == 1 || keys[KEY_INPUT_W] == 1 || InputY < 0) {
							lineAlpha += 8;
						}
						else if (keys[KEY_INPUT_DOWN] == 1 || keys[KEY_INPUT_S] == 1 || InputY > 0) {
							lineAlpha -= 8;
						}
					}
				}
				else {
					isLimit = 0;
					lineAlpha = 0;
				}



				//�V�[���`�F���W����Ƃ��Ɉꔑ����
				//����
				if (boss.isAlive == 1) {
					if (sceneTime == 0 && isShake == 0) {
						isShake = 1;
					}
					sceneTime++;
					if (sceneTime == 10) {
						isBossBomb[0] = 1;
					}
					if (sceneTime == 20) {
						isBossBomb[1] = 1;
					}
					if (sceneTime == 30) {
						isBossBomb[2] = 1;
					}
					if (sceneTime == 40) {
						isBossBomb[3] = 1;
					}
					if (sceneTime == 50) {
						isBossBomb[4] = 1;
						isBossBye[0] = 1;
					}
					if (sceneTime == 60) {
						isBossBomb[5] = 1;
					}
					if (sceneTime == 70) {
						isBossBomb[6] = 1;
					}
					if (sceneTime == 80) {
						isBossBomb[7] = 1;
					}
					if (sceneTime == 90) {
						isBossBomb[8] = 1;
					}
					if (sceneTime == 100) {
						isBossBomb[9] = 1;
						isBossBye[1] = 1;
					}

					if (sceneTime == 140) {
						isShake = 0;
					}

					if (sceneTime == 160) {
						sceneTime = 0;
						scene = 5;
					}

				}
				for (int i = 0; i < 10; i++) {
					if (isBossBomb[i] == 1) {
						bossBombTime[i]++;

						if (bossBombTime[i] == 10) {
							bossBombCount[i]++;
						}
						if (bossBombTime[i] == 20) {
							bossBombCount[i]++;
						}
						if (bossBombTime[i] == 30) {
							bossBombCount[i]++;
						}
						if (bossBombTime[i] == 40) {
							bossBombCount[i]++;
						}
						if (bossBombTime[i] == 50) {
							isBossBomb[i] = 0;
						}
					}
				}

				//���s
				if (isFaled == 1 && boss.isAlive == 0) {
					sceneTime++;

					if (sceneTime == 30) {
						sceneTime = 0;
						scene = 3;
					}
				}
				//���S
				if (isDead == 1 && boss.isAlive == 0) {
					sceneTime++;

					if (sceneTime == 10) {
						playerBombCount = 1;
					}
					if (sceneTime == 20) {
						playerBombCount = 2;
					}
					if (sceneTime == 30) {
						playerBombCount = 3;
					}
					if (sceneTime == 40) {
						playerBombCount = 4;
					}
					if (sceneTime == 50) {
						playerBombCount = 5;
					}

					if (sceneTime == 60) {
						sceneTime = 0;
						scene = 3;
					}
				}

				//�{�X�̒e�̏���------------------------------------------------------------------------
				for (int i = 0; i < BOSS_BULLET_CONST; i++) {
					//���݂��Ȃ��e�̏�����
					if (bossBullet[i].isShot == false) {
						bossBullet[i].x = bossCenterX;
						bossBullet[i].y = bossCenterY;
						bossBullet[i].shotType = false;
						bossBullet[i].recoilX = 0;
						bossBullet[i].recoilY = 0;
					}
					//��ʊO�ɏo���e�̏�����
					if (bossBullet[i].y >= WIN_HEIGHT && bossBullet[i].isShot == true) {
						bossBullet[i].isShot = false;
					}
					if (bossBullet[i].y <= 0 && bossBullet[i].isShot == true) {
						bossBullet[i].isShot = false;
					}
					if (bossBullet[i].x >= WIN_WIDTH && bossBullet[i].isShot == true) {
						bossBullet[i].isShot = false;
					}
					if (bossBullet[i].x <= 0 && bossBullet[i].isShot == true) {
						bossBullet[i].isShot = false;
					}

					//�e�̋���(shotType�ˑ�)
					if (bossBullet[i].isShot == true) {
						//�V���b�g�^�C�v1�̎�
						if (bossBullet[i].shotType == 1 || bossBullet[i].shotType == 8) {
							if (i % 5 == 0) {
								bossBullet[i].y += 5;
							}
							else if (i % 5 == 1) {
								bossBullet[i].x -= 2;
								bossBullet[i].y += 4;
							}
							else if (i % 5 == 2) {
								bossBullet[i].x += 2;
								bossBullet[i].y += 4;
							}
							else if (i % 5 == 3) {
								bossBullet[i].x -= 4;
								bossBullet[i].y += 2;
							}
							else if (i % 5 == 4) {
								bossBullet[i].x += 4;
								bossBullet[i].y += 2;
							}
						}
						//�V���b�g�^�C�v2�̎�
						else if (bossBullet[i].shotType == 2 || bossBullet[i].shotType == 15) {
							bossBullet[i].x += bossBullet[i].recoilX;
							bossBullet[i].y += 5;
						}
						//�V���b�g�^�C�v3.4.6.9.12.13.14�̂Ƃ�
						else if (bossBullet[i].shotType == 3 || bossBullet[i].shotType == 4 || bossBullet[i].shotType == 6 || bossBullet[i].shotType == 9 || bossBullet[i].shotType == 8 || bossBullet[i].shotType == 12 || bossBullet[i].shotType == 13 || bossBullet[i].shotType == 14) {
							bossBullet[i].x += bossBullet[i].recoilX;
							bossBullet[i].y += bossBullet[i].recoilY;
						}
						else if (bossBullet[i].shotType == 11) {
							bossBullet[i].y += 3;
						}
					}
				}

				//�{�X�̍s��(attackType�ˑ�)------------------------------------------------------------------
				//�{�X�^�C�}�[�̌���(�f�o�b�N���őҋ@���̓^�C�}�[�������Ȃ�)
				if (isDebug == false || boss.attackType != 0) {
					boss.attackTimer--;
				}

				//�f�o�b�O���̑���̍s������
				if (isDebug == true) {
					//0�L�[�Ń��Z�b�g
					if (keys[KEY_INPUT_0] == 1 && oldkeys[KEY_INPUT_0] == 0) {
						//�S�����Z�b�g
						isRetry = 1;
						isShot = 0;
						isFaled = 0;
						playerTmpX = 350.0f;
						playerTmpY = 650.0f;
						bulletY = 1000.0f;
						bulletSpeed = 0;
						sceneTime = 0;
						alpha = 0;
						bulletLineX = 0.0f;
						bulletLineY = 0.0f;
						bulletLineColor = 255;
						bossCenterX = 350.0f;
						bossCenterY = 200.0f;
						bossAngleSpeed = 20.0f;
						bossLength = 0.0f;
						isBarrierOpen = 0;
						openTime = 60;
						bossBarrierR = 32.0f;
						beamRand = 0;
						circleNumber = 0;
						trap = false;
						isPlay = 0;
						isStart = 0;
						trapEx = -1;
						bossMoveTime = 0;
						bossMoveCount = 0;
						oldSceneType = 0;
						oldBeam = -1;
						oldBeam2_1 = -1;
						oldBeam2_2 = -1;
						playerAngle = 0.0f;
						playerBombCount = 0;
						isDead = 0;
						lineAlpha = 0;
						isLimit = 0;
						randX = 0;
						isShake = 0;
						barrierNum = 1.5f;

						//���g���C���Ƀ{�X����u�`�J�b�Ƃ���̂�j�~
						for (int i = 0; i < 4; i++) {
							bossAddX[i] = cos(bossRadius[i]) * bossLength;
							bossAddY[i] = sin(bossRadius[i]) * bossLength;

							bossPartX[i] = (bossCenterX + bossAddX[i]);
							bossPartY[i] = (bossCenterY + bossAddY[i]);
						}

						boss = {
							300.0f,		//X���W
							200.0f,		//Y���W
							150,		//���a
							0.0f,		//�{�X�̒��̉摜�̉�]
							2.0f,		//X����
							0.5f,		//Y����
							0,			//���E�ړ�(0�Ȃ�E�A1�Ȃ獶)
							0,			//�㉺�ړ�(0�Ȃ��A1�Ȃ牺)
							0,			//�U�����(0�Ȃ�ҋ@�A����ȊO�Ȃ�Ή������s��)
							250,		//�U���̃^�C�}�[�Ǘ�
							false		//���݂��Ă��邩(true�Ȃ瑶�݂���Afalse�Ȃ瑶�݂��Ȃ�)
						};

						for (int i = 0; i < BOSS_BULLET_CONST; i++) {
							bossBullet[i] = {
								bossCenterX,		//X���W
								bossCenterY,		//Y���W
								16,			//���a
								false,		//���݂��Ă��邩(true�Ȃ瑶�݂���Afalse�Ȃ瑶�݂��Ȃ�)
								0,			//�e�̋����̎��
								0,			//�e�̗�����ۑ�
								0
							};
						}

						for (int i = 0; i < OLD_PLAYER_MAX; i++) {
							oldPlayerX[i] = 0;
							oldPlayerY[i] = 0;
						}

						for (int i = 0; i < LINE_CONST; i++) {
							line[i] = {
								0,		//x���W
								0,		//y���W
								false	//���݂��Ă��邩
							};
						}

						for (int i = 0; i < CIRCLE_CONST; i++) {
							circle[i] = {
								0,		//x���W
								0,		//y���W
								false	//���݂��Ă��邩
							};
						}

						for (int i = 0; i < BEAM_CONST; i++) {
							beam[i] = {
								0,		//�r�[���̏��(0�Ȃ疳�A1�Ȃ�\���A2�Ȃ甭��)
								0		//�^�C�}�[
							};
						}

						//�{�X�o���A
						for (int i = 0; i < 2; i++) {
							bossBarrierX[0] = bossCenterX - 32;
							bossBarrierX[1] = bossCenterX + 32;
							bossBarrierY[i] = bossCenterY + 40;
						}

						//�������o
						for (int i = 0; i < 10; i++) {
							bossBombTime[i] = 0;
							bossBombCount[i] = 0;
							isBossBomb[i] = 0;
						}
						for (int i = 0; i < 2; i++) {
							isBossBye[i] = 0;
						}

						//���Z�b�g�t���O��߂�
						isReset = 0;
					}
					//1�L�[�ōs��1�N��
					if (keys[KEY_INPUT_1] == 1 && oldkeys[KEY_INPUT_1] == 0) {
						boss.attackType = 1;
						boss.attackTimer = timer1;
					}
					//2�L�[�ōs��2�N��
					if (keys[KEY_INPUT_2] == 1 && oldkeys[KEY_INPUT_2] == 0) {
						boss.attackType = 2;
						boss.attackTimer = timer2;
					}
					//3�L�[�ōs��3�N��
					if (keys[KEY_INPUT_3] == 1 && oldkeys[KEY_INPUT_3] == 0) {
						boss.attackType = 3;
						boss.attackTimer = timer3;
					}
					//4�L�[�ōs��4�N��
					if (keys[KEY_INPUT_4] == 1 && oldkeys[KEY_INPUT_4] == 0) {
						boss.attackType = 4;
						boss.attackTimer = timer4;
					}
					//5�L�[�ōs��5�N��
					if (keys[KEY_INPUT_5] == 1 && oldkeys[KEY_INPUT_5] == 0) {
						boss.attackType = 5;
						boss.attackTimer = timer5;
					}
					//6�L�[�ōs��6�N��
					if (keys[KEY_INPUT_6] == 1 && oldkeys[KEY_INPUT_6] == 0) {
						boss.attackType = 6;
						boss.attackTimer = timer6;
						circleNumber = 0;
					}
					//8�L�[�ōs��8�N��
					if (keys[KEY_INPUT_8] == 1 && oldkeys[KEY_INPUT_8] == 0) {
						boss.attackType = 8;
						boss.attackTimer = timer8;
						circleNumber = 0;
					}
					//9�L�[�ōs��9�N��
					if (keys[KEY_INPUT_9] == 1 && oldkeys[KEY_INPUT_9] == 0) {
						boss.attackType = 9;
						boss.attackTimer = timer6;
						circleNumber = 0;
					}

					//Q�L�[�ōs��11�N��
					if (keys[KEY_INPUT_Q] == 1 && oldkeys[KEY_INPUT_Q] == 0) {
						boss.attackType = 11;
						boss.attackTimer = timer11;
					}
					//E�L�[�ōs��12�N��
					if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0) {
						boss.attackType = 12;
						boss.attackTimer = timer12;
					}
				}

				if (isStart == 1 && boss.isAlive == 0) {
					switch (boss.attackType) {
						//�ҋ@��Ԏ� �s�����I
						case 0:
							//�o�O�h�~�ŃA�^�b�N�^�C�}�[��0�ȉ��ɂȂ�Ȃ��悤�ɂ���
							if (boss.attackTimer <= 0) {
								boss.attackTimer == 0;
							}
							//�ړ����x�̏�����
							boss.speedX = 2.0f;
							boss.speedY = 0.5f;

							bossMoveTime = 0;
							bossMoveCount = 0;

							if (eyeState == 2) {
								bossAngleSpeed = 5.0f;
							}
							else if (eyeState == 1) {
								bossAngleSpeed = 20.0f;
							}
							else {
								bossAngleSpeed = 15.0f;
							}

							//���S�Ƃ̋��������ɖ߂�
							if (bossLength < 128) {
								bossLength += 2.0f;
							}
							if (bossLength > 128) {
								bossLength -= 2.0f;
							}


							//�{�X�^�C�}�[��0�̎�
							if (boss.attackTimer <= 0) {
								//�{�X�̃A�^�b�N�^�C�v���I
								//1�O�̃V�[���Ɠ����U�������Ȃ��悤�ɏ���
								for (int i = 0; i < 10; i++) {
									if (trapEx == sceneCount) {
										boss.attackType = 9;
									}
									else if (sceneCount % 5 == 0 && sceneCount >= 5) {
										boss.attackType = 8;
									}
									else {
										boss.attackType = rand() % 8 + 1;

										if (boss.attackType == 8) {
											boss.attackType = 11;
										}
									}
									if (sceneCount % 5 == 4 && (boss.attackType == 6 || boss.attackType == 7)) {}
									else if (boss.attackType != oldSceneType) {
										break;
									}
								}
								//�A�^�b�N�^�C�v�ʂɑҋ@��Ԃɖ߂�܂ł̎��Ԃ�ݒ�
								if (boss.attackType == 1) {
									boss.attackTimer = timer1;
								}
								else if (boss.attackType == 2) {
									boss.attackTimer = timer2;
								}
								else if (boss.attackType == 3) {
									boss.attackTimer = timer3;
								}
								else if (boss.attackType == 4) {
									boss.attackTimer = timer4;
								}
								else if (boss.attackType == 5) {
									boss.attackTimer = timer5;
								}
								else if (boss.attackType == 6) {
									boss.attackTimer = timer6;
								}
								else if (boss.attackType == 8) {
									boss.attackTimer = timer8;
								}
								else if (boss.attackType == 9) {
									boss.attackTimer = timer6;
								}

								//�{�X�̑̒�
								if (sceneCount < 5 && sceneCount >= 2) {
									eyeState = 1;
									partState = 1;
									barrierState = 1;
								}
								else if (sceneCount < 2) {
									eyeState = 0;
								}
							}
							break;
							//�ʏ�̊g�U�e
						case 1:
							isBarrierOpen = 1;
							//oldSceneType��ݒ�
							oldSceneType = 1;
							//�{�X����
							bossAngleSpeed = 3.0f;
							if (bossMoveTime > 7) {
								bossMoveTime++;
								bossLength += 16;

								if (bossMoveTime == 16) {
									bossMoveTime = 0;
								}
							}
							else {
								bossMoveTime++;
								bossLength -= 16;
							}

							//�e���ˏo
							if (boss.attackTimer % 30 == 1) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0 && bossBullet[i + 1].isShot == 0 && bossBullet[i + 2].isShot == 0 && bossBullet[i + 3].isShot == 0 &&
										bossBullet[i + 4].isShot == 0 && bossBullet[i + 5].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 1;
										bossBullet[i + 1].isShot = 1;
										bossBullet[i + 1].shotType = 1;
										bossBullet[i + 2].isShot = 1;
										bossBullet[i + 2].shotType = 1;
										bossBullet[i + 3].isShot = 1;
										bossBullet[i + 3].shotType = 1;
										bossBullet[i + 4].isShot = 1;
										bossBullet[i + 4].shotType = 1;
										bossBullet[i + 5].isShot = 1;
										bossBullet[i + 5].shotType = 1;
										break;
									}
								}
							}
							//attackTimer��0�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= 0) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								sceneCount++;
								isBarrierOpen = 0;
							}
							break;
							//�����ł̂΂�܂��e
						case 2:
							//oldSceneType��ݒ�
							oldSceneType = 2;
							//�{�X����
							if (bossMoveTime == 0) {
								bossAngleSpeed = 5.0f;
								bossMoveTime++;
							}
							else if (bossAngleSpeed < 35.0f) {
								bossAngleSpeed += 0.2f;
							}

							if (boss.attackTimer % 5 == 1) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 2;
										bossBullet[i].recoilX = rand() % 9 - 4;
										break;
									}
								}
							}

							//attackTimer��0�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= 0) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								sceneCount++;
							}
							break;
							//���@�_���r�[��
						case 3:
							//oldSceneType��ݒ�
							oldSceneType = 3;
							//�{�X�̓������~�߂�
							boss.speedX = 0;
							boss.speedY = 0;
							//�{�X����
							if (bossAngleSpeed > 2.5f) {
								bossAngleSpeed -= 1.0f;
							}
							//�\�����̕\��
							if (boss.attackTimer <= 450 && boss.attackTimer >= 440) {
								line[0].x = playerX;
								line[0].y = playerY;
								line[0].isLine = true;
							}
							if (boss.attackTimer <= 420 && boss.attackTimer >= 410) {
								line[1].x = playerX;
								line[1].y = playerY;
								line[1].isLine = true;
							}
							if (boss.attackTimer <= 390 && boss.attackTimer >= 380) {
								line[2].x = playerX;
								line[2].y = playerY;
								line[2].isLine = true;
								isBarrierOpen = 1;
							}
							if (boss.attackTimer <= 360 && boss.attackTimer >= 350) {
								line[3].x = playerX;
								line[3].y = playerY;
								line[3].isLine = true;
							}
							if (boss.attackTimer <= 330 && boss.attackTimer >= 320) {
								line[4].x = playerX;
								line[4].y = playerY;
								line[4].isLine = true;
							}
							if (boss.attackTimer <= 300 && boss.attackTimer >= 290) {
								line[5].x = playerX;
								line[5].y = playerY;
								line[5].isLine = true;
							}
							//�\�����ɉ������e�𔭎�
							if (boss.attackTimer <= 440 && boss.attackTimer >= 420) {
								for (int i = 400; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 3;
										bossBullet[i].recoilX = (line[0].x - bossCenterX) / sqrt(((line[0].x - bossCenterX) * (line[0].x - bossCenterX)) + ((line[0].y - bossCenterY) * (line[0].y - bossCenterY))) * 20;
										bossBullet[i].recoilY = (line[0].y - bossCenterY) / sqrt(((line[0].x - bossCenterX) * (line[0].x - bossCenterX)) + ((line[0].y - bossCenterY) * (line[0].y - bossCenterY))) * 20;
										break;
									}
								}
							}
							if (boss.attackTimer <= 410 && boss.attackTimer >= 390) {
								for (int i = 500; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 3;
										bossBullet[i].recoilX = (line[1].x - bossCenterX) / sqrt(((line[1].x - bossCenterX) * (line[1].x - bossCenterX)) + ((line[1].y - bossCenterY) * (line[1].y - bossCenterY))) * 20;
										bossBullet[i].recoilY = (line[1].y - bossCenterY) / sqrt(((line[1].x - bossCenterX) * (line[1].x - bossCenterX)) + ((line[1].y - bossCenterY) * (line[1].y - bossCenterY))) * 20;
										break;
									}
								}
							}
							if (boss.attackTimer <= 380 && boss.attackTimer >= 360) {
								for (int i = 600; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 3;
										bossBullet[i].recoilX = (line[2].x - bossCenterX) / sqrt(((line[2].x - bossCenterX) * (line[2].x - bossCenterX)) + ((line[2].y - bossCenterY) * (line[2].y - bossCenterY))) * 20;
										bossBullet[i].recoilY = (line[2].y - bossCenterY) / sqrt(((line[2].x - bossCenterX) * (line[2].x - bossCenterX)) + ((line[2].y - bossCenterY) * (line[2].y - bossCenterY))) * 20;
										break;
									}
								}
							}
							if (boss.attackTimer <= 350 && boss.attackTimer >= 330) {
								for (int i = 700; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 3;
										bossBullet[i].recoilX = (line[3].x - bossCenterX) / sqrt(((line[3].x - bossCenterX) * (line[3].x - bossCenterX)) + ((line[3].y - bossCenterY) * (line[3].y - bossCenterY))) * 20;
										bossBullet[i].recoilY = (line[3].y - bossCenterY) / sqrt(((line[3].x - bossCenterX) * (line[3].x - bossCenterX)) + ((line[3].y - bossCenterY) * (line[3].y - bossCenterY))) * 20;
										break;
									}
								}
							}
							if (boss.attackTimer <= 320 && boss.attackTimer >= 300) {
								for (int i = 800; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 3;
										bossBullet[i].recoilX = (line[4].x - bossCenterX) / sqrt(((line[4].x - bossCenterX) * (line[4].x - bossCenterX)) + ((line[4].y - bossCenterY) * (line[4].y - bossCenterY))) * 20;
										bossBullet[i].recoilY = (line[4].y - bossCenterY) / sqrt(((line[4].x - bossCenterX) * (line[4].x - bossCenterX)) + ((line[4].y - bossCenterY) * (line[4].y - bossCenterY))) * 20;
										break;
									}
								}
							}
							if (boss.attackTimer <= 290 && boss.attackTimer >= 270) {
								for (int i = 900; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 3;
										bossBullet[i].recoilX = (line[5].x - bossCenterX) / sqrt(((line[5].x - bossCenterX) * (line[5].x - bossCenterX)) + ((line[5].y - bossCenterY) * (line[5].y - bossCenterY))) * 20;
										bossBullet[i].recoilY = (line[5].y - bossCenterY) / sqrt(((line[5].x - bossCenterX) * (line[5].x - bossCenterX)) + ((line[5].y - bossCenterY) * (line[5].y - bossCenterY))) * 20;
										break;
									}
								}
							}

							//�\�����̍폜
							if (boss.attackTimer == 430) {
								line[0].isLine = false;
							}
							if (boss.attackTimer == 400) {
								line[1].isLine = false;
							}
							if (boss.attackTimer == 370) {
								line[2].isLine = false;
							}
							if (boss.attackTimer == 340) {
								line[3].isLine = false;
							}
							if (boss.attackTimer == 310) {
								line[4].isLine = false;
							}
							if (boss.attackTimer == 280) {
								line[5].isLine = false;
							}

							//attackTimer��200�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= 250) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								sceneCount++;
								isBarrierOpen = 0;
								for (int i = 0; i < 6; i++) {
									line[i] = { 0,0,false };
								}
							}
							break;
							//�����_���r�[��
						case 4:
							//oldSceneType��ݒ�
							oldSceneType = 4;
							//�ړ����x�̏�����
							boss.speedX = 2.0f;
							boss.speedY = 0.5f;
							//�{�X����
							if (bossAngleSpeed < 20.0f) {
								bossAngleSpeed += 0.5f;
							}

							//�\�������o���Ă���ԁA�{�X�̓������~�߂�
							if (line[0].isLine == true) {
								boss.speedX = 0.0f;
								boss.speedY = 0.0f;
							}
							//�����_���ɗ\�������o��
							if (boss.attackTimer == 450 || boss.attackTimer == 370 || boss.attackTimer == 290) {
								for (int i = 0; i < LINE_CONST; i++) {
									line[i].x = rand() % 720;
									line[i].y = rand() % 300 + 600;
									line[i].isLine = true;
								}
							}
							//�\�����ɉ������e�𔭎�
							if ((boss.attackTimer <= 420 && boss.attackTimer >= 400) || (boss.attackTimer <= 340 && boss.attackTimer >= 320) || (boss.attackTimer <= 260 && boss.attackTimer >= 240)) {
								for (int j = 0; j < LINE_CONST; j++) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 4;
											bossBullet[i].recoilX = (line[j].x - bossCenterX) / 20;
											bossBullet[i].recoilY = (line[j].y - bossCenterY) / 20;

											bossAngleSpeed = 2.0f;
											break;
										}
									}
								}
							}
							//�\�������폜
							if (boss.attackTimer == 410 || boss.attackTimer == 330 || boss.attackTimer == 250) {
								for (int i = 0; i < LINE_CONST; i++) {
									line[i].isLine = false;
								}
							}
							//attackTimer��220�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= 220) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								sceneCount++;
								for (int i = 0; i < LINE_CONST; i++) {
									line[i] = { 0,0,false };
								}
							}
							break;
							//�͈͍U��
						case 5:
							//oldSceneType��ݒ�
							oldSceneType = 5;
							//�{�X����
							if (bossLength > 32 && bossMoveTime == 0) {
								bossLength -= 2.0f;
							}
							if (bossMoveTime > 0) {
								bossLength += 16.0f;
								bossMoveTime--;
							}
							if (boss.attackTimer == 945) {
								bossAngleSpeed = 1.0f;
								isBarrierOpen = 1;
							}

							//�r�[���̏ꏊ����
							//1����
							if (boss.attackTimer == 900 || boss.attackTimer == 800 || boss.attackTimer == 710 || boss.attackTimer == 620) {
								for (int i = 0; i < 10; i++) {
									beamRand = rand() % 6;
									//���Ȃ��悤��
									if (beamRand != oldBeam) {
										break;
									}
								}
								oldBeam = beamRand;
								beam[beamRand].state = 1;
								beam[beamRand].timer = BEAM_TIME1_2;
								bossMoveCount = 1;
							}

							//2����
							if (boss.attackTimer == 540 || boss.attackTimer == 460 || boss.attackTimer == 390 || boss.attackTimer == 320) {
								for (int i = 0; i < 10; i++) {
									beamRand = rand() % 3;
									if (beamRand != oldBeam2_1) {
										break;
									}
								}
								beam[beamRand].state = 1;
								beam[beamRand].timer = BEAM_TIME1_2;
								oldBeam2_1 = beamRand;
								for (int i = 0; i < 10; i++) {
									beamRand = rand() % 3 + 3;
									if (beamRand != oldBeam2_2) {
										break;
									}
								}
								beam[beamRand].state = 1;
								beam[beamRand].timer = BEAM_TIME1_2;
								oldBeam2_2 = beamRand;
								bossMoveCount = 2;
							}

							//���X�g��4�ӏ�
							if (boss.attackTimer == 240) {
								beam[0].state = 1;
								beam[0].timer = BEAM_TIME1_2;
								beam[2].state = 1;
								beam[2].timer = BEAM_TIME1_2;
								beam[3].state = 1;
								beam[3].timer = BEAM_TIME1_2;
								beam[5].state = 1;
								beam[5].timer = BEAM_TIME1_2;
								bossMoveCount = 3;
							}

							//attackTimer��130�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= 130) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								sceneCount++;
								oldBeam = 0;
								isBarrierOpen = 0;
							}
							break;
							//�ݒu�^�e
						case 6:
						case 7:
							//oldSceneType��ݒ�
							oldSceneType = 6;
							//�{�X�̓������~�߂�
							boss.speedX = 0.0f;
							boss.speedY = 0.0f;

							if (trap == false) {

								//�e�̐ݒu�ʒu����
								if (boss.attackTimer == 400 || boss.attackTimer == 395 || boss.attackTimer == 390 || boss.attackTimer == 385 || boss.attackTimer == 380 ||
									boss.attackTimer == 375 || boss.attackTimer == 370 || boss.attackTimer == 365 || boss.attackTimer == 360 || boss.attackTimer == 355 ||
									boss.attackTimer == 350 || boss.attackTimer == 345 || boss.attackTimer == 340 || boss.attackTimer == 335 || boss.attackTimer == 330 ||
									boss.attackTimer == 325 || boss.attackTimer == 320 || boss.attackTimer == 315 || boss.attackTimer == 310 || boss.attackTimer == 305 || boss.attackTimer == 300) {
									line[0].x = rand() % 720;
									line[0].y = rand() % 560 + 400;
									line[0].isLine = true;
									circle[circleNumber].x = line[0].x;
									circle[circleNumber].y = line[0].y;
									circle[circleNumber].isCircle = true;
									if (circleNumber < 20) {
										circleNumber++;
									}
								}
								//�\�����̍폜
								if (boss.attackTimer == 290) {
									line[0].isLine = false;
								}
								//�e����
								if (boss.attackTimer == 250) {
									for (int j = 0; j < CIRCLE_CONST; j++) {
										for (int i = 0; i < BOSS_BULLET_CONST; i++) {
											if (bossBullet[i].isShot == 0) {
												bossBullet[i].isShot = 1;
												bossBullet[i].shotType = 6;
												bossBullet[i].recoilX = (circle[j].x - bossCenterX) / 100;
												bossBullet[i].recoilY = (circle[j].y - bossCenterY) / 100;
												break;
											}
										}
									}
								}
								//�e��ݒu�Ɨ\���~�̍폜
								if (boss.attackTimer == 150) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].shotType == 6) {
											bossBullet[i].shotType = 0;
										}
									}
									for (int i = 0; i < CIRCLE_CONST; i++) {
										circle[i].isCircle = false;
									}
									trapEx = sceneCount + 3;
								}
								//attackTimer��0�ɂȂ������A�ҋ@��Ԃɖ߂�
								if (boss.attackTimer <= 120) {
									boss.attackType = 0;
									boss.attackTimer = timer0;
									circleNumber = 0;
									sceneCount++;
									//����p
									trap = true;
								}
							}
							else {

								//attackTimer��500�ɂȂ������A�ҋ@��Ԃɖ߂�
								if (boss.attackTimer <= 500) {
									boss.attackType = 0;
									boss.attackTimer = timer0;
									circleNumber = 0;
								}
							}
							break;

							//����U��
						case 8:
							//�U���`���[�g(�Œ�)3000�X�^�[�g

							//�{�X�̑̒�
							if (boss.attackTimer == 400) {
								eyeState = 2;
								partState = 2;
								barrierState = 0;
								bossAngleSpeed = 8.0f;
							}
							//�{�X�̋���
							if (bossLength > 32 && bossMoveTime == 0 && boss.attackTimer > 1350) {
								bossLength -= 2.0f;
							}
							else if (bossLength < 128 && bossMoveTime == 0 && boss.attackTimer <= 1350 && boss.attackTimer > 100) {
								bossLength += 2;
							}
							else if (bossMoveTime > 0) {
								bossLength += 16.0f;
								bossMoveTime--;
							}

							if (bossCenterX == 360 && boss.attackTimer <= 2500) {
								boss.speedX = 0.0f;
								boss.speedY = 0.0f;
							}
							if (bossLength > 32 && boss.attackTimer <= 50 && boss.attackTimer > 0) {
								bossLength -= 2.0f;
								bossAngleSpeed = 0.0f;
								bossPartAngle[0] = 45.0f;
								bossPartAngle[1] = 135.0f;
								bossPartAngle[2] = 225.0f;
								bossPartAngle[3] = 315.0f;
							}
							if (boss.attackTimer <= -70 && boss.attackTimer > -500) {
								if (boss.attackTimer % 2 == 0) {
									bossLength -= 16;
								}
								if (boss.attackTimer % 2 == -1) {
									bossLength += 16;
								}
							}
							if (boss.attackTimer < -550) {
								bossAngleSpeed = 2.0f;
								bossLength--;
							}


							//�r�[���ƒe�̍���------------------------(2950~2500)-----------------
							if (boss.attackTimer <= 2950 && boss.attackTimer >= 2500) {
								if (boss.attackTimer % 30 == 1) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0 && bossBullet[i + 1].isShot == 0 && bossBullet[i + 2].isShot == 0 && bossBullet[i + 3].isShot == 0 &&
											bossBullet[i + 4].isShot == 0 && bossBullet[i + 5].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 1;
											bossBullet[i + 1].isShot = 1;
											bossBullet[i + 1].shotType = 1;
											bossBullet[i + 2].isShot = 1;
											bossBullet[i + 2].shotType = 1;
											bossBullet[i + 3].isShot = 1;
											bossBullet[i + 3].shotType = 1;
											bossBullet[i + 4].isShot = 1;
											bossBullet[i + 4].shotType = 1;
											bossBullet[i + 5].isShot = 1;
											bossBullet[i + 5].shotType = 1;
											break;
										}
									}
									if (isBarrierOpen == 0) {
										isBarrierOpen = 1;
									}
								}
								//�r�[���̏ꏊ����
								//1����
								if (boss.attackTimer % 100 == 0) {
									for (int i = 0; i < 10; i++) {
										beamRand = rand() % 6;
										//���Ȃ��悤��
										if (beamRand != oldBeam) {
											break;
										}
									}
									oldBeam = beamRand;
									beam[beamRand].state = 1;
									beam[beamRand].timer = BEAM_TIME1_2;
									bossMoveCount = 1;
								}
							}

							//�r�[���ƒe�̍���------------------------(2499~2200)-----------------
							if (boss.attackTimer <= 2499 && boss.attackTimer >= 2200) {
								if (boss.attackTimer % 5 == 1) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 2;
											bossBullet[i].recoilX = rand() % 9 - 4;
											break;
										}
									}
								}
								//�r�[���̏ꏊ����
								//1����
								if (boss.attackTimer % 100 == 0) {
									for (int i = 0; i < 10; i++) {
										beamRand = rand() % 6;
										//���Ȃ��悤��
										if (beamRand != oldBeam) {
											break;
										}
									}
									oldBeam = beamRand;
									beam[beamRand].state = 1;
									beam[beamRand].timer = BEAM_TIME1_2;
									bossMoveCount = 1;
								}
							}

							//�����_���r�[���A��------------------------(2100~1900)-----------------
							if (boss.attackTimer <= 2100 && boss.attackTimer >= 1800) {
								//�r�[���̏ꏊ����
								//2����
								if (boss.attackTimer % 75 == 0) {
									for (int i = 0; i < 10; i++) {
										beamRand = rand() % 3;
										if (beamRand != oldBeam2_1) {
											break;
										}
									}
									beam[beamRand].state = 1;
									beam[beamRand].timer = BEAM_TIME1_2;
									oldBeam2_1 = beamRand;
									for (int i = 0; i < 10; i++) {
										beamRand = rand() % 3 + 3;
										if (beamRand != oldBeam2_2) {
											break;
										}
									}
									beam[beamRand].state = 1;
									beam[beamRand].timer = BEAM_TIME1_2;
									oldBeam2_2 = beamRand;
									bossMoveCount = 2;
								}
							}

							//�w��r�[���A��------------------------(1700~1400)-----------------
							if (boss.attackTimer <= 1700 && boss.attackTimer >= 1400) {
								if (boss.attackTimer == 1700) {
									beam[0].state = 1;
									beam[0].timer = BEAM_TIME1_2;
								}
								if (boss.attackTimer == 1660) {
									beam[1].state = 1;
									beam[1].timer = BEAM_TIME1_2;
								}
								if (boss.attackTimer == 1620) {
									beam[2].state = 1;
									beam[2].timer = BEAM_TIME1_2;
								}
								if (boss.attackTimer == 1500) {
									beam[2].state = 1;
									beam[2].timer = BEAM_TIME1_2;
								}
								if (boss.attackTimer == 1460) {
									beam[1].state = 1;
									beam[1].timer = BEAM_TIME1_2;
								}
								if (boss.attackTimer == 1420) {
									beam[0].state = 1;
									beam[0].timer = BEAM_TIME1_2;
								}
							}

							//�g�U�e���~��---------------------(1400~1000)-----------------------
							if (boss.attackTimer <= 1400 && boss.attackTimer >= 1200) {
								//�e���ˏo
								if (boss.attackTimer % 30 == 1) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0 && bossBullet[i + 1].isShot == 0 && bossBullet[i + 2].isShot == 0 && bossBullet[i + 3].isShot == 0 &&
											bossBullet[i + 4].isShot == 0 && bossBullet[i + 5].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 1;
											bossBullet[i + 1].isShot = 1;
											bossBullet[i + 1].shotType = 1;
											bossBullet[i + 2].isShot = 1;
											bossBullet[i + 2].shotType = 1;
											bossBullet[i + 3].isShot = 1;
											bossBullet[i + 3].shotType = 1;
											bossBullet[i + 4].isShot = 1;
											bossBullet[i + 4].shotType = 1;
											bossBullet[i + 5].isShot = 1;
											bossBullet[i + 5].shotType = 1;
											break;
										}
									}
								}
								if (isBarrierOpen == 1) {
									isBarrierOpen = 0;
								}
							}


							if (boss.attackTimer <= 1300 && boss.attackTimer >= 1200) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 1) {
										bossBullet[i].shotType = 1;
										if (boss.attackTimer % 20 == 1 || boss.attackTimer % 20 == 2 || boss.attackTimer % 20 == 3) {
											bossBullet[i].shotType = 8;
										}
									}
								}
							}

							if (boss.attackTimer == 1200) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									bossBullet[i].shotType = 0;
								}
							}
							//���~�ߒ�---------------------(1100~750)-----------------------
							if (boss.attackTimer <= 1100 && boss.attackTimer >= 750) {
								//�\�������o���Ă���ԁA�{�X�̓������~�߂�
								if (line[0].isLine == true) {
									boss.speedX = 0.0f;
									boss.speedY = 0.0f;
								}
								//�����_���ɗ\�������o��
								if (boss.attackTimer == 1050 || boss.attackTimer == 900) {
									for (int i = 0; i < LINE_CONST; i++) {
										line[i].x = rand() % 720;
										line[i].y = rand() % 300 + 600;
										line[i].isLine = true;
									}
								}
								//�\�����ɉ������e�𔭎�
								if ((boss.attackTimer <= 950 && boss.attackTimer >= 930) || (boss.attackTimer <= 800 && boss.attackTimer >= 780)) {
									for (int j = 0; j < LINE_CONST; j++) {
										for (int i = 0; i < BOSS_BULLET_CONST; i++) {
											if (bossBullet[i].isShot == 0) {
												bossBullet[i].isShot = 1;
												bossBullet[i].shotType = 4;
												bossBullet[i].recoilX = (line[j].x - bossCenterX) / 20;
												bossBullet[i].recoilY = (line[j].y - bossCenterY) / 20;
												break;
											}
										}
									}
								}
								//�\�������폜
								if (boss.attackTimer == 930 || boss.attackTimer == 780) {
									for (int i = 0; i < LINE_CONST; i++) {
										line[i].x = 0;
										line[i].y = 0;
										line[i].isLine = false;
									}
								}
							}

							//���~�߉���---------------------(700~600)-----------------------

							//�e�g�U�\��
							if (boss.attackTimer <= 700 && boss.attackTimer >= 600) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									bossBullet[i].shotType = 0;
									if (boss.attackTimer % 20 == 1 || boss.attackTimer % 20 == 2 || boss.attackTimer % 20 == 3) {
										bossBullet[i].shotType = 9;
									}
								}

								//�g�U
								if (boss.attackTimer == 600) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										bossBullet[i].recoilX = rand() % 7 - 3;
										bossBullet[i].recoilY = rand() % 7 - 3;
										if (bossBullet[i].recoilX >= 0 && bossBullet[i].recoilX <= 1) {
											bossBullet[i].recoilX += 1;
										}
										if (bossBullet[i].recoilY >= 0 && bossBullet[i].recoilY <= 1) {
											bossBullet[i].recoilY += 1;
										}
										bossBullet[i].shotType = 6;
									}
								}
							}

							//���~�ߊg�U---------------------(550~350)-----------------------
							if (boss.attackTimer <= 550 && boss.attackTimer >= 350) {
								if (boss.attackTimer % 5 == 1) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 2;
											bossBullet[i].recoilX = rand() % 9 - 4;
											break;
										}
									}
								}
								if (boss.attackTimer <= 450 && boss.attackTimer >= 350) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].shotType == 2 || bossBullet[i].shotType == 15) {
											bossBullet[i].shotType = 2;
											if (boss.attackTimer % 20 == 1 || boss.attackTimer % 20 == 2 || boss.attackTimer % 20 == 3) {
												bossBullet[i].shotType = 15;
											}
										}
									}
								}

								if (boss.attackTimer == 350) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].shotType == 2 || bossBullet[i].shotType == 8) {
											bossBullet[i].shotType = 0;
										}
									}
								}
							}

							//���~�ߒ�---------------------(300~100)-----------------------
							if (boss.attackTimer <= 300 && boss.attackTimer >= 100) {
								//�{�X�̓������~�߂�
								boss.speedX = 0.0f;
								boss.speedY = 0.0f;
								//�\�����̕\��
								if (boss.attackTimer <= 350 && boss.attackTimer >= 330) {
									line[0].x = playerX;
									line[0].y = playerY;
									line[0].isLine = true;
								}
								if (boss.attackTimer <= 300 && boss.attackTimer >= 280) {
									line[1].x = playerX;
									line[1].y = playerY;
									line[1].isLine = true;
								}
								if (boss.attackTimer <= 260 && boss.attackTimer >= 250) {
									line[2].x = playerX;
									line[2].y = playerY;
									line[2].isLine = true;
								}
								if (boss.attackTimer <= 230 && boss.attackTimer >= 220) {
									line[3].x = playerX;
									line[3].y = playerY;
									line[3].isLine = true;
								}
								if (boss.attackTimer <= 210 && boss.attackTimer >= 200) {
									line[4].x = playerX;
									line[4].y = playerY;
									line[4].isLine = true;
								}
								if (boss.attackTimer <= 190 && boss.attackTimer >= 180) {
									line[5].x = playerX;
									line[5].y = playerY;
									line[5].isLine = true;
								}
								//�\�����ɉ������e�𔭎�
								if (boss.attackTimer <= 330 && boss.attackTimer >= 310) {
									for (int i = 400; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 3;
											bossBullet[i].recoilX = (line[0].x - bossCenterX) / sqrt(((line[0].x - bossCenterX) * (line[0].x - bossCenterX)) + ((line[0].y - bossCenterY) * (line[0].y - bossCenterY))) * 20;
											bossBullet[i].recoilY = (line[0].y - bossCenterY) / sqrt(((line[0].x - bossCenterX) * (line[0].x - bossCenterX)) + ((line[0].y - bossCenterY) * (line[0].y - bossCenterY))) * 20;
											break;
										}
									}
								}
								if (boss.attackTimer <= 280 && boss.attackTimer >= 260) {
									for (int i = 500; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 3;
											bossBullet[i].recoilX = (line[1].x - bossCenterX) / sqrt(((line[1].x - bossCenterX) * (line[1].x - bossCenterX)) + ((line[1].y - bossCenterY) * (line[1].y - bossCenterY))) * 20;
											bossBullet[i].recoilY = (line[1].y - bossCenterY) / sqrt(((line[1].x - bossCenterX) * (line[1].x - bossCenterX)) + ((line[1].y - bossCenterY) * (line[1].y - bossCenterY))) * 20;
											break;
										}
									}
								}
								if (boss.attackTimer <= 250 && boss.attackTimer >= 230) {
									for (int i = 600; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 3;
											bossBullet[i].recoilX = (line[2].x - bossCenterX) / sqrt(((line[2].x - bossCenterX) * (line[2].x - bossCenterX)) + ((line[2].y - bossCenterY) * (line[2].y - bossCenterY))) * 20;
											bossBullet[i].recoilY = (line[2].y - bossCenterY) / sqrt(((line[2].x - bossCenterX) * (line[2].x - bossCenterX)) + ((line[2].y - bossCenterY) * (line[2].y - bossCenterY))) * 20;
											break;
										}
									}
								}
								if (boss.attackTimer <= 220 && boss.attackTimer >= 200) {
									for (int i = 700; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 3;
											bossBullet[i].recoilX = (line[3].x - bossCenterX) / sqrt(((line[3].x - bossCenterX) * (line[3].x - bossCenterX)) + ((line[3].y - bossCenterY) * (line[3].y - bossCenterY))) * 20;
											bossBullet[i].recoilY = (line[3].y - bossCenterY) / sqrt(((line[3].x - bossCenterX) * (line[3].x - bossCenterX)) + ((line[3].y - bossCenterY) * (line[3].y - bossCenterY))) * 20;
											break;
										}
									}
								}
								if (boss.attackTimer <= 200 && boss.attackTimer >= 180) {
									for (int i = 800; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 3;
											bossBullet[i].recoilX = (line[4].x - bossCenterX) / sqrt(((line[4].x - bossCenterX) * (line[4].x - bossCenterX)) + ((line[4].y - bossCenterY) * (line[4].y - bossCenterY))) * 20;
											bossBullet[i].recoilY = (line[4].y - bossCenterY) / sqrt(((line[4].x - bossCenterX) * (line[4].x - bossCenterX)) + ((line[4].y - bossCenterY) * (line[4].y - bossCenterY))) * 20;
											break;
										}
									}
								}
								if (boss.attackTimer <= 180 && boss.attackTimer >= 160) {
									for (int i = 900; i < BOSS_BULLET_CONST; i++) {
										if (bossBullet[i].isShot == 0) {
											bossBullet[i].isShot = 1;
											bossBullet[i].shotType = 3;
											bossBullet[i].recoilX = (line[5].x - bossCenterX) / sqrt(((line[5].x - bossCenterX) * (line[5].x - bossCenterX)) + ((line[5].y - bossCenterY) * (line[5].y - bossCenterY))) * 20;
											bossBullet[i].recoilY = (line[5].y - bossCenterY) / sqrt(((line[5].x - bossCenterX) * (line[5].x - bossCenterX)) + ((line[5].y - bossCenterY) * (line[5].y - bossCenterY))) * 20;
											break;
										}
									}
								}

								//�\�����̍폜
								if (boss.attackTimer == 290) {
									line[0] = { 0,0,false };
								}
								if (boss.attackTimer == 240) {
									line[1] = { 0,0,false };
								}
								if (boss.attackTimer == 210) {
									line[2] = { 0,0,false };
								}
								if (boss.attackTimer == 180) {
									line[3] = { 0,0,false };
								}
								if (boss.attackTimer == 160) {
									line[4] = { 0,0,false };
								}
								if (boss.attackTimer == 140) {
									line[5] = { 0,0,false };
								}
							}

							//���~�߉���---------------------(100~0)-----------------------

							//�e�g�U�\��
							if (boss.attackTimer <= 100 && boss.attackTimer >= 0) {
								if (isBarrierOpen == 0) {
									isBarrierOpen = 1;
								}

								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].shotType == 0 || bossBullet[i].shotType == 9) {
										bossBullet[i].shotType = 0;
										if (boss.attackTimer % 20 == 1 || boss.attackTimer % 20 == 2 || boss.attackTimer % 20 == 3) {
											bossBullet[i].shotType = 20;
										}
									}
								}

								//�g�U
								if (boss.attackTimer == 0) {
									for (int i = 0; i < BOSS_BULLET_CONST; i++) {
										bossBullet[i].recoilX = rand() % 7 - 3;
										bossBullet[i].recoilY = rand() % 7 - 3;
										if (bossBullet[i].recoilX >= 0 && bossBullet[i].recoilX <= 1) {
											bossBullet[i].recoilX += 1;
										}
										if (bossBullet[i].recoilY >= 0 && bossBullet[i].recoilY <= 1) {
											bossBullet[i].recoilY += 1;
										}
										bossBullet[i].shotType = 6;
									}
								}
							}

							//�Ō�̃r�[��---------------------(0~-500)-----------------------
							if (boss.attackTimer <= 0 && boss.attackTimer >= -500) {
								if (boss.attackTimer == 0) {
									beam[1].state = 1;
									beam[1].timer = BEAM_TIME1_2;
									bossMoveCount = 3;
								}
							}

							//attackTimer��-500�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= -600) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								sceneCount++;
							}
							break;

						case 9:
							//�^�C�}�[�̒Z�k
							if (boss.attackTimer >= 200) {
								boss.attackTimer = 200;
							}

							//�e�g�U�\��
							if (boss.attackTimer <= 200 && boss.attackTimer >= 100) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].shotType == 0 || bossBullet[i].shotType == 20) {
										bossBullet[i].shotType = 0;
										if (boss.attackTimer % 20 == 1 || boss.attackTimer % 20 == 2 || boss.attackTimer % 20 == 3) {
											bossBullet[i].shotType = 20;
										}
									}
								}
							}

							//�g�U
							if (boss.attackTimer == 80) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									bossBullet[i].recoilX = rand() % 7 - 3;
									bossBullet[i].recoilY = rand() % 7 - 3;
									if (bossBullet[i].recoilX >= 0 && bossBullet[i].recoilX <= 1) {
										bossBullet[i].recoilX += 1;
									}
									if (bossBullet[i].recoilY >= 0 && bossBullet[i].recoilY <= 1) {
										bossBullet[i].recoilY += 1;
									}
									bossBullet[i].shotType = 6;
								}
							}

							//attackTimer��0�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= 0) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								circleNumber = 0;
								sceneCount++;
								//����p
								trap = false;
							}
							break;
							//�x���z�[�~���O
						case 11:
							if (boss.attackTimer % 20 == 0) {
								for (int i = 0; i < BOSS_BULLET_CONST; i++) {
									if (bossBullet[i].isShot == 0) {
										bossBullet[i].isShot = 1;
										bossBullet[i].shotType = 11;
										bossBullet[i].timer = 0;
										break;
									}
								}
							}

							//attackTimer��0�ɂȂ������A�ҋ@��Ԃɖ߂�
							if (boss.attackTimer <= 0) {
								boss.attackType = 0;
								boss.attackTimer = timer0;
								circleNumber = 0;
								sceneCount++;
								//����p
								trap = false;
							}
							break;
							//���@�z�[�~���O
						//case 12:
						//	if (boss.attackTimer == 50) {
						//		for (int i = 0; i < BOSS_BULLET_CONST; i++) {
						//			if (bossBullet[i].isShot == 0) {
						//				bossBullet[i].isShot = 1;
						//				bossBullet[i].shotType = 13;
						//				bossBullet[i].timer = 0;
						//				break;
						//			}
						//		}
						//	}
						//	//attackTimer��0�ɂȂ������A�ҋ@��Ԃɖ߂�
						//	if (boss.attackTimer <= 0) {
						//		boss.attackType = 0;
						//		boss.attackTimer = timer0;
						//		circleNumber = 0;
						//		sceneCount++;
						//		//����p
						//		trap = false;
						//	}
						//	break;
					}

					//�v���C���[�ƒe�̓����蔻��
					if (boss.isAlive == 0) {
						for (int i = 0; i < BOSS_BULLET_CONST; i++) {
							if (BOSS_BULLET_COLLISION(playerX, playerY, PLAYER_R, bossBullet[i]) == 1) {
								isDead = 1;
							}
						}
						if (beam[0].state == 2) {
							if (BEAM1_COLLISION(playerX, playerY, PLAYER_R) == true) {
								isDead = 1;
								isShake = 0;

							}
						}
						if (beam[1].state == 2) {
							if (BEAM2_COLLISION(playerX, playerY, PLAYER_R) == true) {
								isDead = 1;
								isShake = 0;
							}
						}
						if (beam[2].state == 2) {
							if (BEAM3_COLLISION(playerX, playerY, PLAYER_R) == true) {
								isDead = 1;
								isShake = 0;
							}
						}
						if (beam[3].state == 2) {
							if (BEAM4_COLLISION(playerX, playerY, PLAYER_R) == true) {
								isDead = 1;
								isShake = 0;
							}
						}
						if (beam[4].state == 2) {
							if (BEAM5_COLLISION(playerX, playerY, PLAYER_R) == true) {
								isDead = 1;
								isShake = 0;
							}
						}
						if (beam[5].state == 2) {
							if (BEAM6_COLLISION(playerX, playerY, PLAYER_R) == true) {
								isDead = 1;
								isShake = 0;
							}
						}
					}
				}

				//�r�[���^�C�}�[�̊Ǘ�
				for (int i = 0; i < BEAM_CONST; i++) {
					if (beam[i].timer > 0) {
						beam[i].timer--;
					}
					if (beam[i].timer == 0) {
						if (beam[i].state == 1) {
							beam[i].state = 2;
							beam[i].timer = BEAM_TIME2_0;
							if (boss.attackTimer <= 0) {
								beam[1].timer = 250;
							}

							if (isShake == 0) {
								isShake = 1;
							}

							//�{�X����
							if (bossMoveCount == 3) {
								bossMoveTime = 8;
							}
							else if (bossMoveCount == 2) {
								bossMoveTime = 5;
							}
							else {
								bossMoveTime = 4;
							}
						}
						else if (beam[i].state == 2) {
							beam[i].state = 0;
							beam[i].timer = 0;
							if (isShake == 1) {
								isShake = 0;
							}
						}
					}
				}

				for (int i = 0; i < BOSS_BULLET_CONST; i++) {
					if (bossBullet[i].shotType == 11 || bossBullet[i].shotType == 13) {
						bossBullet[i].timer++;
					}
					if (bossBullet[i].timer == 100 && bossBullet[i].shotType == 11) {
						bossBullet[i].shotType = 12;
						bossBullet[i].recoilX = (playerX - bossBullet[i].x) / sqrt(((playerX - bossBullet[i].x) * (playerX - bossBullet[i].x)) + ((playerY - bossBullet[i].y) * (playerY - bossBullet[i].y))) * 8;
						bossBullet[i].recoilY = (playerY - bossBullet[i].y) / sqrt(((playerX - bossBullet[i].x) * (playerX - bossBullet[i].x)) + ((playerY - bossBullet[i].y) * (playerY - bossBullet[i].y))) * 8;
					}
				}

				//50F�O�̎��@���W�̎擾
				for (int i = OLD_PLAYER_MAX - 2; i > -1; i--) {
					oldPlayerX[i + 1] = oldPlayerX[i];
					oldPlayerY[i + 1] = oldPlayerY[i];
				}
				oldPlayerX[0] = playerX;
				oldPlayerY[0] = playerY;

				//�z�[�~���O
				//for (int i = 0; i < BOSS_BULLET_CONST; i++) {
				//	if (bossBullet[i].shotType == 13 && bossBullet[i].timer <= 1000) {
				//		bossBullet[i].recoilX = (oldPlayerX[49] - bossBullet[i].x) / sqrt(((oldPlayerX[49] - bossBullet[i].x) * (oldPlayerX[49] - bossBullet[i].x)) + ((oldPlayerY[49] - bossBullet[i].y) * (oldPlayerY[49] - bossBullet[i].y))) * 3;
				//		bossBullet[i].recoilY = (oldPlayerY[49] - bossBullet[i].y) / sqrt(((oldPlayerX[49] - bossBullet[i].x) * (oldPlayerX[49] - bossBullet[i].x)) + ((oldPlayerY[49] - bossBullet[i].y) * (oldPlayerY[49] - bossBullet[i].y))) * 3;
				//	}
				//}

				//�z�[�~���O����
				//for (int i = 0; i < BOSS_BULLET_CONST; i++) {
				//	if (HOMING_COLLISION(playerX, playerY, PLAYER_R, bossBullet[i]) == 1) {
				//		bossBullet[i].shotType = 14;
				//	}
				//}

				break;

			case 2:

				//�e���ˌ�̉��o
				if (isShot == 1) {
					sceneTime++;
					bulletTmpY -= bulletSpeed;

					if (sceneTime == 50) {
						playerAngle = 0.0f;
						sceneTime = 0;
						scene = 1;
					}
				}

				break;

				//�G���j���s
			case 3:
				if (isFaled == 0) {
					isFaled = 1;
				}
				//���s�V�[��
				if (isFaled == 1 || isDead == 1) {

					sceneTime++;
					//��ʂ��Â�
					alpha += 3;

					if (sceneTime == 100) {
						scene = 5;
						sceneTime = 0;

					}
				}
				break;

				//�N���A���o
			case 4:
				if (boss.isAlive == 1) {
					//���o
					bulletTmpY -= bulletSpeedTmp;
					bulletLineColor -= 4;
					sceneTime++;

					bulletSpeedTmp += 2.5f;

					//���Ԃ���������ϐ������Z�b�g���A�V�[���`�F���W
					if (sceneTime == 50) {
						sceneTime = 0;
						bulletLineColor = 255;
						bossLength = 128.0f;

						bossCenterX = bossCenterTmpX;
						bossCenterY = bossCenterTmpY;

						for (int i = 0; i < 4; i++) {
							bossAddX[i] = cos(bossRadius[i]) * bossLength;
							bossAddY[i] = sin(bossRadius[i]) * bossLength;

							bossPartX[i] = (bossCenterX + bossAddX[i]);
							bossPartY[i] = (bossCenterY + bossAddY[i]);
						}

						scene = 1;
					}
				}
				break;

				//���U���g
			case 5:
				if (isShake == 1) {
					isShake = 0;
				}

				if (boss.isAlive == 0) {
					//Retry?
					if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1 || InputX < 0) {
						isRetry = 1;
					}
					if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1 || InputX > 0) {
						isRetry = 0;
					}
				}
				else {
					isRetry = 0;
				}


				//��ʐ؂�ւ�
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || pad & PAD_INPUT_2) {
					//���g���C
					if (isRetry == 1) {
						isReset = 1;
						scene = 6;
						deadCount++;
						countAlpha = 255;
						if (sceneCount <= 5 && eyeState == 2) {
							eyeState = 1;
							partState = 1;
							barrierState = 1;
						}
					}
					//�^�C�g��
					else {
						scene = 7;
						isReset = 1;
						playerX = 360.0f;
						playerY = 1000.0f;
						deadCount = 0;
						sceneCount = 0;
						countAlpha = 255;
					}
				}
				break;

				//���S�񐔃J�E���g
			case 6:
				sceneTime++;

				if (sceneTime >= 40) {
					countAlpha -= 8;
				}

				if (sceneTime == 70) {
					sceneTime = 0;
					scene = 1;
				}

				break;

			case 7:
				sceneTime++;

				if (sceneTime >= 70) {
					countAlpha -= 8;
				}

				if (sceneTime == 115) {
					sceneTime = 0;
					scene = 0;
				}
				break;
		}

		//�S�����Z�b�g
		if (isReset == 1) {
			isRetry = 1;
			isShot = 0;
			isFaled = 0;
			playerTmpX = 350.0f;
			playerTmpY = 650.0f;
			bulletY = 1000.0f;
			bulletSpeed = 4.5f;
			sceneTime = 0;
			alpha = 0;
			bulletLineX = 0.0f;
			bulletLineY = 0.0f;
			bulletLineColor = 255;
			bossCenterX = 350.0f;
			bossCenterY = 200.0f;
			bossAngleSpeed = 20.0f;
			bossLength = 0.0f;
			isBarrierOpen = 0;
			openTime = 60;
			bossBarrierR = 32.0f;
			beamRand = 0;
			circleNumber = 0;
			trap = false;
			isPlay = 0;
			isStart = 0;
			trapEx = -1;
			bossMoveTime = 0;
			bossMoveCount = 0;
			oldSceneType = 0;
			oldBeam = -1;
			oldBeam2_1 = -1;
			oldBeam2_2 = -1;
			playerAngle = 0.0f;
			playerBombCount = 0;
			isDead = 0;
			lineAlpha = 0;
			isLimit = 0;
			randX = 0;
			isShake = 0;
			barrierNum = 1.5f;

			//���g���C���Ƀ{�X����u�`�J�b�Ƃ���̂�j�~
			for (int i = 0; i < 4; i++) {
				bossAddX[i] = cos(bossRadius[i]) * bossLength;
				bossAddY[i] = sin(bossRadius[i]) * bossLength;

				bossPartX[i] = (bossCenterX + bossAddX[i]);
				bossPartY[i] = (bossCenterY + bossAddY[i]);
			}

			boss = {
				300.0f,		//X���W
				200.0f,		//Y���W
				150,		//���a
				0.0f,		//�{�X�̒��̉摜�̉�]
				2.0f,		//X����
				0.5f,		//Y����
				0,			//���E�ړ�(0�Ȃ�E�A1�Ȃ獶)
				0,			//�㉺�ړ�(0�Ȃ��A1�Ȃ牺)
				0,			//�U�����(0�Ȃ�ҋ@�A����ȊO�Ȃ�Ή������s��)
				250,		//�U���̃^�C�}�[�Ǘ�
				false		//���݂��Ă��邩(true�Ȃ瑶�݂���Afalse�Ȃ瑶�݂��Ȃ�)
			};

			for (int i = 0; i < BOSS_BULLET_CONST; i++) {
				bossBullet[i] = {
					bossCenterX,		//X���W
					bossCenterY,		//Y���W
					16,			//���a
					false,		//���݂��Ă��邩(true�Ȃ瑶�݂���Afalse�Ȃ瑶�݂��Ȃ�)
					0,			//�e�̋����̎��
					0,			//�e�̗�����ۑ�
					0
				};
			}

			for (int i = 0; i < OLD_PLAYER_MAX; i++) {
				oldPlayerX[i] = 0;
				oldPlayerY[i] = 0;
			}

			for (int i = 0; i < LINE_CONST; i++) {
				line[i] = {
					0,		//x���W
					0,		//y���W
					false	//���݂��Ă��邩
				};
			}

			for (int i = 0; i < CIRCLE_CONST; i++) {
				circle[i] = {
					0,		//x���W
					0,		//y���W
					false	//���݂��Ă��邩
				};
			}

			for (int i = 0; i < BEAM_CONST; i++) {
				beam[i] = {
					0,		//�r�[���̏��(0�Ȃ疳�A1�Ȃ�\���A2�Ȃ甭��)
					0		//�^�C�}�[
				};
			}

			//�{�X�o���A
			for (int i = 0; i < 2; i++) {
				bossBarrierX[0] = bossCenterX - 32;
				bossBarrierX[1] = bossCenterX + 32;
				bossBarrierY[i] = bossCenterY + 40;
			}

			//�������o
			for (int i = 0; i < 10; i++) {
				bossBombTime[i] = 0;
				bossBombCount[i] = 0;
				isBossBomb[i] = 0;
			}
			for (int i = 0; i < 2; i++) {
				isBossBye[i] = 0;
			}

			//���Z�b�g�t���O��߂�
			isReset = 0;
		}


		// �`�揈��

		//�^�C�g��
		//�w�i
		if (isShake == 1) {
			randX = rand() % 31 - 15;
		}
		else {
			randX = 0;
		}

		DrawGraph(0 + randX, backY + randX, backGraph, true);
		DrawGraph(0 + randX, (backY - 960) + randX, backGraph, true);


		if (scene == 0) {
			DrawGraph(0, 0, titleGraph, true);
			if (isPlay == 0) {
				DrawGraph(0, 0, spaceGraph, true);
			}

			if (isPlay == 1) {
				DrawRotaGraph2(playerX, playerY, PLAYER_R, 32, 1.0f, playerAngle, playerGraph[isDead], true);
			}

			DrawRotaGraph2(360, 200, bossCenterR, bossCenterR, 2, 0, eyeGraph[0], true);
		}

		if (scene == 1) {

			if (isStart == 0) {
				DrawGraph(-50, 0, startGraph, true);
				DrawRotaGraph2(180, 520, BULLET_R, BULLET_R, 4.0f, 0.0f, playerBulletGraph, true);
			}


			//�Ԃ����C��
			if (isLimit == 1) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, lineAlpha);	//��������
				DrawBox(0, 400, 720, 420, GetColor(128, 0, 0), true);
				DrawBox(0, 415, 720, 420, GetColor(128, 0, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�����܂ŗL��
			}

			if (boss.isAlive == 0) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, 212);
				//�\����
				if (boss.attackType == 3 || boss.attackType == 4) {
					for (int i = 0; i < LINE_CONST; i++) {
						if (line[i].isLine == true) {
							DrawLine(bossCenterX, bossCenterY, bossCenterX + (line[i].x - bossCenterX), bossCenterY + (line[i].y - bossCenterY), GetColor(255, 0, 0), true);
						}
					}
				}

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
				//�\����
				if (boss.attackType == 6) {
					for (int i = 0; i < LINE_CONST; i++) {
						if (line[i].isLine == true) {
							DrawLine(bossCenterX, bossCenterY, bossCenterX + (line[i].x - bossCenterX), bossCenterY + (line[i].y - bossCenterY), GetColor(255, 0, 0), true);
						}
					}
				}
				else {
					for (int i = 0; i < LINE_CONST; i++) {
						if (line[i].isLine == true) {
							DrawLine(bossCenterX, bossCenterY, bossCenterX + ((line[i].x - bossCenterX) * 5), bossCenterY + ((line[i].y - bossCenterY) * 5), GetColor(128, 0, 0), 18);
							DrawLine(bossCenterX, bossCenterY, bossCenterX + ((line[i].x - bossCenterX) * 5), bossCenterY + ((line[i].y - bossCenterY) * 5), GetColor(196, 0, 0), 6);
						}
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				//�\���~
				for (int i = 0; i < CIRCLE_CONST; i++) {
					if (circle[i].isCircle == true) {
						SetDrawBlendMode(DX_BLENDMODE_ADD, 212);
						DrawCircle(circle[i].x, circle[i].y, bossBullet[0].r, GetColor(48, 0, 0), true);
						DrawCircle(circle[i].x, circle[i].y, 4, GetColor(171, 0, 0), true);
						DrawCircle(circle[i].x, circle[i].y, bossBullet[0].r, GetColor(255, 0, 0), false);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}
				}
				//�r�[���̗\��
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				if (beam[0].state == 1) {
					DrawLine(120, 420, 120, 960, GetColor(196, 0, 0), 240);
					DrawFormatString(120, 690, GetColor(255, 255, 255), "!");
					DrawBox(0, 420, 240, 960, GetColor(255, 0, 0), false);
				}
				if (beam[1].state == 1) {
					DrawLine(360, 420, 360, 960, GetColor(196, 0, 0), 240);
					DrawFormatString(360, 690, GetColor(255, 255, 255), "!");
					DrawBox(240, 420, 480, 960, GetColor(255, 0, 0), false);
				}
				if (beam[2].state == 1) {
					DrawLine(600, 420, 600, 960, GetColor(196, 0, 0), 240);
					DrawFormatString(600, 690, GetColor(255, 255, 255), "!");
					DrawBox(480, 420, 720, 960, GetColor(255, 0, 0), false);
				}
				if (beam[3].state == 1) {
					DrawLine(0, 510, 720, 510, GetColor(196, 0, 0), 180);
					DrawFormatString(360, 510, GetColor(255, 255, 255), "!");
					DrawBox(16, 420, 704, 600, GetColor(255, 0, 0), false);
				}
				if (beam[4].state == 1) {
					DrawLine(0, 690, 720, 690, GetColor(196, 0, 0), 180);
					DrawFormatString(360, 690, GetColor(255, 255, 255), "!");
					DrawBox(16, 600, 704, 780, GetColor(255, 0, 0), false);
				}
				if (beam[5].state == 1) {
					DrawLine(0, 870, 720, 870, GetColor(196, 0, 0), 180);
					DrawFormatString(360, 870, GetColor(255, 255, 255), "!");
					DrawBox(16, 780, 704, 960, GetColor(255, 0, 0), false);
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}

			SetDrawBlendMode(DX_BLENDMODE_ADD, 196);
			//�r�[���̊G
			if (beam[0].state == 2) {
				DrawBox(0, 420, 240, 960, GetColor(128, 0, 0), true);
				DrawBox(20, 420, 220, 960, GetColor(128, 0, 128), true);
				DrawBox(60, 420, 180, 960, GetColor(0, 255, 128), true);
			}
			if (beam[1].state == 2) {
				DrawBox(240, 420, 480, 960, GetColor(128, 0, 0), true);
				DrawBox(260, 420, 460, 960, GetColor(128, 0, 128), true);
				DrawBox(300, 420, 420, 960, GetColor(0, 255, 128), true);
			}
			if (beam[2].state == 2) {
				DrawBox(480, 420, 720, 960, GetColor(128, 0, 0), true);
				DrawBox(500, 420, 700, 960, GetColor(128, 0, 128), true);
				DrawBox(540, 420, 660, 960, GetColor(0, 255, 128), true);
			}
			if (beam[3].state == 2) {
				DrawBox(0, 420, 720, 600, GetColor(128, 0, 0), true);
				DrawBox(0, 440, 720, 580, GetColor(128, 0, 128), true);
				DrawBox(0, 460, 720, 560, GetColor(0, 255, 128), true);
			}
			if (beam[4].state == 2) {
				DrawBox(0, 600, 720, 780, GetColor(128, 0, 0), true);
				DrawBox(0, 620, 720, 760, GetColor(128, 0, 128), true);
				DrawBox(0, 640, 720, 740, GetColor(0, 255, 128), true);
			}
			if (beam[5].state == 2) {
				DrawBox(0, 780, 720, 960, GetColor(128, 0, 0), true);
				DrawBox(0, 800, 720, 940, GetColor(128, 0, 128), true);
				DrawBox(0, 820, 720, 920, GetColor(0, 255, 128), true);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			//�{�X

			for (int i = 0; i < 2; i++) {
				if (i == 0) {
					//DrawBox(bossBarrierX[i], bossBarrierY[i], bossBarrierX[i] + bossBarrierR, bossBarrierY[i] + 16, GetColor(0, 0, 196), true);
					DrawRotaGraph3(bossBarrierX[i] - 4, bossBarrierY[i], 8, 4, barrierNum, 1.5, 0, barrierGraph[barrierState], true);
				}
				else {
					//DrawBox(bossBarrierX[i], bossBarrierY[i], bossBarrierX[i] - bossBarrierR, bossBarrierY[i] + 16, GetColor(0, 0, 196), true);
					DrawRotaGraph3(bossBarrierX[i] + 4, bossBarrierY[i] + 12, 8, 4, barrierNum, 1.5, 3.141519, barrierGraph[barrierState], true);
				}
			}

			if (isBossBye[1] == 0) {
				DrawGraph((bossCenterX - bossCenterR - 2), (bossCenterY - bossCenterR - 4), eyeGraph[eyeState], true);
			}

			if (isBossBye[0] == 0) {
				for (int i = 0; i < 4; i++) {
					DrawGraph(bossPartX[i] - 32, bossPartY[i] - 32, bossPartGraph[partState], true);
				}
			}


			//����
			for (int i = 0; i < 10; i++) {
				if (boss.isAlive == 1) {
					if (isBossBomb[0] == 1) {
						DrawRotaGraph2(bossCenterX + 64, bossCenterY + 64, 32, 32, 1.0f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[1] == 1) {
						DrawRotaGraph2(bossCenterX + 32, bossCenterY - 64, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[2] == 1) {
						DrawRotaGraph2(bossCenterX - 64, bossCenterY - 64, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[3] == 1) {
						DrawRotaGraph2(bossCenterX - 64, bossCenterY + 32, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[4] == 1) {
						DrawRotaGraph2(bossCenterX + 32, bossCenterY + 64, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[5] == 1) {
						DrawRotaGraph2(bossCenterX + 64, bossCenterY + 32, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[6] == 1) {
						DrawRotaGraph2(bossCenterX - 64, bossCenterY + 64, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[7] == 1) {
						DrawRotaGraph2(bossCenterX + 64, bossCenterY - 32, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[8] == 1) {
						DrawRotaGraph2(bossCenterX, bossCenterY - 64, 32, 32, 1.5f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
					if (isBossBomb[9] == 1) {
						DrawRotaGraph2(bossCenterX, bossCenterY, 32, 32, 5.0f, 0.0f, bombGraph[bossBombCount[i]], true);
					}
				}
			}

			//���@
			DrawRotaGraph2(playerX, playerY, PLAYER_R, 32, 1.0f, playerAngle, playerGraph[isDead], true);

			SetDrawBlendMode(DX_BLENDMODE_ADD, 212);
			DrawCircle(playerX, playerY, 16, GetColor(64, 196, 0), true);
			DrawCircle(playerX, playerY, 8, GetColor(191, 59, 255), true);
			DrawCircle(playerX, playerY, 8, GetColor(255, 255, 255), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			//�{�X�̒e
			SetDrawBlendMode(DX_BLENDMODE_ADD, 212);
			if (boss.isAlive == 0) {
				for (int i = 0; i < BOSS_BULLET_CONST; i++) {
					if (bossBullet[i].isShot == true) {
						if (bossBullet[i].shotType == 0 || bossBullet[i].shotType == 8 || bossBullet[i].shotType == 15) {
							DrawCircle(bossBullet[i].x, bossBullet[i].y, bossBullet[i].r, GetColor(96, 0, 255), true);
							DrawCircle(bossBullet[i].x, bossBullet[i].y, 8, GetColor(0, 96, 0), true);
						}
						else {
							DrawCircle(bossBullet[i].x, bossBullet[i].y, bossBullet[i].r, GetColor(196, 0, 0), true);
							DrawCircle(bossBullet[i].x, bossBullet[i].y, 12, GetColor(59, 0, 255), true);
							DrawCircle(bossBullet[i].x, bossBullet[i].y, 8, GetColor(0, 220, 0), true);
						}
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			}

			//�e
			if (isShot == 1) {
				DrawRotaGraph2(bulletX, bulletY, BULLET_R, BULLET_R, 1.5f, 0.0f, playerBulletGraph, true);

				//�摜�Ƃ��𓧉߂�����(0�������A255�����߂��Ȃ�)�� ���̏ꍇ����bulletLineColor�̐��l
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, bulletLineColor);	//��������
				DrawBox((bulletX - 8), bulletY, (bulletLineX + 8), bulletLineY, GetColor(128, 128, 96), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�����܂ŗL��
			}

			if (isDead == 1 && playerBombCount < 5) {
				DrawRotaGraph2(playerX, playerY, 32, 32, 1.5f, 0.0f, bombGraph[playerBombCount], true);
			}
		}


		//�e���˂̉��o
		if (scene == 2) {
			//�w�i(�Y�[��)
			DrawRotaGraph2(0, 0, 360, 480, 8.0f, 0.0f, backGraph, true);

			//�e
			if (isShot == 1) {
				DrawRotaGraph2(bulletTmpX, bulletTmpY, BULLET_R, BULLET_R, 12.0f, 0.0f, playerBulletGraph, true);
			}

			//���@
			DrawRotaGraph2(playerTmpX, playerTmpY + 32, PLAYER_R, 32, 12, 0, playerGraph[0], true);
		}

		//���j���s
		if (scene == 3) {
			//�w�i(�Y�[��)
			DrawRotaGraph2(0, 0, 360, 480, 8.0f, 0.0f, backGraph, true);

			//���@
			if (isDead == 1) {
				DrawRotaGraph2(playerTmpX, playerTmpY, PLAYER_R, 32, 10, 0, playerGraph[1], true);
			}
			else if (isFaled == 1) {
				DrawRotaGraph2(playerTmpX, playerTmpY, PLAYER_R, 32, 10, 0, playerGraph[0], true);
			}

			//�摜�Ƃ��𓧉߂�����(0�������A255�����߂��Ȃ�)�� ���̏ꍇ����alpha�̐��l
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);	//��������
			DrawBox(0, 0, 720, 960, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�����܂ŗL��
		}

		//�������o
		if (scene == 4) {
			//�w�i(�Y�[��)
			DrawRotaGraph2(0, 0, 360, 480, 4.0f, 0.0f, backGraph, true);

			//�e
			DrawRotaGraph2(bulletTmpX, bulletTmpY, BULLET_R, BULLET_R, 3.0f, 0.0f, playerBulletGraph, true);
			//�摜�Ƃ��𓧉߂�����(0�������A255�����߂��Ȃ�)�� ���̏ꍇ����bulletLineColor�̐��l
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, bulletLineColor);	//��������
			DrawBox((bulletTmpX - 16), bulletTmpY, (bulletLineX + 16), bulletLineY, GetColor(128, 128, 96), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�����܂ŗL��


			//�{�X(�Y�[��)
			DrawRotaGraph2(bossPartXTmp[0], bossPartYTmp[0], 32, 32, 3, 0, bossPartGraph[partState], true);
			DrawRotaGraph2(bossPartXTmp[1], bossPartYTmp[1], 32, 32, 3, 0, bossPartGraph[partState], true);
			DrawRotaGraph2(bossPartXTmp[2], bossPartYTmp[2], 32, 32, 3, 0, bossPartGraph[partState], true);
			DrawRotaGraph2(bossPartXTmp[3], bossPartYTmp[3], 32, 32, 3, 0, bossPartGraph[partState], true);

			DrawRotaGraph2(bossCenterXTmp, bossCenterYTmp, 24, 24, 2, 0, eyeGraph[eyeState], true);
		}

		//���U���g
		if (scene == 5) {
			//�Q�[���N���A
			if (boss.isAlive == 1) {
				//DrawFormatString(320, 480, GetColor(255, 255, 255), "GameClear!!");
				DrawGraph(0, 0, resultGraph[0], true);
				DrawGraph(232, 650, overGraph[1], true);
				DrawRotaGraph2(448, 704, BULLET_R, BULLET_R, 2.0f, 0.0f, playerBulletGraph, true);
			}
			//�Q�[���I�[�o�[        //���S
			else if (isDead == 1) {
				DrawGraph(0, 0, resultGraph[1], true);
			}
			//���s
			else if (isFaled == 1) {
				DrawGraph(0, 0, resultGraph[2], true);
			}


			if (boss.isAlive == 0) {
				if (isRetry == 1) {
					DrawGraph(68, 650, retryGraph[0], true);
					DrawRotaGraph2(530, 710, 128, 64, 0.9f, 0, overGraph[0], true);
					DrawRotaGraph2(324, 704, BULLET_R, BULLET_R, 2.0f, 0.0f, playerBulletGraph, true);
				}
				else {
					DrawRotaGraph2(128, 685, 64, 32, 0.9f, 0, retryGraph[1], true);
					DrawGraph(418, 650, overGraph[1], true);
					//DrawTriangle(608, 658, 624, 642, 624, 674, GetColor(255, 255, 255), true);
					DrawRotaGraph2(634, 704, BULLET_R, BULLET_R, 2.0f, 0.0f, playerBulletGraph, true);
				}
			}

		}

		if (scene == 6) {

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, countAlpha);	//��������

			DrawGraph(0, 0, deadCountGraph, true);

			for (int i = 0; i < 2; i++)
			{
				if (deadCount < 10) {
					DrawGraph(430 + 64 * i, 364, numberGraph[eachNumber[i] - 48], true);
				}
				else if (deadCount >= 10) {
					DrawGraph(394 + 64 * i, 364, numberGraph[eachNumber[i] - 48], true);
				}
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�����܂ŗL��

		}

		if (scene == 7) {

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, countAlpha);	//��������
			DrawGraph(0, 0, thxGraph, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�����܂ŗL��
		}

		//�g
		if (scene == 0 || scene == 1 || scene == 5) {
			DrawGraph(-40 + randX, -50 + randX, flameGraph, true);
		}


		//�f�o�b�N�p�\��
		//�V�[��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "scene:%d", scene);
		DrawFormatString(650, 0, GetColor(255, 255, 255), "debug:%d", isDebug);
		//�{�X�̃X�e�[�^�X
		DrawFormatString(0, 20, GetColor(255, 255, 255), "attackType:%d", boss.attackType);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "attackTimer:%d", boss.attackTimer);

		for (int i = 0; i < BEAM_CONST; i++) {
			DrawFormatString(0, 60 + (20 * i), GetColor(255, 255, 255), "beam[%d]:%d", i, beam[i].state);
		}
		DrawFormatString(0, 240, GetColor(255, 255, 255), "sceneTime:%d", sceneTime);
		DrawFormatString(0, 260, GetColor(255, 255, 255), "bmt:%d", isFaled);
		DrawFormatString(0, 280, GetColor(255, 255, 255), "sceneCount:%d", sceneCount);
		DrawFormatString(0, 300, GetColor(255, 255, 255), "trapExCount:%d", boss.isAlive);

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
