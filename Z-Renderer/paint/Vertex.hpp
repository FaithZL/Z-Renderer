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
    
    Vec4 normal;
    
    Color color;
    
    //相机空间坐标
    Vec4 posTrans;
    //透视投影后的坐标
    Vec4 posPer;
    // z值的倒数用于深度测试，投影变换后的1/z与深度成线性关系
    Ldouble oneDivZ;
};

#endif /* Vertex_hpp */
