#include "ZakoEnemy.h"


ZakoEnemy::ZakoEnemy(float posX, float posY)
{
	pos = { posX , posY , 0 };
	EnemyImg = LoadGraph("res/kabocoin.PNG", true);

	//当たり判定の範囲を取得
	hitRect.ImgPos = pos;
	GetGraphSizeF(EnemyImg, &hitRect.whd.x, &hitRect.whd.y);

}

ZakoEnemy::~ZakoEnemy()
{
}

void ZakoEnemy::move()
{
	//暫定で右から左に向かって移動するだけの処理
	pos.x -= 1;

	//自分自信でどのように終了するか決める
	//暫定：画面の中央付近に超えたら死ぬ
	if (pos.x < 320)isDead = 1;

	//移動後の座標を当たり判定に反映させる
	hitRect.ImgPos = pos;
	colliderCheckAABB_2D(SHOT_LAYER, ENEMY_TO_SHOT);

}

void ZakoEnemy::render()
{
	DrawGraph(pos.x, pos.y, EnemyImg, true);
}

void ZakoEnemy::hit(GameObject* obj, int collideID)
{
	//弾と当たった事が返ってきたので、死ぬ
	if (collideID == ENEMY_TO_SHOT) {
		isDead = 1;
	}
}
