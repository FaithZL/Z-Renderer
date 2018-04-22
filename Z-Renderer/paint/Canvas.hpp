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
#include "Color.hpp"

class Canvas {
public:
    
    Canvas(unsigned width = 800 , unsigned height = 600);
    
    void clear();
    
    void render();
    
    void lock();
    
    void update();
    
    unsigned getIndex(int px , int py) const {
        return (unsigned)(_width * py + px);
    }
    
    uint32_t * getPixels() const;
    
    void unlock();
    
    /**
     * draw a point to NDC
     * @param x     -1 <= x <= 1
     * @param y     -1 <= y <= 1
     * @param z     -1 <= z <= 1
     * @param color [description]
     */
    void drawPoint(double x , double y , double z , const Color &color);
    
    void putPixel(int px , int py , const Color &color);
    
    void drawLine();
    
    SDL_Surface * getSurface() const {
        return _surface;
    }
    
    void setSurface(SDL_Surface * p) {
        _surface = p;
    }
    
protected:
    
    int _width;
    
    int _height;
    
    unsigned _bufferSize;
    
    /**
     * -1 <= depth <= 1
     */
    double * _depthBuffer;
    
    SDL_Surface * _surface;
};

#endif /* Canvas_hpp */











