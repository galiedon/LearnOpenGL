#include "Demo4.h"
#include <iostream>
#include "SOIL/SOIL.h"


static float vertices[] = {
    // positions         // colors
    0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // bottom right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0, // bottom left
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0, 0,  // top 
    -0.5f, 0.5f, 0.0f,   1.f, 1.f, 1.f,     0, 1.0f// top 
};

static unsigned int indices[] = { // 注意索引从0开始!  
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

static void resize_window(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

Demo4::Demo4(uint width, uint height):DemoBase(width,height){

    setWindowResizeCallBack(resize_window);

    vector<float> vecVert(vertices, vertices+sizeof(vertices)/sizeof(float));
    vector<uint> vecId(indices, indices+sizeof(indices)/sizeof(uint));

    m_rect.init("src/Demo4/vs.glsl", "src/Demo4/fs.glsl", vecVert, vecId);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);  // 1. 设置顶点属性指针
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);  // 1. 设置顶点属性指针
    
    m_texture[0] = generateTexture("Resources/Textures/wall.jpg", GL_NEAREST, GL_REPEAT);
    m_texture[1] = generateTexture("Resources/Textures/awesomeface.png", GL_NEAREST, GL_REPEAT);
    m_rect.shader.setInt("texSampler", 0);
    m_rect.shader.setInt("texSampler2", 1);
    m_alpha = 0.5f;
    
    m_trans = mat4(1.0f);
    m_trans = rotate(m_trans, radians(90.0f), vec3(0, 0, 1));
    m_trans = scale(m_trans, vec3(0.5, 0.5, 0.5));
}

void Demo4::render(){
    DemoBase::render();
    m_rect.shader.setFloat("bias", sin((float)glfwGetTime()));
    m_rect.shader.setFloat("alpha", m_alpha);
    mat4 trans(1.0f);
    trans = rotate(trans, (float)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
    trans = translate(trans, vec3(0.5f, -0.5f, 0.0f));
    m_rect.shader.setMat4("trans", GL_FALSE, trans);

    float timeValue = (float)glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(m_rect.shader.m_id, "outColor");
    glUniform4f(vertexColorLocation, greenValue, greenValue, greenValue, 1.0f);
    
    glActiveTexture(GL_TEXTURE0); //在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, m_texture[0]);
    glActiveTexture(GL_TEXTURE1); //在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, m_texture[1]);

    m_rect.render();
    glBindVertexArray(m_rect.m_VAO);
    // 3. 绘制物体
    glDrawElements(GL_TRIANGLES, (GLsizei)m_rect.m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

uint Demo4::generateTexture(string imgPath, uint filterType, uint repeatType){
    int width, height;
    uint tex;
    // 加载图片
    uchar* image = SOIL_load_image(imgPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    if(!image){
        std::cout << "Failed to load Image!" << std::endl;
        return FAILED;
    }

    // 获取Texture ID
    glGenTextures(1, &tex);
    // 绑定Texture
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatType);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);

    // 生成Texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // 生成Mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    // 释放图片与TextureID
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

void Demo4::processInput(){

    if(glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS){
        m_alpha = m_alpha >= 1? 1: m_alpha + 0.01f;
    }else if(glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS){
        m_alpha = m_alpha <= 0? 0: m_alpha - 0.01f;
    }

    DemoBase::processInput();
}