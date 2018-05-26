//
//  TextureCube.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/26.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef TextureCube_hpp
#define TextureCube_hpp

#include <stdio.h>
#include "Texture.hpp"
#include "Vec.hpp"

class TextureCube {
    
public:
    TextureCube();
    
    static TextureCube * create(const string &back,
                                const string &front,
                                const string &right,
                                const string &left,
                                const string &top,
                                const string &bottom);
    
    Color sample(Vec3 pos) const;
    
    Color sample(Ldouble x , Ldouble y , Ldouble z) const;
    
protected:
    
    Texture * _front;
    Texture * _back;
    Texture * _right;
    Texture * _left;
    Texture * _top;
    Texture * _bottom;
};

#endif /* TextureCube_hpp */
