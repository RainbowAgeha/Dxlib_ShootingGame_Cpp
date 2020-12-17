#include "Item.h"

Item::Item(VECTOR pos):GameObject(ITEM_LAYER)
{
	this->pos = pos;
	ItemImg = LoadGraph("res/kabocoin.PNG",true);
	GetGraphSizeF(ItemImg, &hitRect.whd.x, &hitRect.whd.y);
	hitRect.ImgPos = pos;

	//当たり判定を広く取る
	hitRect.whd = VECTOR{ hitRect.whd.x * 2,hitRect.whd.y * 2 ,1 };

	DropSpeed = -20;

	UpSpeed = (rand() % 6) - 3;

}

Item::~Item()
{
}

void Item::move()
{
	//プレイヤーに向かって移動
	DropSpeed += 1;
	if (DropSpeed > 5)DropSpeed = 5;	//加速させすぎない
	pos.x -= DropSpeed;
	pos.y += UpSpeed;
	
	//画面外に超えるようなら自分から死ぬ
	if (pos.x < -50 ||
		pos.x > WINDOW_W + 200)  isDead = true;	//画面→は過ぎても無視する(何かあった時用の保険
		//pos.y < -50 || pos.y > WINDOW_H + 50) isDead = true;

	//上下は反転する
	if (pos.y < 0 || pos.y > WINDOW_H - 32)UpSpeed = -UpSpeed;


	//当たり判定を見た目の2倍に
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
