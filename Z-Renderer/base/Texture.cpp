//
//  Texture.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/15.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Texture.hpp"
#include "Canvas.hpp"

Texture::Texture():
_bitmap(nullptr){
    
}

Texture::~Texture() {
    delete _bitmap;
}

void Texture::bind() const {
    Canvas::getInstance()->setTexture(this);
}

void Texture::unbind() const {
    Canvas::getInstance()->setTexture(nullptr);
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
    Color ret;
    int stride = (int)format;
    for (int i = 0; i < stride; ++ i) {
        ret.e[i] = pixel[index + i] / 255.0;
    }
    return ret;
}

Texture * Texture::create(const std::string &fileName) {
    auto ret = new Texture();
    
    ret->_bitmap = new Bitmap(fileName);
    
    return ret;
}

