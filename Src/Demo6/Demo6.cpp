#include "Demo6.h"
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

static float cube[] = {
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

static vec3 cubePositions[] = {
    vec3( 0.0f,  0.0f,  0.0f), 
    vec3( 2.0f,  5.0f, -15.0f), 
    vec3(-1.5f, -2.2f, -2.5f),  
    vec3(-3.8f, -2.0f, -12.3f),  
    vec3( 2.4f, -0.4f, -3.5f),  
    vec3(-1.7f,  3.0f, -7.5f),  
    vec3( 1.3f, -2.0f, -2.5f),  
    vec3( 1.5f,  2.0f, -2.5f), 
    vec3( 1.5f,  0.2f, -1.5f), 
    vec3(-1.3f,  1.0f, -1.5f)  
};

static float lastX = 400, lastY = 300;
static float g_yaw = 0, g_pitch = 0, g_roll = 0;
static bool firstMouse = true;

static float fov = 45.0f;
Camera* g_camera;

static void resize_window(GLFWwindow* window, int width, int height){
    lastX = width / 2.0f;
    lastY = height / 2.0f;
    glViewport(0, 0, width, height);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    
    if(firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
        return;
    }
    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    lastX = (float)xpos;
    lastY = (float)ypos;

    g_camera->processMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_camera->processMouseScroll(yoffset);
}


Demo6::Demo6(uint width, uint height):DemoBase(width,height){
    // 设置窗体回调函数
    setWindowResizeCallBack(resize_window);

    // 初始化顶点
    vector<float> vecVert(cube, cube+sizeof(cube)/sizeof(float));
    vector<uint> vecId(indices, indices+sizeof(indices)/sizeof(uint));
    m_rect.init("src/Demo6/vs.glsl", "src/Demo6/fs.glsl", vecVert, vecId);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);  // 1. 设置顶点属性指针
    
    m_texture[0] = generateTexture("Resources/Textures/wall.jpg", GL_LINEAR, GL_REPEAT);
    m_texture[1] = generateTexture("Resources/Textures/awesomeface.png", GL_LINEAR, GL_REPEAT);
    m_rect.shader.setInt("texSampler", 0);
    m_rect.shader.setInt("texSampler2", 1);
    m_alpha = 0.5f;
    
    // 模型矩阵
    m_model = mat4(1.0f);
    m_model = rotate(m_model, radians(-55.0f), vec3(1.0f, 0, 0));

    // 投影矩阵
    m_proj = perspective(radians(fov), (float)m_size.width/m_size.height, 0.1f, 100.0f);

    g_camera = &m_camera;

    // 隐藏鼠标
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // 监听鼠标事件
    // 原型void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    glfwSetCursorPosCallback(m_window, mouse_callback);

    // 监听鼠标滚轮事件
    glfwSetScrollCallback(m_window, scroll_callback);

}

void Demo6::render(){
    DemoBase::render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_rect.shader.setFloat("bias", sin((float)glfwGetTime()));
    m_rect.shader.setFloat("alpha", m_alpha);

    m_rect.shader.setMat4("view", GL_FALSE, m_camera.getViewMatrix());
    m_proj = perspective(radians(fov), (float)m_size.width/m_size.height, 0.1f, 100.0f);
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

uint Demo6::generateTexture(string imgPath, uint filterType, uint repeatType){
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

void Demo6::processInput(){

    if(glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS){
        m_alpha = m_alpha >= 1? 1: m_alpha + 0.01f;
    }
    if(glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS){
        m_alpha = m_alpha <= 0? 0: m_alpha - 0.01f;
    }

    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
        m_camera.processKeyboard(FORWARD, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
        m_camera.processKeyboard(BACKWARD, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
        m_camera.processKeyboard(LEFT, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
        m_camera.processKeyboard(RIGHT, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_TAB) == GLFW_PRESS){
        tabIsPress = true;
    }
    if(glfwGetKey(m_window, GLFW_KEY_TAB) == GLFW_RELEASE){
        if(tabIsPress){
            switch (m_camera.m_type)
            {
            case LOCK_TARGET: m_camera.setCameraType(FREE_MOVE); break;

            case FREE_MOVE: m_camera.setCameraType(LOCK_TARGET); break;
            
            default:
                break;
            }
            tabIsPress = false;
        }
    }
    DemoBase::processInput();
}
