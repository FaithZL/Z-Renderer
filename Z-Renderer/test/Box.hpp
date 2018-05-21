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
#include "PhongShader.hpp"
#include <vector>
#include "Node.hpp"

using namespace std;

class Texture;

class Box : public Node {
    
public:
    Box();
    ~Box();
    
    static Box * create() {
        Box *ret = new Box();
        ret->init();
        return ret;
    }
    
    void updateTransform(double dt);
    
    void init();
    
    void draw(double dt);
protected:
    
    Texture * _texture;
    
    vector<Vertex> _vertice;
};

#endif /* Box_hpp */









