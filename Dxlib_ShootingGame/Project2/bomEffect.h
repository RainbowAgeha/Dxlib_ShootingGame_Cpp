#pragma once
#include "GameObject.h"

#define BomImgNum 6

class bomEffect :
    public GameObject
{
private:
    int BomEffectImg[BomImgNum];
    int AnimCount,AnimTime;

public:
    bomEffect(VECTOR pos);
    ~bomEffect();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

