#include "Enemy.h"

#include "Shot.h"
#include "Item.h"

Enemy::Enemy(float _x, float _y, int id):GameObject(ENEMY_LAYER)
{
	//�摜�ǂݍ��݊֌W
	LoadDivGraph("res/boss.png",1,1,1,80,56,&enemyImg, true);
	GetGraphSizeF(enemyImg, &hitRect.whd.x, &hitRect.whd.y);

	//�X�e�[�^�X�Ǘ�
	pos = VECTOR{ _x , _y , 0 };
	speed = 2;		//��������
	BossPattern = BossPattern_Init;
	AttackTime = 0;
	SyncTime = 0;
	hp = 50;
	maxhp = hp;

	hitRect.ImgPos = pos;
	//�g�債�Ă���̂�2�{
	hitRect.whd = VECTOR{ hitRect.whd.x * 2 , hitRect.whd.y * 2 , 1 };
}

Enemy::~Enemy()
{
}

void Enemy::move()
{
	switch (BossPattern) {
	case BossPattern_Init:

		//����̏ꏊ�܂ňړ�
		pos.x -= speed;
		if (pos.x < 400) BossPattern = BossPattern_MoveUp;

		break;
	case BossPattern_MoveUp:

		//����̏ꏊ�܂ňړ�
		pos.y -= speed;
		if (pos.y < 30) BossPattern = BossPattern_MoveDown;

		AttackTime++;
		if (AttackTime > 30) {
			new Shot(pos.x - 30, pos.y,180, this->layer);
			AttackTime = 0;
		}

		break;
	case BossPattern_MoveDown:
		//����̏ꏊ�܂ňړ�
		pos.y += speed;
		if (pos.y > 360) BossPattern = BossPattern_MoveUp;

		AttackTime++;
		if (AttackTime > 30) {
			new Shot(pos.x -30, pos.y, 180, this->layer);
			AttackTime = 0;
		}

		break;

	}

	hitRect.ImgPos = pos;
	colliderCheckAABB_2D(SHOT_LAYER, ENEMY_TO_SHOT);

	//HP��0�ɂȂ����玀��
	if (hp <= 0) isDead = true;
}

void Enemy::render()
{
	//�摜��2�{�̃T�C�Y�ŕ\��
	DrawExtendGraph(pos.x, pos.y,
		pos.x + hitRect.whd.x,
		pos.y + hitRect.whd.y, enemyImg, true);

	//HP�Q�[�W��\��
	//���O�o���Ă����H
	DrawString(30, 400, "�{�X", GetColor(255, 255, 255), true);
	//�g
	DrawBox(30, 440, 630, 450, GetColor(255, 0, 0), true);
	//����
	DrawBoxAA(30, 440, 30.0f + (((float)hp / (float)maxhp) * 600.0f), 450, GetColor(0, 255, 0), true, 1.0f);

}

void Enemy::hit(GameObject* obj, int collideID)
{
	switch (collideID) {
	case ENEMY_TO_SHOT:
		hp -= 5;
		break;
	}
}
