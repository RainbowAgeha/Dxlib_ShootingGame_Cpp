#include "Shot.h"
#include "bomEffect.h"
#include "Item.h"

Shot::Shot() : GameObject(SHOT_LAYER)
{
	pos = VECTOR{ 0,0,0 };
	angle = 0;	//デフォルト
	Speed = 5.0f;

	parent = PLAYER_LAYER;

	ShotImg = LoadGraph("res/shot.png", true);
	GetGraphSizeF(ShotImg, &RectW, &RectH);

	hitRect.center = pos;
	hitRect.whd = VECTOR{ RectW , RectH , 1 };
	
}

Shot::Shot(float _posX, float _PosY,int _parent) : GameObject(SHOT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = 0;	//デフォルト
	Speed = 5.0f;

	parent = _parent;

	ShotImg = LoadGraph("res/shot.png", true);
	GetGraphSizeF(ShotImg, &RectW, &RectH);

	hitRect.ImgPos = pos;
	hitRect.whd = VECTOR{ RectW , RectH , 1 };
}

Shot::Shot(float _posX, float _PosY,float _angle, int _parent) : GameObject(SHOT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = _angle;
	Speed = 5.0f;

	parent = _parent;

	ShotImg = LoadGraph("res/shot.png", true);
	GetGraphSizeF(ShotImg, &RectW, &RectH);

	hitRect.ImgPos = pos;
	hitRect.whd = VECTOR{ RectW , RectH , 1 };
}

Shot::~Shot()
{
}

void Shot::move()
{
	//角度を元に移動する
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	hitRect.ImgPos = pos;

	//画面外に超えるようなら自分から死ぬ
	if (pos.x < -50 || pos.x > WINDOW_W + 50  || 
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;
}

void Shot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg,true);
}

void Shot::hit(GameObject* obj, int collideID)
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
		//isDead = true;
		new bomEffect(pos);
		//得点アイテムを生成
		new Item(pos);
		break;
	}
}
