#include "ZakoEnemy.h"


ZakoEnemy::ZakoEnemy(float posX, float posY)
{
	pos = { posX , posY , 0 };
	EnemyImg = LoadGraph("res/kabocoin.PNG", true);

	//�����蔻��͈̔͂��擾
	hitRect.ImgPos = pos;
	GetGraphSizeF(EnemyImg, &hitRect.whd.x, &hitRect.whd.y);

}

ZakoEnemy::~ZakoEnemy()
{
}

void ZakoEnemy::move()
{
	//�b��ŉE���獶�Ɍ������Ĉړ����邾���̏���
	pos.x -= 1;

	//�������M�łǂ̂悤�ɏI�����邩���߂�
	//�b��F��ʂ̒����t�߂ɒ������玀��
	if (pos.x < 320)isDead = 1;

	//�ړ���̍��W�𓖂��蔻��ɔ��f������
	hitRect.ImgPos = pos;
	colliderCheckAABB_2D(SHOT_LAYER, ENEMY_TO_SHOT);

}

void ZakoEnemy::render()
{
	DrawGraph(pos.x, pos.y, EnemyImg, true);
}

void ZakoEnemy::hit(GameObject* obj, int collideID)
{
	//�e�Ɠ������������Ԃ��Ă����̂ŁA����
	if (collideID == ENEMY_TO_SHOT) {
		isDead = 1;
	}
}
