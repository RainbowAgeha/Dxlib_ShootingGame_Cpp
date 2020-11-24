#include "Item.h"

Item::Item(VECTOR pos):GameObject(ITEM_LAYER)
{
	this->pos = pos;
	ItemImg = LoadGraph("res/kabocoin.PNG",true);
	GetGraphSizeF(ItemImg, &hitRect.whd.x, &hitRect.whd.y);
	hitRect.ImgPos = pos;

	//�����蔻����L�����
	hitRect.whd = VECTOR{ hitRect.whd.x * 2,hitRect.whd.y * 2 ,1 };

	DropSpeed = -20;

}

Item::~Item()
{
}

void Item::move()
{
	//�v���C���[�Ɍ������Ĉړ�
	DropSpeed += 1;
	if (DropSpeed > 5)DropSpeed = 5;	//�������������Ȃ�
	pos.x -= DropSpeed;
	
	//��ʊO�ɒ�����悤�Ȃ玩�����玀��
	if (pos.x < -50 ||
		pos.x > WINDOW_W + 200 ||	//��ʁ��͉߂��Ă���������(�������������p�̕ی�
		pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;

	//�����蔻��������ڂ�2�{��
	hitRect.ImgPos = VECTOR{ pos.x - hitRect.whd.x,pos.y - hitRect.whd.y ,1};
	colliderCheckAABB_2D(PLAYER_LAYER, PLAYER_TO_ITEM);
}

void Item::render()
{
	DrawGraph(pos.x, pos.y, ItemImg, true);
}

void Item::hit(GameObject* obj, int collideID)
{
	switch (collideID) {
	case PLAYER_TO_ITEM:
		isDead = true;
		break;
	}
}
