//
//  Bitmap.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/15.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Bitmap.hpp"
#include <cstdlib>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"


Bitmap::Bitmap():
    _path(""),
    _pixels(nullptr),
    _width(0),
    _height(0),
    _format(Format_RGBA){
    
}

Bitmap::Bitmap(const string &fileName) {
    int width , height , channel;
    unsigned char * pixels = stbi_load(fileName.c_str(), &width, &height , &channel , 0);
    stbi_image_free(pixels);
    init(width , height, _format , _pixels);
    free(pixels);
    _path = fileName;
}

Bitmap::~Bitmap() {
    free(_pixels);
}

Bitmap::Bitmap(const Bitmap &other) {
    init(other._width, other._height, other._format, other._pixels);
}

Bitmap & Bitmap::operator = (const Bitmap &other) {
    init(other._width, other._height, other._format, other._pixels);
    return *this;
}

void Bitmap::init(int width, int height, Bitmap::Format format, unsigned char *pixel) {
    if(width == 0) throw std::runtime_error("Zero width bitmap");
    if(height == 0) throw std::runtime_error("Zero height bitmap");
    if(format <= 0 || format > 4) throw std::runtime_error("Invalid bitmap format");
    
    _width = width;
    _height = height;
    _format = format;
    unsigned newSize = _width * _height * _format;
    if(_pixels){
        _pixels = (unsigned char*)realloc(_pixels, newSize);
    } else {
        _pixels = (unsigned char*)malloc(newSize);
    }
    memcpy(_pixels , pixel , newSize);
}

//Bitmap Bitmap::create(const string &fileName) {
//
//}












