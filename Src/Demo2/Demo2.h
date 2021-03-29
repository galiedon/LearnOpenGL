#pragma once

#include "../DemoBase.h"

class Demo2 : public DemoBase{

public:
    Demo2(uint width=800, uint height=600);
    void render();
};