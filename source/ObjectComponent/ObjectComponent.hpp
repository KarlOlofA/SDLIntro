
#pragma once

#include <iostream>

class ObjectComponent{

public:

    ObjectComponent();
    ~ObjectComponent();

    virtual void Initialize();
    virtual void Destroy();

};