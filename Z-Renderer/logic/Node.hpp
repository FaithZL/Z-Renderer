//
//  Node.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include "Ref.hpp"
#include "Vec.hpp"

class Node : public Ref {
    
    inline void setPosition(const Vec3 &pos) {
        _position = pos;
    }
    
    inline Vec3 getPosition() const {
        return _position;
    }
    
    inline void setScale(const Vec3 &scale) {
        _scale = scale;
    }
    
    inline Vec3 getScale() const {
        return _scale;
    }
    
public:
    Vec3 _position;
    
    Vec3 _scale;
};

#endif /* Node_hpp */
