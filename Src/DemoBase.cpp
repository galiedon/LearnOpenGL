#include "DemoBase.h"
#include <iostream>

DemoBase::DemoBase(uint width, uint height){
    m_size.width = width; 
    m_size.height = height;
    init();
}

int DemoBase::init(){
    
    // init glfw
    glfwInit();
    // 设置GLFW信息
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建GLFW窗体
    m_window = glfwCreateWindow(m_size.width, m_size.height, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL){
        std::cout << "Failed to create GLFW m_window" << std::endl;
        glfwTerminate();

        return FAILED;
    }
    glfwMakeContextCurrent(m_window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to init GLAD" << std::endl;

        return FAILED;
    }

    // 初始化视角大小
    glViewport(0, 0, m_size.width, m_size.height);

    return SUCCESS;
}

int DemoBase::run(){
    while(!glfwWindowShouldClose(m_window)){
        processInput();

        render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glfwTerminate();

    return SUCCESS;
}

void DemoBase::processInput(){
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(m_window, true);
    }
}

void DemoBase::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DemoBase::setWindowResizeCallBack(GLFWframebuffersizefun func){
    glfwSetFramebufferSizeCallback(m_window, func);  
}
