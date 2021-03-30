#pragma once

#include "../DemoBase.h"
#include "../Object/Object.h"
using namespace glm;

class Demo5 : public DemoBase{

private:
    Object m_rect;
    uint m_texture[2];
    float m_alpha;
    mat4 m_trans;

    mat4 m_model;
    mat4 m_view;
    mat4 m_proj;

public:
    Demo5(uint width=800, uint height=600);
    void render();
    
    void processInput();

    uint generateTexture(string imgPath, uint filterType, uint repeatType);
};