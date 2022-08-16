
#include "Demo1.h"
#include <iostream>

static float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

static unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

static void resize_window(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

Demo1::Demo1(uint width, uint height):DemoBase(width,height){

    setWindowResizeCallBack(resize_window);

    vector<float> vecVert(vertices, vertices+sizeof(vertices)/sizeof(float));
    vector<uint> vecId(indices, indices+sizeof(indices)/sizeof(uint));

    m_rect.init("src/Demo1/vs.glsl", "src/Demo1/fs.glsl", vecVert, vecId);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
}

void Demo1::render(){
    DemoBase::render();
    m_rect.render();
    
    glBindVertexArray(m_rect.m_VAO);
    // 3. 绘制物体
    glDrawElements(GL_TRIANGLES, (GLsizei)m_rect.m_indices.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}