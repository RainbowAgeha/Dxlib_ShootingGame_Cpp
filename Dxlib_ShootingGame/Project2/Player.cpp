#include "Player.h"

Player::Player() : GameObject(PLAYER_LAYER)
{
	playerImg = LoadGraph("res/ura_R.png", true);
	x = y = z = 0;

	PlayerInit();

	//�̌��p������
	x = 100;
	y = 240;

	pos = VECTOR{ x , y , z };
	//�摜�̑傫���͉摜���g�̉����c���ɒ���
	GetGraphSizeF(playerImg, &RectW, &RectH);

	//�V���b�g�̈ʒu�͊�{�E���̃C�J����
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

	//Object�ɏ�����͂���
	pos = VECTOR{ x,y,z };
	hitRect.ImgPos = pos;
}

void Player::render()
{
	DrawGraphF(pos.x, pos.y, playerImg, true);

	//�X�R�A�̕\��
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
