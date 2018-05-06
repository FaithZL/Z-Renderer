//
//  Vertex.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Vertex.hpp"

Vertex::Vertex(Vec3 pos , Color color, Vec3 normal , Vec2 tex):
pos(pos),
normal(normal),
tex(tex),
color(color){

}


Vertex Vertex::interpolate(const Vertex &vertex, Ldouble factor) const {
    Vec3 p = pos.interpolate(vertex.pos , factor);
    Vec3 nor = normal.interpolate(vertex.normal, factor);
    Vec2 t = tex.interpolate(vertex.tex , factor);
    Color c = color.interpolate(vertex.color, factor);
    return Vertex(p , c , nor , t);
}

void Vertex::transform(const Mat4 &mat4) {
//    pos = mat4.transform(pos);
}

