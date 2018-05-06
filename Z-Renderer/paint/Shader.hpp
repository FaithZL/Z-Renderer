//
//  Shader.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/23.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "Vertex.hpp"
#include "Mat4.hpp"

class Shader {
public:
    Shader() {
        
    }
    virtual ~Shader() {
        
    }
    
    virtual VertexOut vs(Vertex vin) = 0;
    
    virtual VertexOut fs(VertexOut vin) = 0;
    
    Mat4 _model;
    Mat4 _view;
    Mat4 _projection;
    
};

#endif /* Shader_hpp */
