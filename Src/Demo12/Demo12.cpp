#include "Demo12.h"
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

static vec3 lightBias[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

static float lastX = 400, lastY = 300;
static float g_yaw = 0, g_pitch = 0, g_roll = 0;
static bool firstMouse = true;

static float fov = 45.0f;
static Camera* g_camera;

typedef enum{
    DIRECTION_LIGHTING_TEST = 1,
    POINT_LIGHTING_TEST,
    SPOT_LIGHTING_TEST,
    MIX_LIGHTING_TEST
}LightTestId;
static LightTestId lightTestId = MIX_LIGHTING_TEST;

// #define DEBUG
#ifndef DEBUG
    static const char* const cube_vs = "src/Demo12/cube.vs";
    static const char* const cube_fs = "src/Demo12/cube.fs";
    static const char* const light_vs = "src/Demo12/light.vs";
    static const char* const light_fs = "src/Demo12/light.fs";
    static const char* const cube_diffuse = "Resources/Textures/container2.png";
    static const char* const cube_specular = "Resources/Textures/lighting_maps_specular_color.png";
    static const char* const cube_emissive = "Resources/Textures/matrix.jpg";
    static const char* const flashLightTexture = "Resources/Textures/hahachan017-cc.jpg";
    static const char* const nanosuitModelPath = "Resources/Models/nanosuit/nanosuit.obj";
    static const char* const nanosuit_vs = "src/Demo12/nanosuit.vs";
    static const char* const nanosuit_fs = "src/Demo12/nanosuit.fs";
#else
    static const char* const cube_vs = "../src/Demo12/cube.vs";
    static const char* const cube_fs = "../src/Demo12/cube.fs";
    static const char* const light_vs = "../src/Demo12/light.vs";
    static const char* const light_fs = "../src/Demo12/light.fs";
    static const char* const cube_diffuse = "../Resources/Textures/container2.png";
    static const char* const cube_specular = "../Resources/Textures/container2_specular.png";
    static const char* const cube_emissive = "../Resources/Textures/matrix.jpg";
    static const char* const flashLightTexture = "Resources/Textures/hahachan017-cc.jpg";
    static const char* const nanosuitModelPath = "../Resources/Models/nanosuit/nanosuit.obj";
    static const char* const nanosuit_vs = "../src/Demo12/nanosuit.vs";
    static const char* const nanosuit_fs = "../src/Demo12/nanosuit.fs";
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


Demo12::Demo12(uint width, uint height):DemoBase(width,height){
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
    m_spotLightTexture = generateTexture(flashLightTexture, GL_LINEAR, GL_REPEAT);
    m_rect.shader.setInt("material.diffuse", 0);
    m_rect.shader.setInt("material.specular", 1);
    m_rect.shader.setInt("material.emissive", 2);
    m_rect.shader.setInt("spotLight.color", 3);

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

    // 设置模型
    m_nanosuit.loadModel(nanosuitModelPath);
    m_shader.init(cube_vs, cube_fs);

}

void Demo12::render(){
    DemoBase::render();
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    switch (lightTestId)
    {
    case DIRECTION_LIGHTING_TEST: dirLightingRenderTest(); break;
    case POINT_LIGHTING_TEST: pointLightingRenderTest(); break;
    case SPOT_LIGHTING_TEST: spotLightingRenderTest(); break;
    case MIX_LIGHTING_TEST: mixLightingRenderTest(); break;
    
    default:
        break;
    }
    
}

uint Demo12::generateTexture(string imgPath, uint filterType, uint repeatType){
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

void Demo12::processInput(){

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
    if(glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
        m_camera.processKeyboard(UP, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){
        m_camera.processKeyboard(DOWN, m_deltaTime);
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

void Demo12::dirLightingRenderTest(){
    
    m_rect.render();
    vec3 lightColor(1);

    vec3 diffuseColor = lightColor   * vec3(0.5f); // 降低影响
    vec3 ambientColor = diffuseColor * vec3(0.2f); // 很低的影响
    m_rect.shader.setVec3("dirLight.direction",  vec3(-0.2f, -1.0f, -0.3f));
    m_rect.shader.setVec3("dirLight.model.ambient",  ambientColor);
    m_rect.shader.setVec3("dirLight.model.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
    m_rect.shader.setVec3("dirLight.model.specular", vec3(1.0f, 1.0f, 1.0f)); 
    m_rect.shader.setVec3("dirLight.model.color", m_lightColor);
    m_rect.shader.setInt("renderTestId", lightTestId);
    
    drawCubes();
    glBindVertexArray(0);
}

void Demo12::pointLightingRenderTest(){
    
    m_rect.render();
    vec3 lightColor(1);

    vec3 diffuseColor = lightColor   * vec3(0.5f); // 降低影响
    vec3 ambientColor = diffuseColor * vec3(0.2f); // 很低的影响
    float constant = 1.f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    m_rect.shader.setVec3("pointLight.pos",  m_lightPos);
    m_rect.shader.setVec3("pointLight.model.ambient",  ambientColor);
    m_rect.shader.setVec3("pointLight.model.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
    m_rect.shader.setVec3("pointLight.model.specular", vec3(1.0f, 1.0f, 1.0f)); 
    m_rect.shader.setVec3("pointLight.model.color", m_lightColor);
    m_rect.shader.setFloat("pointLight.constant",  constant);
    m_rect.shader.setFloat("pointLight.linear",  linear);
    m_rect.shader.setFloat("pointLight.quadratic",  quadratic);
    m_rect.shader.setInt("renderTestId", lightTestId);
    
    drawCubes();
    glBindVertexArray(0);

    
    m_lightCube.render();
    drawLightCube();
    glBindVertexArray(0);
}

void Demo12::spotLightingRenderTest(){
    m_rect.render();
    vec3 lightColor(1);

    vec3 diffuseColor = lightColor   * vec3(0.5f); // 降低影响
    vec3 ambientColor = diffuseColor * vec3(0.2f); // 很低的影响
    float cutOff = 12.5f;
    float outerCutOff = 17.5f;
    m_rect.shader.setVec3("spotLight.pos",  m_camera.m_position);
    m_rect.shader.setVec3("spotLight.direction",  m_camera.m_front);
    m_rect.shader.setVec3("spotLight.model.ambient",  ambientColor);
    m_rect.shader.setVec3("spotLight.model.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
    m_rect.shader.setVec3("spotLight.model.specular", vec3(1.0f, 1.0f, 1.0f)); 
    m_rect.shader.setFloat("spotLight.cutOff",  cos(radians(cutOff)));
    m_rect.shader.setFloat("spotLight.outerCutOff",  cos(radians(outerCutOff)));
    m_rect.shader.setInt("renderTestId", lightTestId);
    
    drawCubes();
    glBindVertexArray(0);
    
    // m_lightCube.render();
    // drawLightCube();
    // glBindVertexArray(0);
}

void Demo12::mixLightingRenderTest(){
    m_rect.render();
    vec3 lightColor(1);

    vec3 diffuseColor = lightColor * vec3(0.4f); // 降低影响
    vec3 ambientColor = lightColor * vec3(0.05f); // 很低的影响
    vec3 specularColor = lightColor * vec3(0.5f); // 很低的影响
    
    // 设置平行光
    m_rect.shader.setVec3("dirLight.direction",  vec3(-0.2f, -1.0f, -0.3f));
    m_rect.shader.setVec3("dirLight.model.ambient",  ambientColor);
    m_rect.shader.setVec3("dirLight.model.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
    m_rect.shader.setVec3("dirLight.model.specular", specularColor); 
    m_rect.shader.setVec3("dirLight.model.color", m_lightColor);

    diffuseColor = lightColor * vec3(1); // 降低影响
    ambientColor = lightColor * vec3(0); // 很低的影响
    specularColor = lightColor * vec3(1); // 很低的影响
    // 设置聚光
    float cutOff = 12.5f;
    float outerCutOff = 15.0f;
    float constant = 1.f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    m_rect.shader.setVec3("spotLight.pos", m_camera.m_position);
    m_rect.shader.setVec3("spotLight.direction", m_camera.m_front);
    m_rect.shader.setVec3("spotLight.model.ambient", ambientColor);
    m_rect.shader.setVec3("spotLight.model.diffuse", diffuseColor); // 将光照调暗了一些以搭配场景
    m_rect.shader.setVec3("spotLight.model.specular", vec3(1.0f, 1.0f, 1.0f)); 
    m_rect.shader.setFloat("spotLight.cutOff", cos(radians(cutOff)));
    m_rect.shader.setFloat("spotLight.outerCutOff", cos(radians(outerCutOff)));
    m_rect.shader.setFloat("spotLight.constant",  constant);
    m_rect.shader.setFloat("spotLight.linear", linear);
    m_rect.shader.setFloat("spotLight.quadratic", quadratic);
    m_rect.shader.setInt("renderTestId", lightTestId);
    
    // 设置点光
    diffuseColor = lightColor * vec3(0.8f); // 降低影响
    ambientColor = lightColor * vec3(0.05f); // 很低的影响
    specularColor = lightColor * vec3(1); // 很低的影响
    for(int i = 0; i < 4; ++i){
        string tmp = "pointLights[";
        tmp += std::to_string(i);
        tmp += "]";

        m_rect.shader.setVec3((tmp+".pos").c_str(),  m_lightPos + lightBias[i]);
        m_rect.shader.setVec3((tmp+".model.ambient").c_str(),  ambientColor);
        m_rect.shader.setVec3((tmp+".model.diffuse").c_str(),  diffuseColor);
        m_rect.shader.setVec3((tmp+".model.specular").c_str(),  vec3(1.0f, 1.0f, 1.0f));
        m_rect.shader.setFloat((tmp+".constant").c_str(),  constant);
        m_rect.shader.setFloat((tmp+".linear").c_str(),  linear);
        m_rect.shader.setFloat((tmp+".quadratic").c_str(),  quadratic);
    }

    drawCubes();
    glBindVertexArray(0);
    
    m_lightCube.render();
    // drawLightCube();
    m_lightCube.shader.setMat4("view", GL_FALSE, m_camera.getViewMatrix());
    m_proj = perspective(radians(m_camera.m_zoom), (float)m_size.width/m_size.height, 0.1f, 100.0f);
    m_lightCube.shader.setMat4("proj", GL_FALSE, m_proj);
    glBindVertexArray(m_lightCube.m_VAO);
    for(uint i = 0; i < 4; ++i){
        auto model = scale(m_lightCube.m_model, vec3(5));
        model = translate(model, -m_lightPos);
        model = translate(model, lightBias[i]);
        model = scale(model, vec3(0.2f));
        m_lightCube.shader.setMat4("model", GL_FALSE, model);
        m_lightCube.shader.setVec3("lightColor", m_lightColor);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
    
    // 设置MVP矩阵与uniform 参数
    m_rect.shader.use();
    m_rect.shader.setMat4("model", GL_FALSE, scale(mat4(1), vec3(0.2f)));
    m_nanosuit.Render(m_rect.shader);
}
void Demo12::drawCubes(){
    
    // 设置MVP矩阵与uniform 参数
    m_rect.shader.setMat4("view", GL_FALSE, m_camera.getViewMatrix());
    m_proj = perspective(radians(m_camera.m_zoom), (float)m_size.width/m_size.height, 0.1f, 100.0f);
    m_rect.shader.setMat4("proj", GL_FALSE, m_proj);
    m_rect.shader.setVec3("viewPos", m_camera.m_position);

    // 设置材质
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_specularTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_emissiveTexture);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_spotLightTexture);
    m_rect.shader.setFloat("material.shininess", 32.0f);

    glBindVertexArray(m_rect.m_VAO);
    for(uint i = 0; i < 10; ++i){
        auto model = translate(m_rect.m_model, cubePositions[i]);
        float angle = 20.0f * i;
        model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
        model = rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));
        m_rect.shader.setMat4("model", GL_FALSE, model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Demo12::drawLightCube(){
    
    m_lightCube.shader.setMat4("view", GL_FALSE, m_camera.getViewMatrix());
    m_proj = perspective(radians(m_camera.m_zoom), (float)m_size.width/m_size.height, 0.1f, 100.0f);
    m_lightCube.shader.setMat4("proj", GL_FALSE, m_proj);
    glBindVertexArray(m_lightCube.m_VAO);
    
    m_lightCube.shader.setMat4("model", GL_FALSE, m_lightCube.m_model);
    m_lightCube.shader.setVec3("lightColor", m_lightColor);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
