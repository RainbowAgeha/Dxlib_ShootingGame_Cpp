#include "EffectStar.h"

EffectStar::EffectStar(float _posX, float _PosY, float _angle) : GameObject(EFFECT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = _angle;	//デフォルト
	Speed = (float)((rand() % 5) + 1);
	lifeTime = (float)(rand() % 360);

	StarImg = LoadGraph("res/star.png", true);
}

EffectStar::~EffectStar()
{
}

void EffectStar::move()
{
	//角度を元に移動する
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	lifeTime += 0.05f;


	//画面外に超えるようなら自分から死ぬ
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;
}

void EffectStar::render()
{
	//星なので半透明(負荷的にどーなの？
	 // 描画ブレンドモードをアルファブレンド（５０％）にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	//回転しながら
	DrawRotaGraph2(pos.x, pos.y ,16, 16, 2.0f, -cos( 3.1415 / 180) * lifeTime, StarImg, TRUE);

	// 描画ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void EffectStar::hit(GameObject* obj, int collideID)
{
}
