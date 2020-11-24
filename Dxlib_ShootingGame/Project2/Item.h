#pragma once
#include "GameObject.h"
class Item :
    public GameObject
{

private:
    int ItemImg;
    int DropSpeed;
public:
    Item(VECTOR pos);
    ~Item();
    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

