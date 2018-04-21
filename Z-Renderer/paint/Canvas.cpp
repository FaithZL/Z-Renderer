//
//  Canvas.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Canvas.hpp"
#include <algorithm>

Canvas::Canvas(unsigned width , unsigned height):
_surface(nullptr),
_width(width),
_height(height),
_bufferSize(height * width){
    
}

void Canvas::clear() {
    memset(getPixels(), 0, sizeof(uint32_t) * _width * _height);
    std::fill(_depthBuffer, _depthBuffer + _bufferSize, 1);
}

void Canvas::update() {
    
    lock();
    
    clear();
    
    render();
    
    unlock();
    
}

void Canvas::render() {
    for (int i = 0 ; i < 500 ; ++ i) {
        putPixel(i , i, Color(1 , 1 ,1 ,1));
    }
}

void Canvas::lock() {
    SDL_LockSurface(_surface);
}

void Canvas::unlock() {
    SDL_UnlockSurface(_surface);
}

void Canvas::putPixel(int x , int y , const Color &color) {
    unsigned index = (unsigned)(_width * y + x);
    
    auto pixels = getPixels();
    pixels[index] = color.uint32();
}

void Canvas::drawPoint(double x , double y , double z , const Color &color) {
    
}

uint32_t * Canvas::getPixels() const {
    return (uint32_t *) _surface->pixels;
}











