#pragma once
#include "GameObject.h"
class Item :
    public GameObject
{

private:
    int ItemImg;
    int DropSpeed;
    int UpSpeed;
public:
    Item(VECTOR pos);
    ~Item();
    // GameObject を介して継承されました
    virtual void move() override;
    virtual void render() override;
    virtual void hit(GameObject* obj, int collideID) override;
};

