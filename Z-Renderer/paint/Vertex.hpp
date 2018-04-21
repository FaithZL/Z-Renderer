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

class Vertex {
   
public:
    Vec3 pos;
    Color color;
    Vec3 normal;
    double u;
    double v;
    
    Vertex(Vec3 pos , Vec3 normal , double u , double v , Color color = Color());
    
    Vertex interpolate(Vertex vertex , double factor);
};

#endif /* Vertex_hpp */
