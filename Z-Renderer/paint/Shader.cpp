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
    vOut.color = vert.color;
    
    return vOut;
}

Color Shader::fs(const VertexOut &vert) const {
    Color ret = vert.color;
    
    return ret;
}
