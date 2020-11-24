#include "GameMain.h"
#include "GameSceneMain.h"
#include "MenuScene.h"

#include "EffectStar.h"

//メニュー項目のシーン番号の配列
#define MENU_MAX 3
SCENE_NO menu[MENU_MAX] = { SCENE_GAME1, SCENE_GAME2, SCENE_GAME3 };
char *menuList[3] = { "ゲームスタート","ランキング","終了" };
//選択されたゲームを表すメニュー番号の初期化（menuの添え字）
static int selectedGame = 0;

int startfont;

int MenuImg;

#define MASKCOUNT 120

//外部定義(GameMain.cppにて宣言)
extern int Input, EdgeInput;

int StarImg;
int Timer;


//シーン開始前の初期化を行う
BOOL initMenuScene(void) {

	SetFontSize(32);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	MenuImg = LoadGraph("res/back.PNG", true);
	//PlaySoundFile("res/bgml063.ogg", DX_PLAYTYPE_LOOP);

	Timer = 0;

	selectedGame = 0;

	return TRUE;
}

//フレーム処理
void moveMenuScene() {

	if (Timer++ % 30 == 0) {
		new EffectStar(640, 0, rand()%90 + 90);
	}

	//７メニュー項目の選択
	//７(1) ①新たに↑が押されたら、
	if ((EdgeInput & PAD_INPUT_UP)) {
		//７(1) ②１つ上のメニュー項目が選択されたとする。
		//      　ただし、それより上のメニュー項目がないときは、最下段のメニュー項目が選択されたとする
		if (--selectedGame < 0) {
			selectedGame = MENU_MAX - 1;
		}
	}


	//７(2) ①新たに↓が押されたら、
	if ((EdgeInput & PAD_INPUT_DOWN)) {
		//７(2) ②１つ下のメニュー項目が選択されたとする。。
		//      　ただし、それより下のメニュー項目がないときは、最上段のメニュー項目が選択されたとする
		if (++selectedGame >= MENU_MAX) {
			selectedGame = 0;
		}
	}

	//７(3) 新たにボタン１が押されたら選択されているシーンへ
	if ((EdgeInput & PAD_INPUT_1)) {
		changeScene(menu[selectedGame]);
	}
	
	//オブジェクトに登録されているオブジェクト全部動かす
	GameObjectList::instance()->moveAll();
}

//レンダリング処理
void renderMenuScene(void) {

	DrawExtendGraph(0, 0, 640, 480, MenuImg, true);

	//オブジェクトに登録されているオブジェクト全部表示する
	GameObjectList::instance()->renderAll();

	DrawString(30, 50, "PumpkinShot", GetColor(255, 255, 255));
	DrawString(30, 400, "キー↑↓で選択。ボタン１で決定", GetColor(255, 255, 255));

	//６(2) メニュー項目の表示
	int x = 220, y = 140, gapY = 60;	//（x,y)：表示開始座標　gapY：行の高さ
	for (int i = 0; i < MENU_MAX; i++, y += gapY) {

		//６(2) ①選択された項目の表示
		if (i == selectedGame) {
			DrawString(x, y, menuList[i], GetColor(255, 0, 0));
			//６(2) ②選択されていない項目の表示
		}
		else {
			DrawString(x, y, menuList[i], GetColor(255, 255, 255));
		}

	}
}

//シーン終了時の後処理
void releaseMenuScene(void) {

	//使っていたオブジェクトを全削除する
	GameObjectList::instance()->destruct();
}

//当り判定コールバック 　　　ここでは要素を削除しないこと！！
void  MenuSceneCollideCallback(int nSrc, int nTarget, int nCollideID) {
}
