//
//  SkyBox.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/26.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "SkyBox.hpp"
#include "Canvas.hpp"
#include "SkyBoxShader.hpp"

SkyBox::SkyBox():
_textureCube(nullptr) {
    
}

SkyBox * SkyBox::create() {
    auto ret = new SkyBox();
    
    ret->init();
    
    return ret;
}

void SkyBox::init() {
    _textureCube = TextureCube::create("skyback.jpg", "skyfront.jpg", "right.jpg", "left.jpg", "top.jpg", "bottom.jpg");
    
    vector<Vec3> pos = {
        Vec3(1, -1, 1),Vec3(1, 1, 1),Vec3(-1, 1, 1),Vec3(-1, -1, 1),
        Vec3(1, -1, -1),Vec3(1, 1, -1),Vec3(-1, 1, -1),Vec3(-1, -1, -1),
    };
    
    for (int i = 0 ; i < pos.size(); ++ i) {
        _vertice.push_back(Vertex(pos.at(i)));
    }
    
    vector<int> idxBuf = {
        2, 1, 0, 3, 2, 0, // front
        1, 5, 4, 1, 4, 0, // right
        4, 5, 6, 4, 6, 7, // back
        7, 6, 2, 7, 2, 3, // left
        2, 6, 5, 2, 5, 1, // up
        3, 0, 4, 3, 4, 7  // down
    };
    _indice = idxBuf;
    
    _shader = SkyBoxShader::create();
}

void SkyBox::draw(Ldouble dt) {
    auto canvas = Canvas::getInstance();
    
    auto camera = Camera::getInstance();
    
    _shader->setViewMat(camera->getCurDirectionMat());
//    _shader->setViewMat(camera->getViewMat());
    _shader->setProjectionMat(camera->getProjectionMat());
    
    canvas->setShader(_shader);
    canvas->setTextureCube(_textureCube);
    canvas->drawElement(_vertice, _indice);
}











