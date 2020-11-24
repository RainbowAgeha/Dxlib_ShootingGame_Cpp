#pragma once
#include "GameObject.h"
class EnemyShot :
    public GameObject
{
public:
    EnemyShot();
    ~EnemyShot();

    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

