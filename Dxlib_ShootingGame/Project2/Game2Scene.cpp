#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game2Scene.h"

#include "ScoreData.h"

//ランキングシーン
//スコアデータなどは外部にて保存してあるのを使用。

//外部定義(GameMain.cppにて宣言)
extern int Input, EdgeInput;
extern int ScoreData[FILEDATA_NUM];

//背景
int Scene2BGImg;

//放置用カウント
int Scene2Time;

// シーン開始前の初期化を行う
BOOL initGame2Scene(void) {

	Scene2BGImg = LoadGraph("res/back.PNG", true);

	//何かあった時用にスコアデータを初期化したあとにロード
	ScoreInit();
	ScoreLoad("res\\SaveData\\scoredata.dat");

	return TRUE;
}

//	フレーム処理
void moveGame2Scene() {

	if ((EdgeInput & PAD_INPUT_1)) {
		changeScene(SCENE_MENU);
	}

}

//	レンダリング処理
void renderGame2Scene(void) {

	//DrawString(30, 50, "ゲーム画面２です", GetColor(255, 255, 255));
	//DrawString(30, 100, "ボタン１でタイトルに戻る", GetColor(255, 255, 255));

	DrawGraph(0, 0, Scene2BGImg, true);

	DrawString(0, 0, "Ranking", GetColor(255, 255, 255));

	//ランキングデータの表示する。
	for (int i = 0; i < FILEDATA_NUM; i++) {
		DrawFormatString(100 + i *10, 60 + i * 40, GetColor(255, 255, 255), "%2d : %08d", i + 1, ScoreData[i]);
	}

}

//	シーン終了時の後処理
void releaseGame2Scene(void) {


}

// 当り判定コールバック 　　　ここでは要素を削除しないこと！！
void  Game2SceneCollideCallback(int nSrc, int nTarget, int nCollideID) {



}
