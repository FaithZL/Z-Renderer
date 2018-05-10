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
    vOut.posClip = _mvp.transform(Vec4(vert.pos , 1.0f));
    vOut.color = vert.color;
    vOut.linearDepth = false;
    
    return vOut;
}

VertexOut Shader::fs(const VertexOut &vert) const {
    VertexOut vOut = vert;
    
    return vOut;
}
