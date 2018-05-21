//
//  Sprite3D.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Sprite3D_hpp
#define Sprite3D_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Mesh.hpp"
#include "Sprite3DShader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Sprite3D : public Node {

public:
    static Sprite3D * create(const std::string &fileName);
    
    void init(const std::string &fileName);
    
    void handleNode(const aiNode * node , const aiScene * scene);
    
    void initShader();
    
    Mesh handleMesh(const aiMesh * mesh , const aiScene * scene);
    
    virtual void draw(double dt);
    
protected:
    vector<Mesh> _meshes;
    
    std::string _fileName;
};

#endif /* Sprite3D_hpp */
