//
//  SkyBoxShader.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/26.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef SkyBoxShader_hpp
#define SkyBoxShader_hpp

#include <stdio.h>

#include "Shader.hpp"

class SkyBoxShader : public Shader {
    
public:
    create_func(SkyBoxShader)
    
    void init();
    virtual VertexOut vs(const Vertex &vertex) const;
    virtual Color fs(const VertexOut &frag) const;
};

#endif /* SkyBoxShader_hpp */
