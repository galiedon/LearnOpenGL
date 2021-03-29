
#include "Demo1.h"
#include <iostream>

float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

void resize_window(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

Demo1::Demo1(uint width, uint height):DemoBase(width,height){

    setWindowResizeCallBack(resize_window);

    vector<float> vecVert(vertices, vertices+sizeof(vertices)/sizeof(float));
    vector<uint> vecId(indices, indices+sizeof(indices)/sizeof(uint));

    m_rect.init("Shader/Demo1/vs.glsl", "Shader/Demo1/fs.glsl", vecVert, vecId);
}

void Demo1::render(){
    DemoBase::render();
    m_rect.render();
}