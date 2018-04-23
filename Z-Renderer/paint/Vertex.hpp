//
//  Vertex.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include "Vec3.hpp"
#include "Color.hpp"
#include "Mat4.hpp"

class Vertex {
   
public:
    Vec3 pos;
    Color color;
    Vec3 normal;
    Ldouble u;
    Ldouble v;
    
    Vertex(Vec3 pos , Color color = Color(), Vec3 normal = Vec3() , Ldouble u = 0 , Ldouble v = 0);
    
    Vertex interpolate(const Vertex &vertex , Ldouble factor) const;
    
    void transform(const Mat4 &mat4);
};

#endif /* Vertex_hpp */
