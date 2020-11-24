#pragma once
#include "GameObject.h"

//�e�Ɋւ��鏉���ݒ�
class Shot : public GameObject{
private:
    int ShotImg;
    float Speed;    //���x
    int parent;     //���L��
    float RectW, RectH;

public:
    Shot();
    Shot(float _posX, float _PosY, int _parent);
    Shot(float _posX, float _PosY, float _angle, int _parent);
    ~Shot();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class ReflectShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //���x
    int parent;     //���L��
    int ReflectCount;

public:
    ReflectShot(float _posX, float _PosY,float _angle, int _parent);
    ~ReflectShot();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

