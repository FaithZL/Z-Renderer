//
//  Box.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/3.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include "Vertex.hpp"
#include "Shader.hpp"

class Box {
    
public:
    Box();
    ~Box();
    
    Shader * _shader;
    
    void draw();
};

#endif /* Box_hpp */
