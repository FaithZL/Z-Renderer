//
//  Sprite3D.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Sprite3D_hpp
#define Sprite3D_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Mesh.hpp"

class Sprite3D : public Node {
    
public:
    vector<Mesh> meshes;
};

#endif /* Sprite3D_hpp */
