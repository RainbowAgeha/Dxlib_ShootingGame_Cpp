#pragma once
#include "GameObject.h"

//弾に関する初期設定
class Shot : public GameObject{
private:
    int ShotImg;
    float Speed;    //速度
    int parent;     //所有者
    float RectW, RectH;

public:
    Shot();
    Shot(float _posX, float _PosY, int _parent);
    Shot(float _posX, float _PosY, float _angle, int _parent);
    ~Shot();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class ReflectShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //速度
    int parent;     //所有者
    int ReflectCount;

public:
    ReflectShot(float _posX, float _PosY,float _angle, int _parent);
    ~ReflectShot();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

