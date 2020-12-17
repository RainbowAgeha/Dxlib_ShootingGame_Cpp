#include "Shot.h"
#include "bomEffect.h"
#include "Item.h"

HomingShot::HomingShot(float _posX, float _PosY, float _angle) : GameObject(SHOT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = _angle;
	Speed = 5.0f;
	ShotImg = LoadGraph("res/shot.png", true);
	parent = PLAYER_LAYER;


	GetGraphSizeF(ShotImg, &hitRect.whd.x, &hitRect.whd.y);
	hitRect.ImgPos = pos;

}

HomingShot::~HomingShot()
{
}

void HomingShot::move()
{
	//生きているターゲットを検索して追跡する。
	target = NULL;
	long mins = 1 << 30;
	forEach(GameObject, ENEMY_LAYER) {
		if (ptr->hp <= 0)continue;	//HPが0の敵を狙う必要がない
		if (mins > ((pos.x - ptr->pos.x) * (pos.x - ptr->pos.x) + (pos.y - ptr->pos.y) * (pos.y - ptr->pos.y))) {
			mins = (long)((pos.x - ptr->pos.x) * (pos.x - ptr->pos.x) + (pos.y - ptr->pos.y) * (pos.y - ptr->pos.y));
			target = ptr;
		}
	}
	if (target != NULL) {
		float targetAngle = atan2(((double)target->pos.y - (double)pos.y), ((double)target->pos.x - (double)pos.x)) * 180 / PI;
		float angleBias = targetAngle - angle;
		while (angleBias < 0)angleBias += 360;

		if (angleBias > 180)angle -= 6;
		else angle += 6;
	}

	//だんだん加速する
	Speed *= 1.05f;

	//角度を元に移動する
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	hitRect.ImgPos = pos;
	//画面外に超えるようなら自分から死ぬ
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;

}

void HomingShot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg, true);
}

void HomingShot::hit(GameObject* obj, int collideID)
{
	//当たったら自分は死ぬ
	switch (collideID) {
	case PLAYER_TO_SHOT:
		isDead = true;
		new bomEffect(pos);
		if (rand() % 2 == 0)new Item(pos);//得点アイテムを生成
		break;
	case ENEMY_TO_SHOT:
		//当たったオブジェクトが自分が撃った弾だったら無視する
		//if (obj->getLayer() == ENEMY_LAYER)break;	//自分の弾じゃねーか！！
		isDead = true;
		new bomEffect(pos);
		//得点アイテムを生成
		new Item(pos);
		break;
	}
}
