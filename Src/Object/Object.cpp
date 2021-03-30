#include "Object.h"
#include <fstream>
using ifstream = std::ifstream;
using ios = std::ios;

Object::Object(){
}

Object::Object(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId):
m_vertices(vecVert),
m_indices(vecId){
    
    shader.init(vsPath, fsPath);
    init();
}

void Object::init(){

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // 1. 设置顶点属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);  // 1. 设置顶点属性指针
}

void Object::init(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId){
    shader.init(vsPath, fsPath);
    m_vertices = vecVert;
    m_indices = vecId; 
    init();
}


void Object::render(){
    shader.use();
    glBindVertexArray(m_VAO);
    // 3. 绘制物体
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}