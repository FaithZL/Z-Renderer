//
//  Texture.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/15.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Texture.hpp"


Texture::Texture():
_bitmap(nullptr){
    
}

Texture::~Texture() {
    delete _bitmap;
}

Color Texture::sample(double u, double v) const {
    // 纹理坐标跟像素坐标纵坐标相反
    v = 1 - v;
    auto width = _bitmap->getWidth();
    auto height = _bitmap->getHeight();
    auto format = _bitmap->getFormat();
    unsigned char * pixel = _bitmap->getPixels();
    int tu = u * (width - 1);
    int tv = v * (height - 1);
    int index = (width * tv * (int)format) + tu * (int)format;
    uint32_t colorBit = pixel[index];
    return Color((uint32_t)colorBit);
}

Texture * Texture::create(const std::string &fileName) {
    auto ret = new Texture();
    
    ret->_bitmap = new Bitmap(fileName);
    
    return ret;
}

