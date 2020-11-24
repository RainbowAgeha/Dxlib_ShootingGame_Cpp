#pragma once
#include "GameObject.h"

class ZakoEnemy :
    public GameObject
{
private:
    //•Ï”ŠÖŒW
    int EnemyImg;

public:
    //ŠÖ”ŠÖŒW

    //ƒUƒR“G‚ğŒÄ‚Ño‚·iˆø”‚È‚µj
    ZakoEnemy(float posX,float posY);
    ~ZakoEnemy();

    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

