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

class Node : public Ref {

public:
    
    Node() {
        _scale = Vec3(1 , 1 , 1);
    }
    
    virtual void init() {
        
    }
    
    virtual void updateTransform() {
        
    }
    
    virtual void draw(double dt) {
        
    }
    
    virtual ~Node() {
        
    }
    
protected:

    Setter_and_getter_vec3(_position , Position)
    Setter_and_getter_vec3(_rotate , Rotation)
    Setter_and_getter_vec3(_scale , Scale)
};

#endif /* Node_hpp */
