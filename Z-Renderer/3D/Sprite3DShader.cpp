//
//  Sprite3DShader.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Sprite3DShader.hpp"

VertexOut Sprite3DShader::vs(const Vertex &vert) const {
    return PhongShader::vs(vert);
}

Color Sprite3DShader::fs(const VertexOut &frag) const {
    return PhongShader::fs(frag);
}
