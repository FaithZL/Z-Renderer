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
    Vec4 pos;
    Color color;
    Vec4 normal;
    Ldouble u;
    Ldouble v;
    
    Vertex(Vec4 pos , Color color = Color(), Vec4 normal = Vec4() , Ldouble u = 0 , Ldouble v = 0);
    
    Vertex interpolate(const Vertex &vertex , Ldouble factor) const;
    
    void transform(const Mat4 &mat4);
};

#endif /* Vertex_hpp */
