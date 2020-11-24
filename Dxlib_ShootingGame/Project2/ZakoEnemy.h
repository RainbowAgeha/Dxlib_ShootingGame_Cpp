#pragma once
#include "GameObject.h"

class ZakoEnemy :
    public GameObject
{
private:
    //変数関係
    int EnemyImg;

public:
    //関数関係

    //ザコ敵を呼び出す（引数なし）
    ZakoEnemy(float posX,float posY);
    ~ZakoEnemy();

    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

