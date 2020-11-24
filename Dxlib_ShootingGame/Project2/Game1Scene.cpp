#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game1Scene.h"
#include <math.h>

#include "Player.h"
#include "Enemy.h"

#include "ZakoEnemy.h"

//外部定義
extern int Input, EdgeInput;

//画像変数
int Img_BG;
int Img_CroudLayer1;	//一番奥
int Img_CroudLayer2;
int Img_CroudLayer3;	//手前

int Img_BG_x;
int Img_CL1_x;
int Img_CL2_x;
int Img_CL3_x;


enum {
	GAME_INIT,
	GAME_MAIN,
	GAME_COMMING,
	GAME_BOSS,
	GAME_GAMECLEAR,
	GAME_GAMEOVER,
	GAME_RESULT
};
int GameMode;
int GameTime;
int PerformanceTime;

// シーン開始前の初期化を行う
BOOL initGame1Scene(void) {

	Img_BG = LoadGraph("res/back.PNG", true);
	Img_CroudLayer1 = LoadGraph("res/haikei1.PNG", true);
	Img_CroudLayer2 = LoadGraph("res/haikei2.PNG", true);
	Img_CroudLayer3 = LoadGraph("res/haikei3.PNG", true);

	Img_BG_x = Img_CL1_x = Img_CL2_x = Img_CL3_x = 0;

	//プレイヤーを生成
	new Player();

	GameMode = GAME_MAIN;

	//プレイ時間　秒　× 60フレーム
	GameTime = 60 * 60;
	PerformanceTime = 5 * 60;

	//new Enemy(800,200,0);
	
	return TRUE;
}

//	フレーム処理
void moveGame1Scene() {

	////デバックボタン
	//if ((EdgeInput & PAD_INPUT_4)) {
	//	changeScene(SCENE_MENU);
	//}

	switch (GameMode) {
	case GAME_INIT:

		break;
	case GAME_MAIN:
		//背景スクロール　奥から手前に向かって早くなる
		Img_CL1_x -= 2;
		Img_CL2_x -= 3;
		Img_CL3_x -= 4;
		if (Img_CL1_x < -WINDOW_W)Img_CL1_x += WINDOW_W;
		if (Img_CL2_x < -WINDOW_W)Img_CL2_x += WINDOW_W;
		if (Img_CL3_x < -WINDOW_W)Img_CL3_x += WINDOW_W;

		//暫定　ザコ敵のオブジェクトを生成する
		new ZakoEnemy(640, rand() % 480);

		GameTime--;
		if (GameTime < 0) GameMode = GAME_COMMING;

		break;
	case GAME_COMMING:
		//背景スクロール　奥から手前に向かって早くなる
		Img_CL1_x -= 2;
		Img_CL2_x -= 3;
		Img_CL3_x -= 4;
		if (Img_CL1_x < -WINDOW_W)Img_CL1_x += WINDOW_W;
		if (Img_CL2_x < -WINDOW_W)Img_CL2_x += WINDOW_W;
		if (Img_CL3_x < -WINDOW_W)Img_CL3_x += WINDOW_W;

		PerformanceTime--;
		if (PerformanceTime < 0) {
			GameMode = GAME_BOSS;
			GameTime = 121 * 60;	
			new Enemy(800, 200, 0);
		}

		break;
	case GAME_BOSS:
		//背景スクロール　奥から手前に向かって早くなる
		Img_CL1_x -= 2;
		Img_CL2_x -= 3;
		Img_CL3_x -= 4;
		if (Img_CL1_x < -WINDOW_W)Img_CL1_x += WINDOW_W;
		if (Img_CL2_x < -WINDOW_W)Img_CL2_x += WINDOW_W;
		if (Img_CL3_x < -WINDOW_W)Img_CL3_x += WINDOW_W;

		//敵が居なくなったのでリザルト画面へ
		if (GameObjectList::instance()->getObjectNum(ENEMY_LAYER) == 0) {
			GameMode = GAME_GAMECLEAR;
			PerformanceTime = 5 * 60;
		}

		GameTime--;
		//残り時間が0になった場合強制終了
		if (GameTime < 0) {
			GameMode = GAME_GAMEOVER;
			PerformanceTime = 5 * 60;
		}

		break;
	case GAME_GAMECLEAR:
	case GAME_GAMEOVER:
		PerformanceTime--;
		if (PerformanceTime < 0) {
			PerformanceTime = 6 * 60;
			GameMode = GAME_RESULT;
		}

		break;
	case GAME_RESULT:
		//リザルト中なので、スクロールは止める

		//表示中にボタンを押したらスキップ
		PerformanceTime--;
		if (PerformanceTime >= 60) {
			if ((EdgeInput & PAD_INPUT_1)) {
				PerformanceTime = 1 * 60;
			}
		}

		//ボタンを押したらタイトルへ
		if (PerformanceTime < 0) {
			if ((EdgeInput & PAD_INPUT_1)) {
				changeScene(SCENE_MENU);
			}
		}
		break;
	}

	//オブジェクトに登録されているオブジェクト全部動かす
	GameObjectList::instance()->moveAll();

}


//	レンダリング処理
void renderGame1Scene(void){

	//背景
	DrawGraph(Img_BG_x, 0, Img_BG,true);

	DrawGraph(Img_CL1_x, WINDOW_H-240, Img_CroudLayer1, true);
	DrawGraph(Img_CL1_x + WINDOW_W, WINDOW_H-240, Img_CroudLayer1, true);

	DrawGraph(Img_CL2_x, WINDOW_H - 180, Img_CroudLayer2, true);
	DrawGraph(Img_CL2_x + WINDOW_W, WINDOW_H - 180, Img_CroudLayer2, true);

	DrawGraph(Img_CL3_x, WINDOW_H - 160, Img_CroudLayer3, true);
	DrawGraph(Img_CL3_x + WINDOW_W, WINDOW_H - 160, Img_CroudLayer3, true);

	DrawFormatString(200, 0, GetColor(255, 255, 255), "Time:%d", GameTime / 60);

	//オブジェクトに登録されているオブジェクト全部表示する
	GameObjectList::instance()->renderAll();

	//モードに応じた演出
	switch (GameMode) {
	case GAME_INIT:

		break;
	case GAME_MAIN:

		break;
	case GAME_COMMING:
		DrawBox(0, 200, 640, 300, GetColor(128,128,128), true);
		if ( (PerformanceTime % 60) <= 30 ) {
			DrawString(150, 230, "BOSS COMMING...", GetColor(255, 255, 255), true);
		}

		break;
	case GAME_BOSS:

		break;
	case GAME_GAMECLEAR:
		DrawString(100, 200, "GAME CLEAR!!!", GetColor(255, 255, 255), true);

		break;
	case GAME_GAMEOVER:
		DrawString(100, 200, "GAME OVER!!!", GetColor(255, 255, 255), true);
		break;

	case GAME_RESULT:
		if (PerformanceTime < 5 * 60) {
			DrawString(100, 100, "Boss Bonus:", GetColor(255, 255, 255), true);
		}
		if (PerformanceTime < 4 * 60) {
			DrawString(100, 150, "Time Bonus:", GetColor(255, 255, 255), true);
		}
		if (PerformanceTime < 3 * 60) {
			DrawString(100, 200, "     Score:", GetColor(255, 255, 255), true);
		}
		if (PerformanceTime < 2 * 60) {
			DrawString(100, 250, "Your Rank...", GetColor(255, 255, 255), true);
		}

		if (PerformanceTime < 0) {
			//if(score > 1000000)
			DrawString(150,350, "Subarasi---!!!", GetColor(255, 255, 255), true);
		}

		if (PerformanceTime < 0) {
			DrawString(100, 400, "ボタン１でタイトルに戻る", GetColor(255, 255, 255), true);
		}

		break;
	}

}

//	シーン終了時の後処理
void releaseGame1Scene(void) {

	//使っていたオブジェクトを全削除する
	GameObjectList::instance()->destruct();

}

// 当り判定コールバック 　　　ここでは要素を削除しないこと！！
void  Game1SceneCollideCallback(int nSrc, int nTarget, int nCollideID) {

}
