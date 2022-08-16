#pragma once

#include "../DemoBase.h"
#include "../Object/Object.h"
#include "../Camera/Camera.h"
using namespace glm;

class Demo7 : public DemoBase{

private:
    Object m_rect;

    Object m_lightCube;

    mat4 m_trans;

    mat4 m_proj;

    Camera m_camera;
    
    vec3 m_lightColor;
    vec3 m_cubeColor;


    bool tabIsPress = false; 

public:
    Demo7(uint width=800, uint height=600);
    void render();
    
    void processInput();

    uint generateTexture(string imgPath, uint filterType, uint repeatType);
};