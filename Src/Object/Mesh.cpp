#include "Mesh.h"



Mesh::Mesh(vector<Vertex> vertices, vector<uint> indices, vector<Texture> textures){
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;
    setupMesh();
}

void Mesh::Render(const Shader& shader){
    uint diffuseNr = 1;
    uint specularNr = 1;
    for(uint i = 0; i < m_textures.size(); ++i){
        glActiveTexture(GL_TEXTURE0+i);
        string number;
        string name = m_textures[i].type;
        if(name == TEXTURE_DIFFUSE){
            number = to_string(diffuseNr++);
        }else if(name == TEXTURE_SPECULAR){
            number = to_string(specularNr++);
        }

        shader.setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }
    glActiveTexture(0);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh(){
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
    
    // Vertex.pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);  
    // Vertex.normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);  
    // Vertex.texCoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);  
    // Vertex.color
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);  

    glBindVertexArray(0);
    
}