#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game2Scene.h"

#include "ScoreData.h"

//�����L���O�V�[��
//�X�R�A�f�[�^�Ȃǂ͊O���ɂĕۑ����Ă���̂��g�p�B

//�O����`(GameMain.cpp�ɂĐ錾)
extern int Input, EdgeInput;
extern int ScoreData[FILEDATA_NUM];

//�w�i
int Scene2BGImg;

//���u�p�J�E���g
int Scene2Time;

// �V�[���J�n�O�̏��������s��
BOOL initGame2Scene(void) {

	Scene2BGImg = LoadGraph("res/back.PNG", true);

	//�������������p�ɃX�R�A�f�[�^���������������ƂɃ��[�h
	ScoreInit();
	ScoreLoad("res\\SaveData\\scoredata.dat");

	return TRUE;
}

//	�t���[������
void moveGame2Scene() {

	if ((EdgeInput & PAD_INPUT_1)) {
		changeScene(SCENE_MENU);
	}

}

//	�����_�����O����
void renderGame2Scene(void) {

	//DrawString(30, 50, "�Q�[����ʂQ�ł�", GetColor(255, 255, 255));
	//DrawString(30, 100, "�{�^���P�Ń^�C�g���ɖ߂�", GetColor(255, 255, 255));

	DrawGraph(0, 0, Scene2BGImg, true);

	DrawString(0, 0, "Ranking", GetColor(255, 255, 255));

	//�����L���O�f�[�^�̕\������B
	for (int i = 0; i < FILEDATA_NUM; i++) {
		DrawFormatString(100 + i *10, 60 + i * 40, GetColor(255, 255, 255), "%2d : %08d", i + 1, ScoreData[i]);
	}

}

//	�V�[���I�����̌㏈��
void releaseGame2Scene(void) {


}

// ���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  Game2SceneCollideCallback(int nSrc, int nTarget, int nCollideID) {



}
