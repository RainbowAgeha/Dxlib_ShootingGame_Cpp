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
    ReflectShot(float _posX, float _PosY,float _angle);
    ~ReflectShot();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class EShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //速度
    int parent;     //所有

public:
    EShot(float _posX, float _PosY, float _angle, int _parent);
    ~EShot();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class FallShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //速度
    int parent;     //所有者
    float fallSpeed;

public:
    FallShot(float _posX, float _PosY, float _angle);
    ~FallShot();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class HomingShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //速度
    int parent;     //所有者
    GameObject* target;

public:
    HomingShot(float _posX, float _PosY, float _angle);
    ~HomingShot();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class StrikeShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //速度
    int parent;     //所有者

public:
    StrikeShot(float _posX, float _PosY, float _angle);
    ~StrikeShot();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

