//
//  Shader.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/23.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "Mat4.hpp"
#include "Mat4x4.hpp"

class Shader {
public:
    Shader() {
        
    }
    virtual ~Shader() {
        
    }
    
    Mat4x4 _model;
    Mat4x4 _view;
    Mat4x4 _projection;
    
};

#endif /* Shader_hpp */
