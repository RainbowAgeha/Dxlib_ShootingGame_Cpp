#pragma once
#include "GameObject.h"

class ZakoEnemy :
    public GameObject
{
private:
    //�ϐ��֌W
    int EnemyImg;

public:
    //�֐��֌W

    //�U�R�G���Ăяo���i�����Ȃ��j
    ZakoEnemy(float posX,float posY);
    ~ZakoEnemy();

    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

