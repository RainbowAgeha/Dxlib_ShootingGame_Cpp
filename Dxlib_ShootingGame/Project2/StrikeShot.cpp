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
	//�p�x�����Ɉړ�����
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	hitRect.ImgPos = pos;
	//��ʊO�ɒ�����悤�Ȃ玩�����玀��
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;

}

void StrikeShot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg, true);
}

void StrikeShot::hit(GameObject* obj, int collideID)
{
	//���������玩���͎���
	switch (collideID) {
	case PLAYER_TO_SHOT:		
		new bomEffect(pos);

		break;
	case ENEMY_TO_SHOT:
		//���������I�u�W�F�N�g���������������e�������疳������
		//if (obj->getLayer() == ENEMY_LAYER)break;	//�����̒e����ˁ[���I�I
		isDead = true;
		new bomEffect(pos);
		//���_�A�C�e���𐶐�
		new Item(pos);
		break;
	}
}
