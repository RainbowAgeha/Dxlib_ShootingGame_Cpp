#pragma once
#include "GameObject.h"
class EffectStar :
    public GameObject
{
private:
    float Speed;    //���x
    int StarImg;
    float lifeTime;
public :
    EffectStar(float _posX, float _PosY, float _angle);
    ~EffectStar();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

