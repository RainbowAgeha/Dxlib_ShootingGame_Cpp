#include "Player.h"

Player::Player() : GameObject(PLAYER_LAYER)
{
	playerImg = LoadGraph("res/ura_R.png", true);
	x = y = z = 0;

	PlayerInit();

	//体験用調整中
	x = 100;
	y = 240;

	pos = VECTOR{ x , y , z };
	//画像の大きさは画像自身の横幅縦幅に注意
	GetGraphSizeF(playerImg, &RectW, &RectH);

	//ショットの位置は基本右下のイカから
	ShotX = x + RectW;
	ShotY = y + RectH - 10;

	score = 0;

	hitRect.ImgPos = pos;
	hitRect.whd = VECTOR{ RectW/2 , RectH/2 , 1 };
}

Player::~Player()
{
	DeleteGraph(playerImg,false);
}

void Player::move()
{
	PlayerMove();

	ShotX = x + RectW;
	ShotY = y + RectH -10;

	PlayerAttack();

	//Objectに情報を入力する
	pos = VECTOR{ x,y,z };
	hitRect.ImgPos = pos;
}

void Player::render()
{
	DrawGraphF(pos.x, pos.y, playerImg, true);

	//スコアの表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Score:%d", score);
}

void Player::hit(GameObject* obj, int collideID)
{
	switch (collideID) {
	case PLAYER_TO_ITEM:
		score += 50;
		break;
	}
}
