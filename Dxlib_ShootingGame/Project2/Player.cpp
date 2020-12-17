#include "Player.h"

Player::Player() : GameObject(PLAYER_LAYER)
{
	playerImg = LoadGraph("res/ura_R.png", true);
	x = y = z = 0;

	PlayerInit();

	//�̌��p������
	//x = 100;
	//y = 240;

	pos = VECTOR{ x , y , z };
	//�摜�̑傫���͉摜���g�̉����c���ɒ���
	GetGraphSizeF(playerImg, &RectW, &RectH);

	//�V���b�g�̈ʒu�͊�{�E���̃C�J����
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

	//Object�ɏ�����͂���
	pos = VECTOR{ x,y,z };
	hitRect.ImgPos = pos;

	colliderCheckAABB_2D(ENEMYSHOT_LAYER, ENEMY_TO_SHOT);
}

void Player::render()
{
	DrawGraphF(pos.x, pos.y, playerImg, true);

	//�R���{��0�̏ꍇ�͕\�����Ȃ��B
	if (ComboCount > 0) {
		//�g
		DrawBox(300, 40, 630, 60, GetColor(255, 0, 0), true);
		//����
		DrawBoxAA(300, 40, 300.0f + (((float)ComboTimer / 180.0f) * 330.0f), 60, GetColor(0, 255, 0), true, 1.0f);

		DrawFormatString(350, 40, GetColor(255, 255, 255), "COMBO:%d", ComboCount);
	}

	//�X�R�A�̕\��
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
		//�G�̒e�Ɠ�������
		score -= 2000;
		if (score < 0)score = 0;

		break;
	}
}
