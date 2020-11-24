#pragma once
#include "GameObject.h"
class EffectStar :
    public GameObject
{
private:
    float Speed;    //ë¨ìx
    int StarImg;
    float lifeTime;
public :
    EffectStar(float _posX, float _PosY, float _angle);
    ~EffectStar();
    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

