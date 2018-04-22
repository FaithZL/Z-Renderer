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
    _depthBuffer = new double[_bufferSize]();
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
    for (double i = -1 ; i <= 1 ; i = i + 0.001) {
        drawPoint(i , i, i , Color(1 , 0 ,0 ,0));
    }
}

void Canvas::lock() {
    SDL_LockSurface(_surface);
}

void Canvas::unlock() {
    SDL_UnlockSurface(_surface);
}

void Canvas::putPixel(int px , int py , const Color &color) {
    unsigned index = getIndex(px, py);
    auto pixels = getPixels();
    pixels[index] = color.uint32();
}

void Canvas::drawPoint(double x , double y , double z , const Color &color) {
    bool outX = x > 1 || x < -1;
    bool outY = y > 1 || y < -1;
    bool outZ = z > 1 || z < -1;
    
    if (outX || outY || outZ) {
        return;
    }
    
    double startX = -1;
    double hw = _width / 2;
    double px = (x - startX) * hw;
    double startY = 1;
    double hh = -(_height / 2);
    double py = (y - startY) * hh;
    
    unsigned index = getIndex(px, py);
    double depth = _depthBuffer[index];
    if (z > depth) {
        return;
    }
    
    putPixel(px, py, color);
}

uint32_t * Canvas::getPixels() const {
    return (uint32_t *) _surface->pixels;
}











