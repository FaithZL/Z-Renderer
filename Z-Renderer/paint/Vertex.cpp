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

Ldouble VertexOut::interpolateZ(const VertexOut &target, Ldouble factor) const {
    if (MathUtil::equal(oneDivZ , target.oneDivZ)) {
        return 1 / oneDivZ;
    }
    Ldouble _oneDivZ;
    _oneDivZ = MathUtil::interpolate(oneDivZ , target.oneDivZ , factor);
    return 1 / _oneDivZ;
}

VertexOut VertexOut::interpolate(const VertexOut &target, Ldouble factor) const {
    VertexOut ret;
    
    ret.pos = pos.interpolate(target.pos, factor);
    ret.oneDivZ = MathUtil::interpolate(oneDivZ , target.oneDivZ , factor);
    
    Ldouble z1 = getZ();
    Ldouble z = ret.getZ();
    Ldouble z2 = target.getZ();
    Ldouble cfactor;
    //透视校正
    if (z1 == z2) {
        cfactor = factor;
    } else {
        cfactor = (z - z1) / (z2 - z1);
    }
    ret.fixedNormal = fixedNormal.interpolate(target.fixedNormal, cfactor);
    ret.posWorld = posWorld.interpolate(target.posWorld, cfactor);
    ret.normal = normal.interpolate(target.normal , cfactor);
    ret.color = color.interpolate(target.color, cfactor);
    ret.posTrans = posTrans.interpolate(target.posTrans , cfactor);
    ret.tex = tex.interpolate(target.tex , cfactor);
    
    return ret;
}





