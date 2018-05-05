//
//  Vertex.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Vertex.hpp"

Vertex::Vertex(Vec4 pos , Color color, Vec4 normal , Ldouble u , Ldouble v):
pos(pos),
normal(normal),
u(u),
v(v),
color(color){

}


Vertex Vertex::interpolate(const Vertex &vertex, Ldouble factor) const {
    Vec4 p = pos.interpolate(vertex.pos , factor);
    Vec4 nor = normal.interpolate(vertex.normal, factor);
    Ldouble tu = u + (vertex.u - u) * factor;
    Ldouble tv = v + (vertex.v - v) * factor;
    Color c = color.interpolate(vertex.color, factor);
    return Vertex(p , c , nor , tu , tv);
}

void Vertex::transform(const Mat4 &mat4) {
    pos = mat4.transform(pos);
}
