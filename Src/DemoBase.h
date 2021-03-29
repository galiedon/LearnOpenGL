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

public:
    virtual int init();

    virtual int run();

    virtual void processInput();

    virtual void render();

    virtual void setWindowResizeCallBack(GLFWframebuffersizefun);

};