#include "Shader.h"
#include <fstream>
using ifstream = std::ifstream;
using ios = std::ios;


Shader::Shader(){}

Shader::Shader(string vsPath, string fsPath) : m_vsPath(vsPath), m_fsPath(fsPath){
    init();
}


void Shader::init(){
    auto vsCode = readFile(m_vsPath);
    auto fsCode = readFile(m_fsPath);

    auto vsId = compileShader(GL_VERTEX_SHADER, vsCode, 1);
    auto fsId = compileShader(GL_FRAGMENT_SHADER, fsCode, 1);
    m_id = linkingProgram(vsId, fsId);
}

void Shader::init(string vsPath, string fsPath){
    m_vsPath = vsPath;
    m_fsPath = fsPath;

    init();
}

string Shader::readFile(string filePath){
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

uint Shader::compileShader(int shaderType, string shaderSource, uint shaderNum){
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

uint Shader::linkingProgram(uint vs, uint fs){
    
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

void Shader::use(){
    glUseProgram(m_id);
}

void Shader::setBool(const string &name, bool value) const{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}
void Shader::setInt(const string &name, int value) const{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}
void Shader::setFloat(const string &name, float value) const{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}
void Shader::setMat4(const string &name, uint columnMajorOrder, mat4 value) const{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, columnMajorOrder, value_ptr(value));
}

void Shader::setVec3(const string &name, vec3 value) const{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, value_ptr(value));
}
