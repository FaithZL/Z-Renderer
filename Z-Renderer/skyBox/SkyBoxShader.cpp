//
//  SkyBoxShader.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/26.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "SkyBoxShader.hpp"
#include "TextureCube.hpp"
#include "Canvas.hpp"

void SkyBoxShader::init() {
    
}

VertexOut SkyBoxShader::vs(const Vertex &vert) const {
    auto ret = VertexOut();
    
    auto vp = _view * _projection;
    ret.posTrans = Vec4(vert.pos , 1);
    ret.pos = vp.transform(Vec4(vert.pos , 1.0f));
    
    ret.pos.z = ret.pos.w;
    
    return ret;
}

Color SkyBoxShader::fs(const VertexOut &frag) const {
    auto ret = Color();
    
    const TextureCube * tc = Canvas::getInstance()->getTextureCube();
    ret = tc->sample(frag.posTrans.getVec3());
    
    return ret;
}
