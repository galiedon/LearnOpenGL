#pragma once
#include <glm.hpp>
#include <string>
#include <vector>
#include "../Shader/Shader.h"
using namespace glm;
using namespace std;

#define TEXTURE_DIFFUSE "texture_diffuse"
#define TEXTURE_SPECULAR "texture_specular"

typedef struct{
    vec3 position;
    vec3 normal;
    vec2 texCoords;
    vec3 color;
}Vertex;

typedef struct{
    uint id;
    string type;
    string path;
}Texture;

class Mesh{

public:
    vector<Vertex> m_vertices;
    vector<uint> m_indices;
    vector<Texture> m_textures;

    Mesh(vector<Vertex> vertices, vector<uint> indices, vector<Texture> textures);
    void Render(const Shader& shader);

private:
    uint m_VAO, m_VBO, m_IBO;
    void setupMesh();
};