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
#include "Vertex.hpp"
#include "Color.hpp"

class Canvas {
public:
    
    Canvas(unsigned width = 800 , unsigned height = 600);
    
    void clear();
    
    void render();
    
    void lock();
    
    void update();
    
    inline unsigned getIndex(int px , int py) const {
        return (unsigned)(_width * py + px);
    }
    
    inline unsigned getPX(double x) const {
        double startX = -1;
        double hw = _width / 2;
        double px = (x - startX) * hw;
        return px;
    }
    
    inline unsigned getPY(double y) const {
        double startY = 1;
        double hh = -(_height / 2);
        double py = (y - startY) * hh;
        return py;
    }
    
    inline uint32_t * getPixels() const {
        return (uint32_t *) _surface->pixels;
    }
    
    void unlock();
    
    /**
     * draw a point to NDC
     * @param x     -1 <= x <= 1
     * @param y     -1 <= y <= 1
     * @param z     -1 <= z <= 1
     * @param color [description]
     */
    void drawPoint(double x , double y , double z , const Color &color);
    
    void drawPoint(const Vertex &vert);
    
    void drawPixel(int px , int py , double z , const Color &color) {
        if (!isPassDepth(px , py, z)) {
            return;
        }
        putPixel(px , py , color);
        _setDepth(px, py, z);
    }
    
    void putPixel(int px , int py , const Color &color);
    
    inline bool isPassDepth(int px , int py , double z) {
        unsigned index = getIndex(px , py);
        return z < _depthBuffer[index]
                && z <= 1;
    }
    
    void drawLine(const Vertex &vert1 , const Vertex &vert2);

    
    SDL_Surface * getSurface() const {
        return _surface;
    }
    
    void setSurface(SDL_Surface * p) {
        _surface = p;
    }
    
    ~Canvas(){
        delete [] _depthBuffer;
    }
    
protected:
    
    inline void _setDepth(int px , int py , double z) {
        unsigned index = getIndex(px, py);
        _depthBuffer[index] = z;
    }
    
    inline double _getDepth(int px , int py) {
        return _depthBuffer[getIndex(px , py)];
    }
    
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











