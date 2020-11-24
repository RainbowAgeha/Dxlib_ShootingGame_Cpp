#include "bomEffect.h"

bomEffect::bomEffect(VECTOR pos) : GameObject(EFFECT_LAYER)
{
	this->pos = pos;
	AnimCount = 0;
	AnimTime = 0;

	//‰æ‘œ“Ç‚Ýž‚Ý
	LoadDivGraph("res/bom.png",6,6,1,24,24, BomEffectImg, true);
}

bomEffect::~bomEffect()
{
}

void bomEffect::move()
{
	AnimTime++;
	if (AnimTime > 6) {
		AnimTime = 0;
		AnimCount++;
	}
	if (AnimCount > 6)isDead = true;
}

void bomEffect::render()
{
	DrawGraph(pos.x, pos.y, BomEffectImg[AnimCount], true);
}

void bomEffect::hit(GameObject* obj, int collideID)
{
}
