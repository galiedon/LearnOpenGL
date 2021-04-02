#include "Model.h"

using namespace Assimp;

Model::Model(string path){
    loadModel(path);
}
Model::Model(){}

void Model::loadModel(string path){
    Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
    }

    m_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene){
    for(uint i = 0; i < node->mNumMeshes; ++i){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshList.push_back(processMesh(mesh, scene));
    }

    for(uint i = 0; i < node->mNumChildren; ++i){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    vector<Vertex> vertices;
    vector<uint> indices;
    vector<Texture> textures;

    for(uint i = 0; i < mesh->mNumVertices; ++i){
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标。
        vec3 vector3; 
        vector3.x = mesh->mVertices[i].x;
        vector3.y = mesh->mVertices[i].y;
        vector3.z = mesh->mVertices[i].z; 
        vertex.position = vector3;

        vector3.x = mesh->mNormals[i].x;
        vector3.y = mesh->mNormals[i].y;
        vector3.z = mesh->mNormals[i].z;
        vertex.normal = vector3;


        if(mesh->mTextureCoords[0]){
            vec2 texCoords; 
            
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = texCoords;
        }else{
            vertex.texCoords = vec2(0);
        }

        if(mesh->mColors[0]){
            vector3.x = mesh->mColors[0][i].r;
            vector3.y = mesh->mColors[0][i].g;
            vector3.z = mesh->mColors[0][i].b;
            vertex.color = vector3;
        }else{
            vertex.color = vec3(0);
        }
        vertices.push_back(vertex);
    }

    // 处理索引
    for(uint i = 0; i < mesh->mNumFaces; ++i){
        aiFace face = mesh->mFaces[i];
        for(uint j = 0; j < face.mNumIndices; ++j){
            indices.push_back(face.mIndices[j]);
        }
    }

    // 处理材质
    if(mesh->mMaterialIndex >= 0){
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TEXTURE_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName){
    vector<Texture> textures;
    for(uint i = 0; i < mat->GetTextureCount(type); ++i){
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for(uint j = 0; j < textures_loaded.size(); ++j){
            if(strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0){
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        
        if(skip){
            continue;
        }

        Texture texture;
        texture.id = loadTexture(m_directory+'/'+str.C_Str(), GL_LINEAR, GL_REPEAT);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture);
    }

    return textures;
}

void Model::Render(Shader shader){
    for(uint i = 0; i < m_meshList.size(); ++i){
        m_meshList[i].Render(shader);
    }
}

uint Model::loadTexture(string imgPath, uint filterType, uint repeatType){
    int width, height, nrComponents;
    uint tex;
    // 加载图片
    uchar* image = SOIL_load_image(imgPath.c_str(), &width, &height, &nrComponents, 0);

    GLenum format;
    if(!image){
        std::cout << "Failed to load Image!" << std::endl;
        return FAILED;
    }else{
        switch(nrComponents){
            case 1: format = GL_RED; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
        }
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
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    // 生成Mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    // 释放图片与TextureID
    SOIL_free_image_data(image);
    //glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}