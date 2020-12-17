#pragma once
#include "GameObject.h"
class Enemy :
    public GameObject
{
private:
    int enemyImg;
    int BossPattern;     //移動パターン
    int speed;
    int AttackTime;     //色々使うよ攻撃タイム
    int SyncTime;       //色々使うよ考える時間

    int AttackAngle;

    int maxhp;

    enum {
        BossPattern_Init,       //入場シーン
        BossPattern_MoveUp,     //移動しながら攻撃
        BossPattern_MoveDown,
        BossPattern_Provision,  //反撃準備
        BossPattern_CounterAttack,   //反撃開始
        BossPattern_CAEnd,      //落ち着き
        BossPattern_Max
    };

public:
    Enemy(float _x,float _y,int id);
    ~Enemy();

    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

