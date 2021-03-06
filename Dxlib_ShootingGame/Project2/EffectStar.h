#pragma once
#include "GameObject.h"
class EffectStar :
    public GameObject
{
private:
    float Speed;    //速度
    int StarImg;
    float lifeTime;
public :
    EffectStar(float _posX, float _PosY, float _angle);
    ~EffectStar();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

