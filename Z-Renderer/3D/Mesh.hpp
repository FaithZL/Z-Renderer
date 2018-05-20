//
//  Mesh.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include "Vertex.hpp"
#include "Ref.hpp"
#include "Texture.hpp"
#include <vector>


class Sprite3D;

using namespace std;

class Mesh : public Ref {
    
public:
    
    static Mesh * create(const vector<Vertex> &vertice , const vector<int> &indice , const vector<Texture *> &textures);
    
    void init(const vector<Vertex> &vertice , const vector<int> &indice , const vector<Texture *> &textures);
    
protected:
    
    vector<Vertex> _vertice;
    
    vector<Texture *> _textures;
    
    vector<int> _indice;
    
    Sprite3D * _sprite;
};

#endif /* Mesh_hpp */
