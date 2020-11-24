#pragma once
#include "GameObject.h"

extern int Input, EdgeInput;

class Player : public GameObject
{
private:

	float x, y, z;
	float ShotX, ShotY;
	int playerImg;
	float RectW, RectH;

	int score;
public:
	Player();
	~Player();
	
	virtual void move() override;
	virtual void render() override;
	virtual void hit(GameObject* obj, int collideID) override;

	void PlayerInit();

	void PlayerMove();
	void PlayerAttack();
};

