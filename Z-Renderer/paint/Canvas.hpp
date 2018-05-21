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
#include <vector>
#include "Vertex.hpp"
#include "Color.hpp"
#include "Camera.hpp"
#include "Node.hpp"
#include "Texture.hpp"

enum DrawMode {
    Frame,
    Fill
};

enum CullingMode {
    None,  //不处理
    CCW,  // 逆时针
    CW,  //顺时针
};

class Canvas {
public:
    
    void clear();
    
    static Canvas * getInstance();
    
    void render(double dt);
    
    void lock();
    
    void update(double dt);
    
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
    
    void drawArray(const vector<Vertex> &verts);
    
    void drawElement(const vector<Vertex> &verts , const vector<int> &indice);
    
    bool isCulling(const VertexOut &v1 , const VertexOut &v2 , const VertexOut &v3) const;
    
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
    
    bool isClip(const Vec4 &pos) const {
        return pos.x < -pos.w || pos.x > pos.w
            || pos.y < -pos.w || pos.y > pos.w
            || pos.z < 0 || pos.z > pos.w;
    }
    
    inline bool isPassDepth(int px , int py , Ldouble z) {
        int index = getIndex(px , py);
        return z <= _depthBuffer[index];
    }
    
    inline void setShader(const Shader * shader) {
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
    
    Texture const * getTexture() const {
        return _texture;
    }
    
    inline void setTexture(const Texture * texture) {
        _texture = texture;
    }
    
    inline void setCullingMode(CullingMode mode) {
        _cullingMode = mode;
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
    
    CullingMode _cullingMode;
    
    //perspective correction 透视校正
    bool _PC;
    
    std::vector<Node *> _node;
    
    static Canvas * s_pCanvas;
    
    Shader const * _shader;
    
    int _bufferSize;
    
    DrawMode _drawMode;
    
    Texture const * _texture;
    
    /**
     * 深度缓冲，储存Z坐标的倒数，用于深度测试
     */
    Ldouble * _depthBuffer;
    
    SDL_Surface * _surface;
};

#endif /* Canvas_hpp */











