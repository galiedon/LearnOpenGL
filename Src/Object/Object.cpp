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
}

void Object::init(string vsPath, string fsPath, vector<float> vecVert, vector<uint>vecId){
    shader.init(vsPath, fsPath);
    m_vertices = vecVert;
    m_indices = vecId; 
    init();
}


void Object::render(){
    shader.use();
}