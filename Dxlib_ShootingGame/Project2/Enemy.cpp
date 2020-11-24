#include "Enemy.h"

#include "Shot.h"
#include "Item.h"

Enemy::Enemy(float _x, float _y, int id):GameObject(ENEMY_LAYER)
{
	//画像読み込み関係
	LoadDivGraph("res/boss.png",1,1,1,80,56,&enemyImg, true);
	GetGraphSizeF(enemyImg, &hitRect.whd.x, &hitRect.whd.y);

	//ステータス管理
	pos = VECTOR{ _x , _y , 0 };
	speed = 2;		//ゆっくりめ
	BossPattern = BossPattern_Init;
	AttackTime = 0;
	SyncTime = 0;
	hp = 50;
	maxhp = hp;

	hitRect.ImgPos = pos;
	//拡大しているので2倍
	hitRect.whd = VECTOR{ hitRect.whd.x * 2 , hitRect.whd.y * 2 , 1 };
}

Enemy::~Enemy()
{
}

void Enemy::move()
{
	switch (BossPattern) {
	case BossPattern_Init:

		//特定の場所まで移動
		pos.x -= speed;
		if (pos.x < 400) BossPattern = BossPattern_MoveUp;

		break;
	case BossPattern_MoveUp:

		//特定の場所まで移動
		pos.y -= speed;
		if (pos.y < 30) BossPattern = BossPattern_MoveDown;

		AttackTime++;
		if (AttackTime > 30) {
			new Shot(pos.x - 30, pos.y,180, this->layer);
			AttackTime = 0;
		}

		break;
	case BossPattern_MoveDown:
		//特定の場所まで移動
		pos.y += speed;
		if (pos.y > 360) BossPattern = BossPattern_MoveUp;

		AttackTime++;
		if (AttackTime > 30) {
			new Shot(pos.x -30, pos.y, 180, this->layer);
			AttackTime = 0;
		}

		break;

	}

	hitRect.ImgPos = pos;
	colliderCheckAABB_2D(SHOT_LAYER, ENEMY_TO_SHOT);

	//HPが0になったら死ぬ
	if (hp <= 0) isDead = true;
}

void Enemy::render()
{
	//画像を2倍のサイズで表示
	DrawExtendGraph(pos.x, pos.y,
		pos.x + hitRect.whd.x,
		pos.y + hitRect.whd.y, enemyImg, true);

	//HPゲージを表示
	//名前出しておく？
	DrawString(30, 400, "ボス", GetColor(255, 255, 255), true);
	//枠
	DrawBox(30, 440, 630, 450, GetColor(255, 0, 0), true);
	//現在
	DrawBoxAA(30, 440, 30.0f + (((float)hp / (float)maxhp) * 600.0f), 450, GetColor(0, 255, 0), true, 1.0f);

}

void Enemy::hit(GameObject* obj, int collideID)
{
	switch (collideID) {
	case ENEMY_TO_SHOT:
		hp -= 5;
		break;
	}
}
