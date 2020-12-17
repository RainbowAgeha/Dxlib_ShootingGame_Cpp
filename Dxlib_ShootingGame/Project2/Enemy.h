#pragma once
#include "GameObject.h"
class Enemy :
    public GameObject
{
private:
    int enemyImg;
    int BossPattern;     //�ړ��p�^�[��
    int speed;
    int AttackTime;     //�F�X�g����U���^�C��
    int SyncTime;       //�F�X�g����l���鎞��

    int AttackAngle;

    int maxhp;

    enum {
        BossPattern_Init,       //����V�[��
        BossPattern_MoveUp,     //�ړ����Ȃ���U��
        BossPattern_MoveDown,
        BossPattern_Provision,  //��������
        BossPattern_CounterAttack,   //�����J�n
        BossPattern_CAEnd,      //��������
        BossPattern_Max
    };

public:
    Enemy(float _x,float _y,int id);
    ~Enemy();

    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

