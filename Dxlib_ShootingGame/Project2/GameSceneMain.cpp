#include "GameSceneMain.h"

//全てのシーンのヘッダファイルをインクルードする
#include "Game1Scene.h"
#include "Game2Scene.h"
#include "Game3Scene.h"
#include "MenuScene.h"


//このファイル内だけで使用する関数のプロトタイプ宣言
//現在のシーンの初期化処理
void initCurrentScene(void);
//現在のシーンのフレーム処理
void moveCurrentScene();
//現在のシーンのレンダリング処理
void renderCurrentScene(void);
//現在のシーンの削除処理
void releaseCurrentScene(void);

//このファイル内だけで使用する変数の宣言（staticをつけて宣言する）
static SCENE_NO sceneNo = SCENE_NONE;	// 現在のシーン番号（必ず初期値はSCENE_NONE）
static SCENE_NO prevScene = SCENE_NONE;	// 1つ前のシーン番号（必ず初期値はSCENE_NONE）
static SCENE_NO nextScene = SCENE_NONE;	// 次のシーン番号（必ず初期値はSCENE_NONE）

// 反転円の描画
int DrawReversalCircle(int x, int y, int r, int Color);

int FadeCount;
int FadeInStartFlag;
int FadeInSceneFlag;	//完了したら1
int FadeOutSceneFlag;

//３ゲーム開始前の初期化を行う
BOOL InitGame(void){

	FadeCount = 0;
	FadeInSceneFlag = 0;	
	FadeOutSceneFlag = 0;
	FadeInStartFlag = 0;

	//３(1) 初めのシーン番号の設定
	changeScene(SCENE_MENU);
	return TRUE;
}

//フレーム処理
void FrameMove(){

	//アイリスインループ開始
	if(FadeInStartFlag == 1){
		// ループ
		FadeCount += 6;
		if (FadeCount > 400) {
			FadeInSceneFlag = 1;
		}
	}else{
		//実行開始時のみ、一通り処理を1回のみ終わらせる
		initCurrentScene();
		renderCurrentScene();

		FadeInStartFlag = 1;
	}

	// 次のシーンに変更するかどうか判断する
	if (sceneNo != nextScene) {
		FadeOutSceneFlag = 1;
	}

	if (FadeOutSceneFlag == 1) {
		//シーンを変更しそうであればフェードアウトを実施する
		// ループ
		FadeCount += 6;
		//演出が終わるまでループ
		if (FadeCount > 400) {
			//現在のシーンの削除処理
			releaseCurrentScene();
			//現在のシーンを新規シーンに変更する
			sceneNo = nextScene;
			//新しいシーンの初期化処理
			initCurrentScene();

			FadeCount = 0;
			FadeInSceneFlag = 0;
			FadeOutSceneFlag = 0;
		}
	}

	//フェードイン・アウト中は処理を行わない
	if (FadeInSceneFlag == 1 && FadeOutSceneFlag == 0 ) {
		//現在のシーンのフレーム処理
		moveCurrentScene();
	}
}

//レンダリング処理
void RenderScene(){

	//現在のシーンのレンダリング処理
	renderCurrentScene();

	//アイリスアウトを行う
	if (FadeInSceneFlag == 0) {
		// 描画したグラフィックの上に反転円を描く
		DrawReversalCircle(320, 240, 1 ? FadeCount : 399 - FadeCount, 0);
	}

	//アイリスインを行う
	if (FadeOutSceneFlag == 1) {
		// 描画したグラフィックの上に反転円を描く
		DrawReversalCircle(320, 240, 0 ? FadeCount : 399 - FadeCount, 0);
	}

}

//ゲーム終了時の後処理
void GameRelease(void){
	//現在のシーンの削除処理
	releaseCurrentScene();
	//メインから抜けるので、オブジェクトの全削除を行う
	GameObjectList::instance()->destruct();
}

//３(2) 当り判定コールバック 　　　ここでは要素を削除しないこと！！
void  CollideCallback(int nSrc, int nTarget, int nCollideID){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	MenuSceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME1:	Game1SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME2:	Game2SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME3:	Game3SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "まだそのシーンはない", "作成途中", 0);
		changeScene(prevScene);
	}
}

//シーンを変更する関数
void changeScene(SCENE_NO no){
	// 現在のシーンと同じときは何もしない
	if (sceneNo == no)return;
	// 正しくないシーン番号の時は無視する
	if (no >= SCENE_MAX) return;
	if (no <= SCENE_NONE) return;
	// シーンを変更する
	FadeCount = 0;
	prevScene = sceneNo;
	nextScene = no;

}

//３(3) 現在のシーンの初期化処理
void initCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	initMenuScene();	break;
	case SCENE_GAME1:	initGame1Scene();	break;
	case SCENE_GAME2:	initGame2Scene();	break;
	case SCENE_GAME3:	initGame3Scene();	break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "まだそのシーンはない", "作成途中", 0);
		changeScene(prevScene);
	}
}
//３(4) 現在のシーンのフレーム処理
void moveCurrentScene(){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	moveMenuScene();		break;
	case SCENE_GAME1:	moveGame1Scene();		break;
	case SCENE_GAME2:	moveGame2Scene();		break;
	case SCENE_GAME3:	moveGame3Scene();		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "まだそのシーンはない", "作成途中", 0);
		changeScene(prevScene);
	}
}
//３(5) 現在のシーンのレンダリング処理
void renderCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	renderMenuScene();		break;
	case SCENE_GAME1:	renderGame1Scene();		break;
	case SCENE_GAME2:	renderGame2Scene();		break;
	case SCENE_GAME3:	renderGame3Scene();		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "まだそのシーンはない", "作成途中", 0);
		changeScene(prevScene);
	}
}
//３(6) 現在のシーンの削除処理
void releaseCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	releaseMenuScene();		break;
	case SCENE_GAME1:	releaseGame1Scene();	break;
	case SCENE_GAME2:	releaseGame2Scene();	break;
	case SCENE_GAME3:	releaseGame3Scene();	break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "まだそのシーンはない", "作成途中", 0);
		changeScene(prevScene);
	}
}

// 反転円の描画
int DrawReversalCircle(int x, int y, int r, int Color)
{
	// 円反転描画領域の外側を描画
	DrawBox(0, 0, 640, y - r, Color, TRUE);
	DrawBox(0, y - r, x - r, 480, Color, TRUE);
	DrawBox(x - r, y + r + 1, 640, 480, Color, TRUE);
	DrawBox(x + r, y - r, 640, y + r + 1, Color, TRUE);

	// 描画処理
	{
		int Dx, Dy, F, j;
		int x1, x2, y1;

		// 初期値セット
		Dx = r; Dy = 0; F = -2 * r + 3;

		j = 0;
		// 描画開始
		{
			// まず最初に座標データを進める
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

			// 描き切るまでループ
			while (Dx >= Dy)
			{
				// ラインを描く
				x2 = Dx + x; x1 = -Dx + x; y1 = Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);
				x2 = Dx + x; x1 = -Dx + x; y1 = -Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);

				// 座標データを進める
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


	// 終了
	return 0;
}