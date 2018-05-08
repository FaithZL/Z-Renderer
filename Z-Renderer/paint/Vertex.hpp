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
    Vec2 tex;
    Vec3 normal;
    Color color;
    
    //相机空间坐标
    Vec4 posTrans;
    //裁剪空间中的齐次坐标
    Vec4 posClip;
    //屏幕像素坐标
    Vec2 posScrn;
    
    //深度值是否为线性，如果是投影变换，深度值的倒数为线性
    bool linearDepth = true;
    
    //[0,1] -1为初始值
    Ldouble depth = -1;
};

#endif /* Vertex_hpp */











