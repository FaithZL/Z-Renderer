//
//  Ground.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Ground.hpp"
#include "Canvas.hpp"

void Ground::init() {
    _shader = Shader::create();
    
    int d = 3;
    
    Vertex v1 = Vertex(Vec3(d , 0 , -d) , Color(1,1,1,1));
    Vertex v2 = Vertex(Vec3(-d , 0 , -d) , Color(1,1,1,1));
    Vertex v3 = Vertex(Vec3(-d , 0 , d) , Color(1,1,1,1));
    Vertex v4 = Vertex(Vec3(d , 0 , d) , Color(1,1,1,1));
    
    _vertice.push_back(v1);
    _vertice.push_back(v2);
    _vertice.push_back(v3);
    _vertice.push_back(v4);
    
    _indice = {0 , 1 , 2 , 0 , 2 , 3};
    
}

void Ground::draw(double dt) {
    begin(dt);
    auto canvas = Canvas::getInstance();
    canvas->setCullingMode(None);
    canvas->drawElement(_vertice, _indice);
    canvas->setCullingMode(CW);
    end();
}
