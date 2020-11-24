#include "GameSceneMain.h"

//�S�ẴV�[���̃w�b�_�t�@�C�����C���N���[�h����
#include "Game1Scene.h"
#include "Game2Scene.h"
#include "Game3Scene.h"
#include "MenuScene.h"


//���̃t�@�C���������Ŏg�p����֐��̃v���g�^�C�v�錾
//���݂̃V�[���̏���������
void initCurrentScene(void);
//���݂̃V�[���̃t���[������
void moveCurrentScene();
//���݂̃V�[���̃����_�����O����
void renderCurrentScene(void);
//���݂̃V�[���̍폜����
void releaseCurrentScene(void);

//���̃t�@�C���������Ŏg�p����ϐ��̐錾�istatic�����Đ錾����j
static SCENE_NO sceneNo = SCENE_NONE;	// ���݂̃V�[���ԍ��i�K�������l��SCENE_NONE�j
static SCENE_NO prevScene = SCENE_NONE;	// 1�O�̃V�[���ԍ��i�K�������l��SCENE_NONE�j
static SCENE_NO nextScene = SCENE_NONE;	// ���̃V�[���ԍ��i�K�������l��SCENE_NONE�j

// ���]�~�̕`��
int DrawReversalCircle(int x, int y, int r, int Color);

int FadeCount;
int FadeInStartFlag;
int FadeInSceneFlag;	//����������1
int FadeOutSceneFlag;

//�R�Q�[���J�n�O�̏��������s��
BOOL InitGame(void){

	FadeCount = 0;
	FadeInSceneFlag = 0;	
	FadeOutSceneFlag = 0;
	FadeInStartFlag = 0;

	//�R(1) ���߂̃V�[���ԍ��̐ݒ�
	changeScene(SCENE_MENU);
	return TRUE;
}

//�t���[������
void FrameMove(){

	//�A�C���X�C�����[�v�J�n
	if(FadeInStartFlag == 1){
		// ���[�v
		FadeCount += 6;
		if (FadeCount > 400) {
			FadeInSceneFlag = 1;
		}
	}else{
		//���s�J�n���̂݁A��ʂ菈����1��̂ݏI��点��
		initCurrentScene();
		renderCurrentScene();

		FadeInStartFlag = 1;
	}

	// ���̃V�[���ɕύX���邩�ǂ������f����
	if (sceneNo != nextScene) {
		FadeOutSceneFlag = 1;
	}

	if (FadeOutSceneFlag == 1) {
		//�V�[����ύX�������ł���΃t�F�[�h�A�E�g�����{����
		// ���[�v
		FadeCount += 6;
		//���o���I���܂Ń��[�v
		if (FadeCount > 400) {
			//���݂̃V�[���̍폜����
			releaseCurrentScene();
			//���݂̃V�[����V�K�V�[���ɕύX����
			sceneNo = nextScene;
			//�V�����V�[���̏���������
			initCurrentScene();

			FadeCount = 0;
			FadeInSceneFlag = 0;
			FadeOutSceneFlag = 0;
		}
	}

	//�t�F�[�h�C���E�A�E�g���͏������s��Ȃ�
	if (FadeInSceneFlag == 1 && FadeOutSceneFlag == 0 ) {
		//���݂̃V�[���̃t���[������
		moveCurrentScene();
	}
}

//�����_�����O����
void RenderScene(){

	//���݂̃V�[���̃����_�����O����
	renderCurrentScene();

	//�A�C���X�A�E�g���s��
	if (FadeInSceneFlag == 0) {
		// �`�悵���O���t�B�b�N�̏�ɔ��]�~��`��
		DrawReversalCircle(320, 240, 1 ? FadeCount : 399 - FadeCount, 0);
	}

	//�A�C���X�C�����s��
	if (FadeOutSceneFlag == 1) {
		// �`�悵���O���t�B�b�N�̏�ɔ��]�~��`��
		DrawReversalCircle(320, 240, 0 ? FadeCount : 399 - FadeCount, 0);
	}

}

//�Q�[���I�����̌㏈��
void GameRelease(void){
	//���݂̃V�[���̍폜����
	releaseCurrentScene();
	//���C�����甲����̂ŁA�I�u�W�F�N�g�̑S�폜���s��
	GameObjectList::instance()->destruct();
}

//�R(2) ���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  CollideCallback(int nSrc, int nTarget, int nCollideID){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	MenuSceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME1:	Game1SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME2:	Game2SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME3:	Game3SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}

//�V�[����ύX����֐�
void changeScene(SCENE_NO no){
	// ���݂̃V�[���Ɠ����Ƃ��͉������Ȃ�
	if (sceneNo == no)return;
	// �������Ȃ��V�[���ԍ��̎��͖�������
	if (no >= SCENE_MAX) return;
	if (no <= SCENE_NONE) return;
	// �V�[����ύX����
	FadeCount = 0;
	prevScene = sceneNo;
	nextScene = no;

}

//�R(3) ���݂̃V�[���̏���������
void initCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	initMenuScene();	break;
	case SCENE_GAME1:	initGame1Scene();	break;
	case SCENE_GAME2:	initGame2Scene();	break;
	case SCENE_GAME3:	initGame3Scene();	break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}
//�R(4) ���݂̃V�[���̃t���[������
void moveCurrentScene(){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	moveMenuScene();		break;
	case SCENE_GAME1:	moveGame1Scene();		break;
	case SCENE_GAME2:	moveGame2Scene();		break;
	case SCENE_GAME3:	moveGame3Scene();		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}
//�R(5) ���݂̃V�[���̃����_�����O����
void renderCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	renderMenuScene();		break;
	case SCENE_GAME1:	renderGame1Scene();		break;
	case SCENE_GAME2:	renderGame2Scene();		break;
	case SCENE_GAME3:	renderGame3Scene();		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}
//�R(6) ���݂̃V�[���̍폜����
void releaseCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	releaseMenuScene();		break;
	case SCENE_GAME1:	releaseGame1Scene();	break;
	case SCENE_GAME2:	releaseGame2Scene();	break;
	case SCENE_GAME3:	releaseGame3Scene();	break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}

// ���]�~�̕`��
int DrawReversalCircle(int x, int y, int r, int Color)
{
	// �~���]�`��̈�̊O����`��
	DrawBox(0, 0, 640, y - r, Color, TRUE);
	DrawBox(0, y - r, x - r, 480, Color, TRUE);
	DrawBox(x - r, y + r + 1, 640, 480, Color, TRUE);
	DrawBox(x + r, y - r, 640, y + r + 1, Color, TRUE);

	// �`�揈��
	{
		int Dx, Dy, F, j;
		int x1, x2, y1;

		// �����l�Z�b�g
		Dx = r; Dy = 0; F = -2 * r + 3;

		j = 0;
		// �`��J�n
		{
			// �܂��ŏ��ɍ��W�f�[�^��i�߂�
			if (F >= 0)
			{
				x2 = Dy + x; x1 = -Dy + x; y1 = Dx + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);
				x2 = Dy + x; x1 = -Dy + x; y1 = -Dx + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);

				Dx--;
				F -= 4 * Dx;
			}

			Dy++;
			F += 4 * Dy + 2;

			// �`���؂�܂Ń��[�v
			while (Dx >= Dy)
			{
				// ���C����`��
				x2 = Dx + x; x1 = -Dx + x; y1 = Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);
				x2 = Dx + x; x1 = -Dx + x; y1 = -Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);

				// ���W�f�[�^��i�߂�
				if (F >= 0)
				{
					x2 = Dy + x; x1 = -Dy + x; y1 = Dx + y;
					DrawLine(0, y1, x1, y1, Color);
					DrawLine(x2, y1, 640, y1, Color);
					x2 = Dy + x; x1 = -Dy + x; y1 = -Dx + y;
					DrawLine(0, y1, x1, y1, Color);
					DrawLine(x2, y1, 640, y1, Color);

					Dx--;
					F -= 4 * Dx;
				}

				Dy++;
				F += 4 * Dy + 2;
			}
		}
	}


	// �I��
	return 0;
}