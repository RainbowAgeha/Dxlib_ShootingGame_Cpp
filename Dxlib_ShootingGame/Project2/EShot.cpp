#include "Shot.h"
#include "bomEffect.h"
#include "Item.h"

EShot::EShot(float _posX, float _PosY, float _angle, int _parent) : GameObject(ENEMYSHOT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = _angle;
	Speed = 5.0f;

	parent = _parent;

	ShotImg = LoadGraph("res/eshot.png", true);
	GetGraphSizeF(ShotImg, &RectW, &RectH);

	hitRect.ImgPos = pos;
	hitRect.whd = VECTOR{ RectW , RectH , 1 };

}

EShot::~EShot()
{
}

void EShot::move()
{
	//角度を元に移動する
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	hitRect.ImgPos = pos;

	//画面外に超えるようなら自分から死ぬ
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;
}

void EShot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg, true);
}

void EShot::hit(GameObject* obj, int collideID)
{
	//当たったら自分は死ぬ
	switch (collideID) {
	case ENEMY_TO_SHOT:
		//プレイヤーが敵の弾にあたったのでEShot弾は消える
		isDead = true;
		new bomEffect(pos);
		break;
	}
}