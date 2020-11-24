#pragma once
#include "GameObject.h"
class EnemyShot :
    public GameObject
{
public:
    EnemyShot();
    ~EnemyShot();

    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

