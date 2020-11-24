#include "EffectStar.h"

EffectStar::EffectStar(float _posX, float _PosY, float _angle) : GameObject(EFFECT_LAYER)
{
	pos = VECTOR{ _posX,_PosY,0 };
	angle = _angle;	//�f�t�H���g
	Speed = (float)((rand() % 5) + 1);
	lifeTime = (float)(rand() % 360);

	StarImg = LoadGraph("res/star.png", true);
}

EffectStar::~EffectStar()
{
}

void EffectStar::move()
{
	//�p�x�����Ɉړ�����
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	lifeTime += 0.05f;


	//��ʊO�ɒ�����悤�Ȃ玩�����玀��
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;
}

void EffectStar::render()
{
	//���Ȃ̂Ŕ�����(���דI�ɂǁ[�Ȃ́H
	 // �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	//��]���Ȃ���
	DrawRotaGraph2(pos.x, pos.y ,16, 16, 2.0f, -cos( 3.1415 / 180) * lifeTime, StarImg, TRUE);

	// �`��u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void EffectStar::hit(GameObject* obj, int collideID)
{
}
