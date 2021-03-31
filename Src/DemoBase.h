#pragma once
#include "include/main.h"

class DemoBase{
public:
    struct{
        uint width;
        uint height;
    }m_size;
    GLFWwindow* m_window;
    DemoBase(uint width=800, uint height=600);
    
    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;

public:
    virtual int init();

    virtual int run();

    virtual void processInput();

    virtual void render();

    virtual void setWindowResizeCallBack(GLFWframebuffersizefun);

};