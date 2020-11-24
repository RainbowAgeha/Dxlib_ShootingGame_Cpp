#include "Shot.h"
#include "bomEffect.h"
#include "Item.h"

Shot::Shot() : GameObject(SHOT_LAYER)
{
	pos = VECTOR{ 0,0,0 };
	angle = 0;	//�f�t�H���g
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
	angle = 0;	//�f�t�H���g
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
	//�p�x�����Ɉړ�����
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	hitRect.ImgPos = pos;

	//��ʊO�ɒ�����悤�Ȃ玩�����玀��
	if (pos.x < -50 || pos.x > WINDOW_W + 50  || 
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;
}

void Shot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg,true);
}

void Shot::hit(GameObject* obj, int collideID)
{
	//���������玩���͎���
	switch (collideID) {
	case PLAYER_TO_SHOT:
		isDead = true;
		new bomEffect(pos);
		break;
	case ENEMY_TO_SHOT:
		//���������I�u�W�F�N�g���������������e�������疳������
		//if (obj->getLayer() == ENEMY_LAYER)break;	//�����̒e����ˁ[���I�I
		//isDead = true;
		new bomEffect(pos);
		//���_�A�C�e���𐶐�
		new Item(pos);
		break;
	}
}
