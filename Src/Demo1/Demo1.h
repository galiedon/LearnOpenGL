#pragma once

#include "../DemoBase.h"
#include "../Object/Object.h"

class Demo1 : public DemoBase{

private:
    Object m_rect;

public:
    Demo1(uint width=800, uint height=600);
    void render();
};