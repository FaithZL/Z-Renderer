//
//  Canvas.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Vec3.hpp"

class Canvas {
public:
    
    Canvas();
    
    void clear();
    
    void render();
    
    void lock();
    
    void unlock();
    
    void putPixel(int x , int y , int z , u_int32_t color);
    
    void drawLine();
    
    SDL_Surface * getSurface() const {
        return _surface;
    }
    
    void setSurface(SDL_Surface * p) {
        _surface = p;
    }
    
protected:
    
    unsigned _width;
    
    unsigned _height;
    
    int _bufferSize;
    
    double * _depthBuffer;
    
    SDL_Surface * _surface;
};

#endif /* Canvas_hpp */











