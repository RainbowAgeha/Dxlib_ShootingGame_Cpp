#pragma once
#include "GameObject.h"
class EnemyShot :
    public GameObject
{
public:
    EnemyShot();
    ~EnemyShot();

    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

