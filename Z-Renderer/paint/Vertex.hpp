//
//  Vertex.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include "Vec.hpp"
#include "Color.hpp"
#include "Mat4.hpp"

class Vertex {
   
public:
    Vec3 pos;
    Color color;
    Vec3 normal;
    Vec2 tex;
    
    Vertex(Vec3 pos , Color color = Color(), Vec3 normal = Vec3() , Vec2 tex = Vec2());
    
    Vertex interpolate(const Vertex &vertex , Ldouble factor) const;
    
    void transform(const Mat4 &mat4);
};

class VertexOut {
    
public:
    VertexOut interpolate(const VertexOut &target , Ldouble factor) const;
    
    Vec2 tex;
    Vec3 normal;
    Color color;
    
    //相机空间坐标
    Vec4 posTrans;
    //裁剪空间中的齐次坐标
    Vec4 posClip;
    //屏幕像素坐标
    Vec2 posScrn;
    
    inline Ldouble getZ() const {
        return posClip.w;
    }
    
    inline Ldouble getDepth() const {
        return posClip.z / posClip.w;
    }
    
    Ldouble depth;
    
    Ldouble oneDivZ;
};

#endif /* Vertex_hpp */











