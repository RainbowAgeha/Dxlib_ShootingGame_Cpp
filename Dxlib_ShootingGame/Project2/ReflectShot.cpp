#include "Shot.h"
#include "bomEffect.h"
#include "Item.h"

ReflectShot::ReflectShot(float _posX, float _PosY,float _angle, int _parent) : GameObject(SHOT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = _angle;
	Speed = 5.0f;
	ShotImg = LoadGraph("res/needle.PNG", true);
	parent = _parent;

	GetGraphSizeF(ShotImg, &hitRect.whd.x, &hitRect.whd.y);
	hitRect.ImgPos = pos;

	ReflectCount = 1;

}

ReflectShot::~ReflectShot()
{
}

void ReflectShot::move()
{
	//角度を元に移動する
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	//壁に当たった
	if (ReflectCount > 0) {
		if (pos.y < 0 || pos.y > WINDOW_H - hitRect.whd.y) {
			angle = 360 - angle;
		}
	}

	hitRect.ImgPos = pos;
	//画面外に超えるようなら自分から死ぬ
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;

}

void ReflectShot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg, true);
}

void ReflectShot::hit(GameObject* obj, int collideID)
{
	//当たったら自分は死ぬ
	switch (collideID) {
	case PLAYER_TO_SHOT:
		isDead = true;
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
