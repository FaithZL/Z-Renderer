//
//  Sprite3D.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Sprite3D.hpp"
#include "fileUtil.hpp"

Sprite3D * Sprite3D::create(const std::string &fileName) {
    auto ret = new Sprite3D();
    ret->init(fileName);
    return ret;
}

void Sprite3D::init(const std::string &fileName) {
    _shader = Sprite3DShader::create();
    Assimp::Importer importer;
    const aiScene * scene = importer.ReadFile(getFullPath(fileName), aiProcess_Triangulate | aiProcess_FlipUVs);
    
    handleNode(scene->mRootNode , scene);
}

void Sprite3D::handleNode(const aiNode *node, const aiScene *scene) {
    for (int i = 0 ; i < scene->mNumMeshes ; ++ i) {
        Mesh mesh = handleMesh(scene->mMeshes[i], scene);
        _meshes.push_back(mesh);
    }
    for (int i = 0 ; i < node->mNumChildren ; ++ i) {
        handleNode(node->mChildren[i], scene);
    }
}

Mesh Sprite3D::handleMesh(const aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertice;
    vector<int> indice;
    vector<Texture *> textures;
    for (int i = 0 ; i < mesh->mNumVertices ; ++ i) {
        aiVector3D aiVec = mesh->mVertices[i];
        Vertex vertex;
        vertex.pos = Vec3(aiVec.x , aiVec.y , aiVec.z);
        vertice.push_back(vertex);
    }
    
    for (int i = 0 ; i < mesh->mNumFaces ; ++ i) {
        aiFace aiIndice = mesh->mFaces[i];
        for (int j = 0 ; j < aiIndice.mNumIndices ; ++ j) {
            int index = aiIndice.mIndices[j];
            indice.push_back(index);
        }
    }
    
    Mesh ret(vertice , indice , textures);
    
    return ret;
}

void Sprite3D::draw(double dt) const {
    for (int i = 0 ; i < _meshes.size() ; ++ i) {
        _meshes.at(i).draw(_shader);
    }
}












