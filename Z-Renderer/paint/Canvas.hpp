//
//  Canvas.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include "Shader.hpp"
#include <SDL2/SDL.h>
#include "Vertex.hpp"
#include "Color.hpp"
#include "Camera.hpp"

enum DrawMode {
    Frame,
    Fill
};

class Canvas {
public:
    
    void clear();
    
    static Canvas * getInstance();
    
    void render();
    
    void lock();
    
    void update();
    
    inline uint32_t * getPixels() const {
        return (uint32_t *) _surface->pixels;
    }
    
    void unlock();
    
    void lineBresenham(const VertexOut &v1 , const VertexOut &v2);
    
    void scanLineFill(const VertexOut &v1 , const VertexOut &v2 , int yIndex);
    
    void drawPixel(int px , int py , Ldouble z , const Color &color) {
        if (!isPassClip(px , py)) {
            return;
        }
        if (!isPassDepth(px , py, z)) {
            return;
        }
        putPixel(px , py , color);
        _setDepth(px, py, z);
    }
    
    inline bool isPassClip(int px , int py) {
        bool ret = px >= 0
            && px < _width
            && py >= 0
            && py < _height;
        return ret;
    }
    
    inline void setDrawMode(DrawMode mode) {
        _drawMode = mode;
    }
    
    inline DrawMode getDrawMode() const {
        return _drawMode;
    }
    
    VertexOut handleVertex(const Vertex &vert) const;
    
    void transformToScrn(VertexOut &vert) const;
    
    void drawTriangle(const Vertex &v1 , const Vertex &v2 , const Vertex &v3);
    
    void _triangleRasterize(const VertexOut &v1 , const VertexOut &v2 , const VertexOut &v3);
    
    /**
     *     1
     *
     *  3       2
     * @param v1 [description]
     * @param v2 [description]
     * @param v3 [description]
     */
    void _triangleTopRasterize(const VertexOut &v1 , const VertexOut &v2 , const VertexOut &v3);
    
    /**
     * 1     2
     *
     *     3
     * @param v1 [description]
     * @param v2 [description]
     * @param v3 [description]
     */
    void _triangleBottomRasterize(const VertexOut &v1 , const VertexOut &v2 , const VertexOut &v3);
    
    void putPixel(int px , int py , const Color &color);
    
    inline bool isPassDepth(int px , int py , Ldouble z) {
        int index = getIndex(px , py);
        return z <= _depthBuffer[index]
                && z >= 0;
    }
    
    inline void setShader(Shader * shader) {
        _shader = shader;
    }
    
    SDL_Surface * getSurface() const {
        return _surface;
    }
    
    inline int getWidth() const {
        return _width;
    }
    
    inline int getHeight() const {
        return _height;
    }
    
    void setSurface(SDL_Surface * p) {
        _surface = p;
    }
    
    ~Canvas(){
        delete [] _depthBuffer;
    }
    
protected:
    
    Canvas(int width = 800 , int height = 600);
    
    inline void _setDepth(int px , int py , Ldouble z) {
        int index = getIndex(px, py);
        _depthBuffer[index] = z;
    }
    
    inline Ldouble _getDepth(int px , int py) {
        return _depthBuffer[getIndex(px , py)];
    }
    
    inline int getIndex(int px , int py) const {
        return (int)((_width) * py + px);
    }
    
    inline int _getPX(Ldouble x) const {
        Ldouble startX = -1;
        Ldouble hw = _width / 2;
        int px = MathUtil::round((x - startX) * hw);
        return px;
    }
    
    inline int _getPY(Ldouble y) const {
        Ldouble startY = 1;
        Ldouble hh = -(_height / 2);
        int py = MathUtil::round((y - startY) * hh);
        return py;
    }
    
    int _width;
    
    int _height;
    
    static Canvas * s_pCanvas;
    
    Shader * _shader;
    
    int _bufferSize;
    
    DrawMode _drawMode;
    
    /**
     * -1 <= depth <= 1
     */
    Ldouble * _depthBuffer;
    
    SDL_Surface * _surface;
};

#endif /* Canvas_hpp */











