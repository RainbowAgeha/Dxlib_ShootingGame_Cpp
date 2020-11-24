#pragma once
#include "GameObject.h"

//’e‚ÉŠÖ‚·‚é‰Šúİ’è
class Shot : public GameObject{
private:
    int ShotImg;
    float Speed;    //‘¬“x
    int parent;     //Š—LÒ
    float RectW, RectH;

public:
    Shot();
    Shot(float _posX, float _PosY, int _parent);
    Shot(float _posX, float _PosY, float _angle, int _parent);
    ~Shot();
    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

class ReflectShot : public GameObject {
private:
    int ShotImg;
    float Speed;    //‘¬“x
    int parent;     //Š—LÒ
    int ReflectCount;

public:
    ReflectShot(float _posX, float _PosY,float _angle, int _parent);
    ~ReflectShot();
    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

