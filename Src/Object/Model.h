#pragma once
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "SOIL/SOIL.h"

class Model{
public:
    vector<Texture> textures_loaded;
    vector<Mesh> m_meshList;
    string m_directory;

    Model(string path);
    Model();

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    void Render(Shader shader);

private:
    uint loadTexture(string imgPath, uint filterType, uint repeatType);

};