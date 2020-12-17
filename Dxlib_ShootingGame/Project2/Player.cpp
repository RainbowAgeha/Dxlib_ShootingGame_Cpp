#include "Player.h"

Player::Player() : GameObject(PLAYER_LAYER)
{
	playerImg = LoadGraph("res/ura_R.png", true);
	x = y = z = 0;

	PlayerInit();

	//体験用調整中
	//x = 100;
	//y = 240;

	pos = VECTOR{ x , y , z };
	//画像の大きさは画像自身の横幅縦幅に注意
	GetGraphSizeF(playerImg, &RectW, &RectH);

	//ショットの位置は基本右下のイカから
	ShotX = x + RectW;
	ShotY = y + RectH - 10;

	score = 0;
	ComboCount = 0;
	ComboTimer = 0;

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

	if (ComboTimer-- < 0) {
		ComboTimer = 0;
		ComboCount = 0;
	}

	//Objectに情報を入力する
	pos = VECTOR{ x,y,z };
	hitRect.ImgPos = pos;

	colliderCheckAABB_2D(ENEMYSHOT_LAYER, ENEMY_TO_SHOT);
}

void Player::render()
{
	DrawGraphF(pos.x, pos.y, playerImg, true);

	//コンボが0の場合は表示しない。
	if (ComboCount > 0) {
		//枠
		DrawBox(300, 40, 630, 60, GetColor(255, 0, 0), true);
		//現在
		DrawBoxAA(300, 40, 300.0f + (((float)ComboTimer / 180.0f) * 330.0f), 60, GetColor(0, 255, 0), true, 1.0f);

		DrawFormatString(350, 40, GetColor(255, 255, 255), "COMBO:%d", ComboCount);
	}

	//スコアの表示
	DrawFormatString(300, 0, GetColor(255, 255, 255), "Score:%09d", score);
}

void Player::hit(GameObject* obj, int collideID)
{
	switch (collideID) {
	case PLAYER_TO_ITEM:
		score += BASE_POINT *(1 + ComboCount);
		ComboTimer = 180;
		ComboCount += 1;
		 
		break;
	case ENEMY_TO_SHOT:
		//敵の弾と当たった
		score -= 2000;
		if (score < 0)score = 0;

		break;
	}
}
