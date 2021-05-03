#pragma once

#include "../DemoBase.h"
#include "../Object/Object.h"
#include "../Camera/Camera.h"
#include "../Object/Model.h"
using namespace glm;

class Demo13 : public DemoBase{

private:
    Object m_rect;

    Object m_lightCube;

    mat4 m_trans;

    mat4 m_proj;

    Camera m_camera;
    

    vec3 m_lightColor;
    vec3 m_cubeColor;

    vec3 m_lightPos;

    uint m_diffuseTexture;
    uint m_specularTexture;
    uint m_emissiveTexture;
    uint m_spotLightTexture;

    Model m_nanosuit;
    Shader m_shader;
    uint m_depth_mode;


    bool tabIsPress = false; 
    bool numIsPress[10] = {false}; 

public:
    Demo13(uint width=800, uint height=600);
    void render();
    
    void processInput();

    uint generateTexture(string imgPath, uint filterType, uint repeatType);

private:
    void dirLightingRenderTest();
    void pointLightingRenderTest();
    void spotLightingRenderTest();
    void mixLightingRenderTest();
    void drawCubes();
    void drawLightCube();
    
};