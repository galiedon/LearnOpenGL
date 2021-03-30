#include "Demo2.h"
#include <iostream>

static float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

static unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 2, // 第一个三角形
};

static void resize_window(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

Demo2::Demo2(uint width, uint height):DemoBase(width,height){

    setWindowResizeCallBack(resize_window);

    vector<float> vecVert(vertices, vertices+sizeof(vertices)/sizeof(float));
    vector<uint> vecId(indices, indices+sizeof(indices)/sizeof(uint));

    m_rect.init("src/Demo2/vs.glsl", "src/Demo2/fs.glsl", vecVert, vecId);
}

void Demo2::render(){
    DemoBase::render();
    m_rect.shader.setFloat("bias", sin((float)glfwGetTime()));

    float timeValue = (float)glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(m_rect.shader.m_id, "outColor");
    glUniform4f(vertexColorLocation, greenValue, greenValue, greenValue, 1.0f);
    m_rect.render();
}