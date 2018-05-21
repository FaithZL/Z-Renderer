//
//  Ground.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Ground_hpp
#define Ground_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Vertex.hpp"
#include <vector>

class Ground : public Node {
    
public:
    
    virtual void draw(double dt);
    
    create_func(Ground);
    
    void init();
    
protected:
    
    std::vector<Vertex> _vertice;
    
    std::vector<int> _indice;
};

#endif /* Ground_hpp */
