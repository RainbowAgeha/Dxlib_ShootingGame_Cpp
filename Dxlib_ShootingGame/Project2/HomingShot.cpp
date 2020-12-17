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
	//�����Ă���^�[�Q�b�g���������ĒǐՂ���B
	target = NULL;
	long mins = 1 << 30;
	forEach(GameObject, ENEMY_LAYER) {
		if (ptr->hp <= 0)continue;	//HP��0�̓G��_���K�v���Ȃ�
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

	//���񂾂��������
	Speed *= 1.05f;

	//�p�x�����Ɉړ�����
	pos.x += (float)cos(angle * 3.1415 / 180) * Speed;
	pos.y += (float)sin(angle * 3.1415 / 180) * Speed;

	hitRect.ImgPos = pos;
	//��ʊO�ɒ�����悤�Ȃ玩�����玀��
	if (pos.x < -50 || pos.x > WINDOW_W + 50 ||
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;

}

void HomingShot::render()
{
	DrawGraph(pos.x, pos.y, ShotImg, true);
}

void HomingShot::hit(GameObject* obj, int collideID)
{
	//���������玩���͎���
	switch (collideID) {
	case PLAYER_TO_SHOT:
		isDead = true;
		new bomEffect(pos);
		if (rand() % 2 == 0)new Item(pos);//���_�A�C�e���𐶐�
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
