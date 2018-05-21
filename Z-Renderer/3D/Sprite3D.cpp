//
//  Sprite3D.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Sprite3D.hpp"
#include "fileUtil.hpp"
#include "PhongShader.hpp"
#include "Camera.hpp"

Sprite3D * Sprite3D::create(const std::string &fileName) {
    auto ret = new Sprite3D();
    ret->init(fileName);
    return ret;
}

void Sprite3D::init(const std::string &fileName) {
    _shader = Sprite3DShader::create();
    Assimp::Importer importer;
    const aiScene * scene = importer.ReadFile(getFullPath(fileName), aiProcess_Triangulate | aiProcess_FlipUVs);
    initShader();
    handleNode(scene->mRootNode , scene);
}

void Sprite3D::initShader() {
    Ambient ambient;
    ambient.color = Color(1,1,1,1);
    ambient.factor = 0.15;
    
    Light light;
    light.pos = Vec3(0 , 0 , 9);
    light.color = Color(1 , 1 , 1 , 1);
    light.factor = 1.95;
    
    Material material;
    material.diffuseFactor = 0.9;
    material.specularFactor = 0.0;
    material.shininess = 64;
    
    _shader = PhongShader::create();
    static_cast<PhongShader *>(_shader)->setMaterial(material);
    static_cast<PhongShader *>(_shader)->setLight(light);
    static_cast<PhongShader *>(_shader)->setAmbient(ambient);
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
        if (mesh->mNormals != nullptr) {
            aiVector3D aiNormal = mesh->mNormals[i];
            vertex.normal = Vec3(aiNormal.x , aiNormal.y , aiNormal.z);
        }
        
        if (mesh->mTextureCoords[0] != nullptr) {
            aiVector3D aiTex = mesh->mTextureCoords[0][i];
            vertex.tex = Vec2(aiTex.x , aiTex.y);
        }
        
        vertice.push_back(vertex);
    }
    
    for (int i = 0 ; i < mesh->mNumFaces ; ++ i) {
        aiFace aiIndice = mesh->mFaces[i];
        for (int j = 0 ; j < aiIndice.mNumIndices ; ++ j) {
            int index = aiIndice.mIndices[j];
            indice.push_back(index);
        }
    }
    
    if (mesh->mMaterialIndex > 0) {
        aiMaterial * aiM = scene->mMaterials[mesh->mMaterialIndex];
        
    }
    
    Mesh ret(vertice , indice , textures);
    
    return ret;
}

void Sprite3D::draw(double dt) {
    
    double velo = 45;
    _rotate.y += velo * dt;
    if (_rotate.y > 360) {
        _rotate.y -= 360;
    }
    Mat4 r = Mat4::rotateY(MathUtil::angle2radian(_rotate.y));
    Mat4 model = r * Mat4::scale(_scale) * Mat4::translate(_position);
    auto camera = Camera::getInstance();
    auto v = camera->getViewMat();
    auto p = camera->getProjectionMat();
    _shader->setMvp(model , v, p);
    _shader->use();
    for (int i = 0 ; i < _meshes.size() ; ++ i) {
        _meshes.at(i).draw(_shader);
    }
}












