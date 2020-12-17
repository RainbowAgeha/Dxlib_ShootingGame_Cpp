#include "Shot.h"
#include "bomEffect.h"
#include "Item.h"

StrikeShot::StrikeShot(float _posX, float _PosY, float _angle) : GameObject(SHOT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = _angle;
	Speed = 5.0f;
	ShotImg = LoadGraph("res/needle.PNG", true);
	parent = PLAYER_LAYER;

	GetGraphSizeF(ShotImg, &hitRect.whd.x, &hitRect.whd.y);
	hitRect.ImgPos = pos;

}

StrikeShot::~StrikeShot()
{
}

void StrikeShot::move()
{
	//角度を元に移動する
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	hitRect.ImgPos = pos;
	//画面外に超えるようなら自分から死ぬ
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;

}

void StrikeShot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg, true);
}

void StrikeShot::hit(GameObject* obj, int collideID)
{
	//当たったら自分は死ぬ
	switch (collideID) {
	case PLAYER_TO_SHOT:		
		new bomEffect(pos);

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
