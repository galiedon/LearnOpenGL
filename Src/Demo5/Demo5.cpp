#include "Demo5.h"
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

float cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


static void resize_window(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

Demo5::Demo5(uint width, uint height):DemoBase(width,height){

    setWindowResizeCallBack(resize_window);

    vector<float> vecVert(cube, cube+sizeof(cube)/sizeof(float));
    vector<uint> vecId(indices, indices+sizeof(indices)/sizeof(uint));

    m_rect.init("src/Demo5/vs.glsl", "src/Demo5/fs.glsl", vecVert, vecId);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);  // 1. 设置顶点属性指针
    
    m_texture[0] = generateTexture("Resources/Textures/wall.jpg", GL_NEAREST, GL_REPEAT);
    m_texture[1] = generateTexture("Resources/Textures/awesomeface.png", GL_NEAREST, GL_REPEAT);
    m_rect.shader.setInt("texSampler", 0);
    m_rect.shader.setInt("texSampler2", 1);
    m_alpha = 0.5f;
    
    // 模型矩阵
    m_model = mat4(1.0f);
    m_model = rotate(m_model, radians(-55.0f), vec3(1.0f, 0, 0));

    // 观察矩阵
    m_view = mat4(1.0f);
    m_view = translate(m_view, vec3(0, 0.0f, -5.0f));

    // 投影矩阵
    m_proj = mat4(1.0f);
    m_proj = perspective(radians(110.0f), (float)m_size.width/m_size.height, 0.1f, 100.0f);
}

void Demo5::render(){
    DemoBase::render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_rect.shader.setFloat("bias", sin((float)glfwGetTime()));
    m_rect.shader.setFloat("alpha", m_alpha);
    m_rect.shader.setMat4("view", GL_FALSE, m_view);
    m_rect.shader.setMat4("proj", GL_FALSE, m_proj);

    float timeValue = (float)glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(m_rect.shader.m_id, "outColor");
    glUniform4f(vertexColorLocation, greenValue, greenValue, greenValue, 1.0f);
    
    glActiveTexture(GL_TEXTURE0); //在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, m_texture[0]);
    glActiveTexture(GL_TEXTURE1); //在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, m_texture[1]);

    glEnable(GL_DEPTH_TEST);
    m_rect.render();
    glBindVertexArray(m_rect.m_VAO);
    
    for(uint i = 0; i < 10; ++i){
        
        auto model = translate(m_model, cubePositions[i]);
        float angle = 20.0f * i;
        model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
        model = rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));
        m_rect.shader.setMat4("model", GL_FALSE, model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
}

uint Demo5::generateTexture(string imgPath, uint filterType, uint repeatType){
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

void Demo5::processInput(){

    if(glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS){
        m_alpha = m_alpha >= 1? 1: m_alpha + 0.01f;
    }else if(glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS){
        m_alpha = m_alpha <= 0? 0: m_alpha - 0.01f;
    }

    DemoBase::processInput();
}