#include "ZakoEnemy.h"
#include "Shot.h"


ZakoEnemy::ZakoEnemy(float posX, float posY) :GameObject(ENEMY_LAYER)
{
	pos = { posX , posY , 0 };
	LoadDivGraph("res/sEnemy.png",48,8,6,48,48, EnemyImg, true);

	hp = 1;

	//�����蔻��͈̔͂��擾
	hitRect.ImgPos = pos;
	GetGraphSizeF(EnemyImg[0], &hitRect.whd.x, &hitRect.whd.y);
	EnemyIndex = 0;
	//�����_���ŃL�����N�^�[�����肷��B
	int randInd = rand() % 6;
	switch (randInd) {
	
	case 0:
		EnemyIndex = 0;	//�n�`
		break;
	case 1:
		EnemyIndex = 8;	//�L�m�R
		break;
	case 2:
		EnemyIndex = 16;	//�E��
		break;
	case 3:
		EnemyIndex = 20;	//�ԒM
		break;
	case 4:
		EnemyIndex = 23;	//�M
		break;
	case 5:
		EnemyIndex = 24;	//���΂�
		break;
	}

	//�ړ��p�^�[�����b�胉���_��
	MovePatten = rand() % 3;
	//�㉺�̈ړ���
	UDMoveSpeed = 3;

}

ZakoEnemy::~ZakoEnemy()
{
}

void ZakoEnemy::move()
{
	switch (MovePatten) {
	case 0:
		//�E���獶�Ɍ������Ĉړ����邾���̏���
		pos.x -= 2;
		break;
	case 1:
		//�E���獶�Ɍ������Ĉړ����Ȃ���㉺�Ɉړ����鏈��
		pos.x -= 2;
		pos.y += UDMoveSpeed;
		if (pos.y < 0 || pos.y > 440) UDMoveSpeed = -UDMoveSpeed;

		//�H�ɍU��
		AttackTime++;
		if (AttackTime > 90) {
			new EShot(pos.x, pos.y, 180, this->layer);
			AttackTime = 0;
		}

		break;
	case 2:
		//�E���獶�Ɍ������Ĉړ����邾���̏���
		pos.x -= 2;

		//�H�ɍU��
		AttackTime++;
		if (AttackTime > 120) {
			new EShot(pos.x, pos.y, 45, this->layer);
			new EShot(pos.x, pos.y, 135, this->layer);
			new EShot(pos.x, pos.y, 225, this->layer);
			new EShot(pos.x, pos.y, 315, this->layer);
			AttackTime = 0;
		}
		break;
	}

	//�������M�łǂ̂悤�ɏI�����邩���߂�
	if (pos.x < -60)isDead = 1;

	//�ړ���̍��W�𓖂��蔻��ɔ��f������
	hitRect.ImgPos = pos;
	colliderCheckAABB_2D(SHOT_LAYER, ENEMY_TO_SHOT);

}

void ZakoEnemy::render()
{
	DrawGraph(pos.x, pos.y, EnemyImg[EnemyIndex], true);
}

void ZakoEnemy::hit(GameObject* obj, int collideID)
{
	//�e�Ɠ������������Ԃ��Ă����̂ŁA����
	if (collideID == ENEMY_TO_SHOT) {
		isDead = 1;
	}
}
