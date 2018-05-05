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
        
    }
    
    virtual ~Node() {
        
    }
    
protected:

    Setter_and_getter_vec4(_position , Position)
    Setter_and_getter_vec4(_rotate , Rotation)
    Setter_and_getter_vec4(_scale , Scale)
};

#endif /* Node_hpp */
