#include "GameMain.h"
#include "GameSceneMain.h"
#include "MenuScene.h"

#include "EffectStar.h"

//���j���[���ڂ̃V�[���ԍ��̔z��
#define MENU_MAX 3
SCENE_NO menu[MENU_MAX] = { SCENE_GAME1, SCENE_GAME2, SCENE_GAME3 };
char *menuList[3] = { "�Q�[���X�^�[�g","�����L���O","�I��" };
//�I�����ꂽ�Q�[����\�����j���[�ԍ��̏������imenu�̓Y�����j
static int selectedGame = 0;

int startfont;

int MenuImg;

#define MASKCOUNT 120

//�O����`(GameMain.cpp�ɂĐ錾)
extern int Input, EdgeInput;

int StarImg;
int Timer;


//�V�[���J�n�O�̏��������s��
BOOL initMenuScene(void) {

	SetFontSize(32);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	MenuImg = LoadGraph("res/back.PNG", true);
	//PlaySoundFile("res/bgml063.ogg", DX_PLAYTYPE_LOOP);

	Timer = 0;

	selectedGame = 0;

	return TRUE;
}

//�t���[������
void moveMenuScene() {

	if (Timer++ % 30 == 0) {
		new EffectStar(640, 0, rand()%90 + 90);
	}

	//�V���j���[���ڂ̑I��
	//�V(1) �@�V���Ɂ��������ꂽ��A
	if ((EdgeInput & PAD_INPUT_UP)) {
		//�V(1) �A�P��̃��j���[���ڂ��I�����ꂽ�Ƃ���B
		//      �@�������A�������̃��j���[���ڂ��Ȃ��Ƃ��́A�ŉ��i�̃��j���[���ڂ��I�����ꂽ�Ƃ���
		if (--selectedGame < 0) {
			selectedGame = MENU_MAX - 1;
		}
	}


	//�V(2) �@�V���Ɂ��������ꂽ��A
	if ((EdgeInput & PAD_INPUT_DOWN)) {
		//�V(2) �A�P���̃��j���[���ڂ��I�����ꂽ�Ƃ���B�B
		//      �@�������A�����艺�̃��j���[���ڂ��Ȃ��Ƃ��́A�ŏ�i�̃��j���[���ڂ��I�����ꂽ�Ƃ���
		if (++selectedGame >= MENU_MAX) {
			selectedGame = 0;
		}
	}

	//�V(3) �V���Ƀ{�^���P�������ꂽ��I������Ă���V�[����
	if ((EdgeInput & PAD_INPUT_1)) {
		changeScene(menu[selectedGame]);
	}
	
	//�I�u�W�F�N�g�ɓo�^����Ă���I�u�W�F�N�g�S��������
	GameObjectList::instance()->moveAll();
}

//�����_�����O����
void renderMenuScene(void) {

	DrawExtendGraph(0, 0, 640, 480, MenuImg, true);

	//�I�u�W�F�N�g�ɓo�^����Ă���I�u�W�F�N�g�S���\������
	GameObjectList::instance()->renderAll();

	DrawString(30, 50, "PumpkinShot", GetColor(255, 255, 255));
	DrawString(30, 400, "�L�[�����őI���B�{�^���P�Ō���", GetColor(255, 255, 255));

	//�U(2) ���j���[���ڂ̕\��
	int x = 220, y = 140, gapY = 60;	//�ix,y)�F�\���J�n���W�@gapY�F�s�̍���
	for (int i = 0; i < MENU_MAX; i++, y += gapY) {

		//�U(2) �@�I�����ꂽ���ڂ̕\��
		if (i == selectedGame) {
			DrawString(x, y, menuList[i], GetColor(255, 0, 0));
			//�U(2) �A�I������Ă��Ȃ����ڂ̕\��
		}
		else {
			DrawString(x, y, menuList[i], GetColor(255, 255, 255));
		}

	}
}

//�V�[���I�����̌㏈��
void releaseMenuScene(void) {

	//�g���Ă����I�u�W�F�N�g��S�폜����
	GameObjectList::instance()->destruct();
}

//���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  MenuSceneCollideCallback(int nSrc, int nTarget, int nCollideID) {
}
