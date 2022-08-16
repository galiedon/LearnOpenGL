#pragma once
#include "../include/main.h"
#include "../Shader/Shader.h"

class Object{

public:

    uint m_VBO;
    uint m_IBO;
    uint m_VAO;

    vector<float> m_vertices;
    vector<uint> m_indices;
    Shader shader;
    mat4 m_model;
    
    Object();
    
    Object(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId);
    
    virtual void init();
    void init(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId);

    virtual void render();

};