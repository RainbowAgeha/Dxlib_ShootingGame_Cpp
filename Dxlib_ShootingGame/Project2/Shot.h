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
    ReflectShot(float _posX, float _PosY,float _angle);
    ~ReflectShot();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class EShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //���x
    int parent;     //���L

public:
    EShot(float _posX, float _PosY, float _angle, int _parent);
    ~EShot();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class FallShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //���x
    int parent;     //���L��
    float fallSpeed;

public:
    FallShot(float _posX, float _PosY, float _angle);
    ~FallShot();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class HomingShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //���x
    int parent;     //���L��
    GameObject* target;

public:
    HomingShot(float _posX, float _PosY, float _angle);
    ~HomingShot();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class StrikeShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //���x
    int parent;     //���L��

public:
    StrikeShot(float _posX, float _PosY, float _angle);
    ~StrikeShot();
    // GameObject ����Čp������܂���
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

