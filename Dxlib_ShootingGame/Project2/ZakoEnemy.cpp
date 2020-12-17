#include "ZakoEnemy.h"
#include "Shot.h"


ZakoEnemy::ZakoEnemy(float posX, float posY) :GameObject(ENEMY_LAYER)
{
	pos = { posX , posY , 0 };
	LoadDivGraph("res/sEnemy.png",48,8,6,48,48, EnemyImg, true);

	hp = 1;

	//当たり判定の範囲を取得
	hitRect.ImgPos = pos;
	GetGraphSizeF(EnemyImg[0], &hitRect.whd.x, &hitRect.whd.y);
	EnemyIndex = 0;
	//ランダムでキャラクターを決定する。
	int randInd = rand() % 6;
	switch (randInd) {
	
	case 0:
		EnemyIndex = 0;	//ハチ
		break;
	case 1:
		EnemyIndex = 8;	//キノコ
		break;
	case 2:
		EnemyIndex = 16;	//ウリ
		break;
	case 3:
		EnemyIndex = 20;	//赤樽
		break;
	case 4:
		EnemyIndex = 23;	//青樽
		break;
	case 5:
		EnemyIndex = 24;	//おばけ
		break;
	}

	//移動パターンを暫定ランダム
	MovePatten = rand() % 3;
	//上下の移動量
	UDMoveSpeed = 3;

}

ZakoEnemy::~ZakoEnemy()
{
}

void ZakoEnemy::move()
{
	switch (MovePatten) {
	case 0:
		//右から左に向かって移動するだけの処理
		pos.x -= 2;
		break;
	case 1:
		//右から左に向かって移動しながら上下に移動する処理
		pos.x -= 2;
		pos.y += UDMoveSpeed;
		if (pos.y < 0 || pos.y > 440) UDMoveSpeed = -UDMoveSpeed;

		//稀に攻撃
		AttackTime++;
		if (AttackTime > 90) {
			new EShot(pos.x, pos.y, 180, this->layer);
			AttackTime = 0;
		}

		break;
	case 2:
		//右から左に向かって移動するだけの処理
		pos.x -= 2;

		//稀に攻撃
		AttackTime++;
		if (AttackTime > 120) {
			new EShot(pos.x, pos.y, 45, this->layer);
			new EShot(pos.x, pos.y, 135, this->layer);
			new EShot(pos.x, pos.y, 225, this->layer);
			new EShot(pos.x, pos.y, 315, this->layer);
			AttackTime = 0;
		}
		break;
	}

	//自分自信でどのように終了するか決める
	if (pos.x < -60)isDead = 1;

	//移動後の座標を当たり判定に反映させる
	hitRect.ImgPos = pos;
	colliderCheckAABB_2D(SHOT_LAYER, ENEMY_TO_SHOT);

}

void ZakoEnemy::render()
{
	DrawGraph(pos.x, pos.y, EnemyImg[EnemyIndex], true);
}

void ZakoEnemy::hit(GameObject* obj, int collideID)
{
	//弾と当たった事が返ってきたので、死ぬ
	if (collideID == ENEMY_TO_SHOT) {
		isDead = 1;
	}
}
