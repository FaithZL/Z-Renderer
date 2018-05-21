//
//  Mesh.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Mesh.hpp"
#include "Canvas.hpp"

Mesh * Mesh::create(const vector<Vertex> &vertice, const vector<int> &indice, const vector<Texture *> &textures) {
    Mesh * ret = new Mesh();
    ret->init(vertice , indice , textures);
    return ret;
}

void Mesh::init(const vector<Vertex> &vertice, const vector<int> &indice, const vector<Texture *> &textures) {
    _vertice = vertice;
    _indice = indice;
    _textures = textures;
}

void Mesh::draw(Shader *shader) const {
    auto canvas = Canvas::getInstance();
    canvas->drawElement(_vertice , _indice);
}
