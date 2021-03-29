#pragma once
#include "../include/main.h"
#include <iostream>

class Object{

public:

    uint m_VBO;
    uint m_IBO;
    uint m_VAO;
    uint m_shaderProgram;

    string m_vsPath;
    string m_fsPath;

    string m_vs;
    string m_fs;

    vector<float> m_vertices;
    vector<uint> m_indices;
    
    Object();
    
    Object(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId);
    
    void init();
    void init(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId);

    string readFile(string filePath);

    virtual uint compileShader(int shaderType, string shaderSource, uint shaderNum);

    virtual uint linkingProgram(uint vs, uint fs);

    virtual void render();

};