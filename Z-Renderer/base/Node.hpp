//
//  Node.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include "Ref.hpp"
#include "Vec.hpp"
#include "Macro.h"
#include "Shader.hpp"

class Node : public Ref {

public:
    
    Node() :
    _shader(nullptr){
        _scale = Vec3(1 , 1 , 1);
    }
    
    virtual void init() {
        
    }
    
    virtual void updateTransform(double dt) {
        
    }
    
    virtual void begin(double dt) {
        updateTransform(dt);
        _shader->use();
    }
    
    virtual void draw(double dt) {
        
    }
    
    virtual void end() {
        _shader->unUse();
    }
    
    virtual ~Node() {
        
    }
    
protected:
    
    Shader * _shader;
    
    Setter_and_getter_vec3(_position , Position)
    Setter_and_getter_vec3(_rotate , Rotation)
    Setter_and_getter_vec3(_scale , Scale)
};

#endif /* Node_hpp */
