//
//  Ref.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Ref_hpp
#define Ref_hpp

#include <stdio.h>

class Ref {
    
    Ref():
    _refCount(1){
        
    }
    
    void retain() {
        ++_refCount;
    }
    
    void release() {
        --_refCount;
        if (_refCount == 0) {
            delete this;
        }
    }
    
public:
    unsigned _refCount;
};

#endif /* Ref_hpp */
