//
//  Shader.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/8.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Shader.hpp"
#include "Canvas.hpp"

VertexOut Shader::vs(const Vertex &vert) const {
    VertexOut vOut;
    auto temp = Vec4(vert.pos , 1.0f);
    vOut.posTrans = _mv.transform(temp);
    vOut.pos = _mvp.transform(Vec4(vert.pos , 1.0f));
    vOut.posWorld = _model.transform(Vec4(vert.pos , 1.0f));
    vOut.normal = _model.transform(Vec4(vert.normal , 0)).get3DNormal();
    vOut.color = vert.color;
    vOut.tex = vert.tex;
    
    return vOut;
}

void Shader::use() const {
    Canvas::getInstance()->setShader(this);
}

void Shader::unUse() const {
    Canvas::getInstance()->setShader(nullptr);
}

Color Shader::fs(const VertexOut &vert) const {
    
    auto texture = Canvas::getInstance()->getTexture();
    
    auto ret = texture->sample(vert.tex.u, vert.tex.v);
    
//    ret = vert.color;
    
    return ret;
}
