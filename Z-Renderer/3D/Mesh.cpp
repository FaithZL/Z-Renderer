//
//  Mesh.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Mesh.hpp"

Mesh * Mesh::create(const vector<Vertex> &vertice, const vector<int> &indice, const vector<Texture *> &textures) {
    Mesh * ret = new Mesh();
    ret->init(vertice , indice , textures);
    return ret;
}

void Mesh::init(const vector<Vertex> &vertice, const vector<int> &indice, const vector<Texture *> &textures) {
    
}

void Mesh::setUp() {
    
}

void Mesh::draw(Shader *shader) const {
    
}
