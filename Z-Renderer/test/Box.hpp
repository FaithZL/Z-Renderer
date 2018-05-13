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
#include <vector>
#include "Node.hpp"

using namespace std;

class Box : public Node {
    
public:
    Box();
    ~Box();
    
    Shader * _shader;
    
    static Box * create() {
        Box *ret = new Box();
        ret->init();
        return ret;
    }
    
    void updateTransform(double dt);
    
    void init();
    
    void draw(double dt);
protected:
    
    vector<Vertex> _vertice;
};

#endif /* Box_hpp */
