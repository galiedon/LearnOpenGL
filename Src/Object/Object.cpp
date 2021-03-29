#include "Object.h"
#include <fstream>
using ifstream = std::ifstream;
using ios = std::ios;

Object::Object(){
}

Object::Object(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId):
m_vsPath(vsPath), 
m_fsPath(fsPath),
m_vertices(vecVert),
m_indices(vecId){
    init();
}

void Object::init(){
    m_vs = readFile(m_vsPath);
    m_fs = readFile(m_fsPath);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);

    auto vs = compileShader(GL_VERTEX_SHADER, m_vs, 1);
    auto fs = compileShader(GL_FRAGMENT_SHADER, m_fs, 1);
    m_shaderProgram = linkingProgram(vs, fs);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    float* vert = new float[m_vertices.size()];
    memcpy(vert, &m_vertices[0], sizeof(float) * m_vertices.size());
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), vert, GL_STATIC_DRAW);
    delete vert;

    uint* frag = new uint[m_indices.size()];
    memcpy(frag, &m_indices[0], sizeof(uint) * m_indices.size());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * m_indices.size(), frag, GL_STATIC_DRAW);
    delete frag;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
}

void Object::init(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId){
    m_vsPath = vsPath;
    m_fsPath = fsPath;
    m_vertices = vecVert;
    m_indices = vecId; 
    init();
}

string Object::readFile(string filePath){
    string result = "";
    char tmp[100] = {0};
    try{
        ifstream inFile(filePath);

        while(inFile.getline(tmp, 100)){
            result += tmp;
            result += '\n';
        }

        inFile.close();
    } catch (std::ifstream::failure e){
        std::cout << "读取文件失败" << std::endl; 
    }
    
    return result;
}

uint Object::compileShader(int shaderType, string shaderSource, uint shaderNum){
    uint shader = glCreateShader(shaderType);
    auto c_str = shaderSource.c_str();
    char infoLog[512];

    int success = 0;

    glShaderSource(shader, shaderNum, &c_str, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        switch (shaderType)
        {
        case GL_VERTEX_SHADER:
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return FAILED;

        case GL_FRAGMENT_SHADER:
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            return FAILED;

        default:
            break;
        }
    }

    return shader;
}

uint Object::linkingProgram(uint vs, uint fs){
    
    uint shaderProgram = glCreateProgram();
    int success = 0;
    char infoLog[512] = {0};

    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return shaderProgram;
}

void Object::render(){
    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_VAO);
    // 3. 绘制物体
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}