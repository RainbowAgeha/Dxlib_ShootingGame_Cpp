#include "Player.h"
#include "Shot.h"

void Player::PlayerInit() {
	x = -300;
	y = -300;
}

void Player::PlayerMove()
{

	//�v���C���[�̈ړ�
	if ((Input & PAD_INPUT_LEFT)) {
		x = x - 5.0f;
	}

	if ((Input & PAD_INPUT_RIGHT)) {
		x = x + 5.0f;
	}

	if ((Input & PAD_INPUT_UP)) {
		y = y - 5.0f;
	}

	if ((Input & PAD_INPUT_DOWN)) {
		y = y + 5.0f;
	}

	//�v���C���[�̈ʒu����ʓ��ɋ���悤�ɂ���
	//if (x < 0) x = 0;
	//if (y < 0) y = 0;
	if (x > WINDOW_W) x = WINDOW_W;
	if (y > WINDOW_H) y = WINDOW_H;
}

void Player::PlayerAttack()
{

	//�v���C���[�U��
	if ((EdgeInput & PAD_INPUT_1)) {
		new Shot(ShotX, ShotY, this->layer);
	}

	if ((EdgeInput & PAD_INPUT_2)) {
		new ReflectShot(ShotX, ShotY, 30, this->layer);
		new ReflectShot(ShotX, ShotY, -30, this->layer);
	}


}
