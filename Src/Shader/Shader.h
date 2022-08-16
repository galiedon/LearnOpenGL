#pragma once
#include "../include/main.h"
using namespace glm;

class Shader{

public:
    uint m_id;
    string m_vsPath;
    string m_fsPath;

    Shader(string vsPath, string fsPath);
    Shader();
    void init();
    void init(string vsPath, string fsPath);

    void use();
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    void setMat4(const string &name, uint columnMajorOrder, mat4 value) const;
    void setVec3(const string &name, vec3 value) const;

    string readFile(string filePath);

    uint compileShader(int shaderType, string shaderSource, uint shaderNum);

    uint linkingProgram(uint vs, uint fs);

};