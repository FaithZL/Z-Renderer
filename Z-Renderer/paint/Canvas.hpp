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
    void drawPointRasterize(Ldouble x , Ldouble y , Ldouble z , const Color &color);
    
    void drawPointRasterize(const Vertex &vert);
    
    void drawPixel(int px , int py , Ldouble z , const Color &color) {
        if (!isPassDepth(px , py, z)) {
            return;
        }
        putPixel(px , py , color);
        _setDepth(px, py, z);
    }
    
    void drawTriangle(const Vertex &v1 , const Vertex &v2 , const Vertex &v3);
    
    void triangleRasterize(const Vertex &v1 , const Vertex &v2 , const Vertex &v3);
    
    void putPixel(int px , int py , const Color &color);
    
    inline bool isPassDepth(int px , int py , Ldouble z) {
        unsigned index = getIndex(px , py);
        return z <= _depthBuffer[index]
                && z >= - 1;
    }
    
    void scanLineFill(const Vertex &v1 , const Vertex &v2 , int yIdx);
    
    void drawLineRasterize(const Vertex &vert1 , const Vertex &vert2);
    
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
    
    inline void _setDepth(int px , int py , Ldouble z) {
        unsigned index = getIndex(px, py);
        _depthBuffer[index] = z;
    }
    
    /**
     *     1
     *
     *  3       2
     * @param v1 [description]
     * @param v2 [description]
     * @param v3 [description]
     */
    void _triangleTopRasterize(const Vertex &v1 , const Vertex &v2 , const Vertex &v3);
    
    /**
     * 1     2
     *
     *     3
     * @param v1 [description]
     * @param v2 [description]
     * @param v3 [description]
     */    
    void _triangleBottomRasterize(const Vertex &v1 , const Vertex &v2 , const Vertex &v3);
    
    inline Ldouble _getDepth(int px , int py) {
        return _depthBuffer[getIndex(px , py)];
    }
    
    inline unsigned getIndex(int px , int py) const {
        return (unsigned)((_width) * py + px);
    }
    
    inline unsigned _getPX(Ldouble x) const {
        Ldouble startX = -1;
        Ldouble hw = _width / 2;
        unsigned px = MathUtil::round((x - startX) * hw);
        return px;
    }
    
    inline unsigned _getPY(Ldouble y) const {
        Ldouble startY = 1;
        Ldouble hh = -(_height / 2);
        unsigned py = MathUtil::round((y - startY) * hh);
        return py;
    }
    
    int _width;
    
    int _height;
    
    unsigned _bufferSize;
    
    /**
     * -1 <= depth <= 1
     */
    Ldouble * _depthBuffer;
    
    SDL_Surface * _surface;
};

#endif /* Canvas_hpp */











