//
//  TextureCube.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/26.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "TextureCube.hpp"

TextureCube::TextureCube() {
    
}

Color TextureCube::sample(Vec3 pos) const {
    return sample(pos.x , pos.y, pos.z);
}

Ldouble tranform(Ldouble v) {
    return (v + 1) / 2.0;
}

Color TextureCube::sample(Ldouble x, Ldouble y, Ldouble z) const {
    if (z == -1) {
        x = tranform(-x);
        y = tranform(y);
        return _front->sample(x , y);
    } else if (z == 1) {
        x = tranform(x);
        y = tranform(y);
        return _back->sample(x , y);
    } else if (y == -1) {
        z = tranform(z);
        x = tranform(x);
        return _bottom->sample(x, z);
    } else if (y == 1) {
        z = tranform(-z);
        x = tranform(x);
        return _top->sample(x, z);
    } else if (x == -1) {
        y = tranform(y);
        z = tranform(z);
        return _left->sample(z, y);
    } else if (x == 1) {
        y = tranform(y);
        z = tranform(-z);
        return _right->sample(z , y);
    }
    
    return Color();
}

TextureCube * TextureCube::create(const string &back, const string &front, const string &right, const string &left, const string &top, const string &bottom) {
    auto ret = new TextureCube();
    
    ret->_front = Texture::create(front);
    ret->_top = Texture::create(top);
    ret->_back = Texture::create(back);
    ret->_left = Texture::create(left);
    ret->_right = Texture::create(right);
    ret->_bottom = Texture::create(bottom);
    
    return ret;
}
