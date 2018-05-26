//
//  SkyBox.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/26.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef SkyBox_hpp
#define SkyBox_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Vertex.hpp"
#include <vector>
#include "TextureCube.hpp"

class SkyBox : public Node {
    
public:
    static SkyBox * create();
    
    SkyBox();
    
    void init();
    
    virtual void draw(Ldouble dt);
    
protected:
    
    TextureCube * _textureCube;
    
    vector<Vertex> _vertice;
    
    vector<int> _indice;
};

#endif /* SkyBox_hpp */
