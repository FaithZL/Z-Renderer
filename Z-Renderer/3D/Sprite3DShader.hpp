//
//  Sprite3DShader.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Sprite3DShader_hpp
#define Sprite3DShader_hpp

#include <stdio.h>
#include "Shader.hpp"

class Sprite3DShader : public Shader {
    
public:
    
    create_func(Sprite3DShader)
    
    virtual VertexOut vs(const Vertex &vert) const;
    
    virtual Color fs(const VertexOut &frag) const;
    
};

#endif /* Sprite3DShader_hpp */
