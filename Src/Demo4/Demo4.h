#pragma once

#include "../DemoBase.h"
#include "../Object/Object.h"
using namespace glm;

class Demo4 : public DemoBase{

private:
    Object m_rect;
    uint m_texture[2];
    float m_alpha;
    mat4 m_trans;

public:
    Demo4(uint width=800, uint height=600);
    void render();
    
    void processInput();

    uint generateTexture(string imgPath, uint filterType, uint repeatType);
};