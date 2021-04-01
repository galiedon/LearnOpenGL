#include "Demo10.h"
#include <iostream>
#include "SOIL/SOIL.h"

static unsigned int indices[] = { // 注意索引从0开始!  
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

static float cube[] = {    
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

static float lastX = 400, lastY = 300;
static float g_yaw = 0, g_pitch = 0, g_roll = 0;
static bool firstMouse = true;

static float fov = 45.0f;
static Camera* g_camera;

// #define DEBUG
#ifndef DEBUG
    static const char* const cube_vs = "src/Demo10/cube.vs";
    static const char* const cube_fs = "src/Demo10/cube.fs";
    static const char* const light_vs = "src/Demo10/light.vs";
    static const char* const light_fs = "src/Demo10/light.fs";
    static const char* const cube_diffuse = "Resources/Textures/container2.png";
    static const char* const cube_specular = "Resources/Textures/lighting_maps_specular_color.png";
    static const char* const cube_emissive = "Resources/Textures/matrix.jpg";
#else
    static const char* const cube_vs = "../src/Demo10/cube.vs";
    static const char* const cube_fs = "../src/Demo10/cube.fs";
    static const char* const light_vs = "../src/Demo10/light.vs";
    static const char* const light_fs = "../src/Demo10/light.fs";
    static const char* const cube_diffuse = "../Resources/Textures/container2.png";
    static const char* const cube_specular = "../Resources/Textures/container2_specular.png";
    static const char* const cube_emissive = "../Resources/Textures/matrix.jpg";
#endif

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

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_camera->processMouseScroll((float)yoffset);
}


Demo10::Demo10(uint width, uint height):DemoBase(width,height){
    // 设置窗体回调函数
    setWindowResizeCallBack(resize_window);

    // 初始化顶点
    vector<float> vecVert(cube, cube+sizeof(cube)/sizeof(float));
    vector<uint> vecId(indices, indices+sizeof(indices)/sizeof(uint));
    m_rect.init(cube_vs, cube_fs, vecVert, vecId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  // 1. 设置顶点属性指针
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  // 1. 设置顶点属性指针

    m_diffuseTexture = generateTexture(cube_diffuse, GL_LINEAR, GL_REPEAT);
    m_specularTexture = generateTexture(cube_specular, GL_LINEAR, GL_REPEAT);
    m_emissiveTexture = generateTexture(cube_emissive, GL_LINEAR, GL_REPEAT);
    m_rect.shader.setInt("material.diffuse", 0);
    m_rect.shader.setInt("material.specular", 1);
    m_rect.shader.setInt("material.emissive", 2);

    m_lightCube.init(light_vs, light_fs, vecVert, vecId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
    
    // 模型矩阵
    m_rect.m_model = rotate(m_rect.m_model, radians(-55.0f), vec3(1.0f, 0, 0));

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

    // 设置颜色
    m_lightColor = vec3(1, 1, 1);
    m_cubeColor = vec3(1, 0.5, 0.3);

    // 移动物体
    m_lightPos = vec3(1, 0, 0);
    m_lightCube.m_model = translate(m_lightCube.m_model, m_lightPos);
    m_lightCube.m_model = scale(m_lightCube.m_model, vec3(0.2f));
    m_camera.processKeyboard(BACKWARD, 2);

}

void Demo10::render(){
    DemoBase::render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    m_rect.render();
    
    // 设置MVP矩阵与uniform 参数
    m_rect.shader.setMat4("view", GL_FALSE, m_camera.getViewMatrix());
    m_proj = perspective(radians(m_camera.m_zoom), (float)m_size.width/m_size.height, 0.1f, 100.0f);
    m_rect.shader.setMat4("proj", GL_FALSE, m_proj);
    
    // 设置贴图
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_specularTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_emissiveTexture);

    glBindVertexArray(m_rect.m_VAO);
    auto model = rotate(m_rect.m_model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));
    // auto model = m_rect.m_model;
    m_rect.shader.setVec3("lightColor", m_lightColor);
    m_rect.shader.setVec3("objectColor", m_cubeColor);
    m_rect.shader.setVec3("light.lightPos", m_lightPos);
    m_rect.shader.setVec3("viewPos", m_camera.m_position);
    m_rect.shader.setMat4("model", GL_FALSE, model);

    m_rect.shader.setFloat("material.shininess", 32.0f);
    vec3 lightColor;
    lightColor.x = (float)sin(glfwGetTime() * 2.0f);
    lightColor.y = (float)sin(glfwGetTime() * 0.7f);
    lightColor.z = (float)sin(glfwGetTime() * 1.3f);

    vec3 diffuseColor = lightColor   * vec3(0.5f); // 降低影响
    vec3 ambientColor = diffuseColor * vec3(0.2f); // 很低的影响
    m_rect.shader.setVec3("light.ambient",  ambientColor);
    m_rect.shader.setVec3("light.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
    m_rect.shader.setVec3("light.specular", vec3(1.0f, 1.0f, 1.0f)); 

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    m_lightCube.render();
    m_lightCube.shader.setMat4("view", GL_FALSE, m_camera.getViewMatrix());
    m_proj = perspective(radians(m_camera.m_zoom), (float)m_size.width/m_size.height, 0.1f, 100.0f);
    m_lightCube.shader.setMat4("proj", GL_FALSE, m_proj);
    glBindVertexArray(m_lightCube.m_VAO);
    
    m_lightCube.shader.setMat4("model", GL_FALSE, m_lightCube.m_model);
    m_lightCube.shader.setVec3("lightColor", m_lightColor);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
}

uint Demo10::generateTexture(string imgPath, uint filterType, uint repeatType){
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
    //glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

void Demo10::processInput(){

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
