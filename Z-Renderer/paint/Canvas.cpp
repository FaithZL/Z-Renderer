//
//  Canvas.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Canvas.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

Canvas::Canvas(unsigned width , unsigned height):
_surface(nullptr),
_width(width),
_height(height),
_drawMode(DrawMode::Fill),
_bufferSize(height * width),
_shader(nullptr) {
    _depthBuffer = new Ldouble[_bufferSize]();
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
    
    Vec4 p1 = Vec4(-0.99 , -0.99 ,0);
    Vec4 p2 = Vec4(0 , 1 ,5);
    Vec4 p3 = Vec4(1 , 0, 10);
    
    Vertex v1(p1 , Color(1 , 0 , 0 , 0));
    Vertex v2(p2 , Color(0 , 1 , 0 , 0));
    Vertex v3(p3 , Color(0 , 0 , 1 , 0));
    
    Vertex v4(Vec4(- 0.5 , 0.8, 0) , Color(0 , 0 , 1 , 0));
    
    drawTriangle(v1 , v2 , v3);
    
//    drawTriangle(v1 , v2 , v4);
}

void Canvas::lock() {
    SDL_LockSurface(_surface);
}

void Canvas::unlock() {
    SDL_UnlockSurface(_surface);
}

void Canvas::drawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    if (_drawMode == Fill) {
        triangleRasterize(v1, v2, v3);
    } else if (_drawMode == Frame) {
        drawLineRasterize(v2, v1);
        drawLineRasterize(v2, v3);
        drawLineRasterize(v3, v1);
    }
}

void Canvas::triangleRasterize(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    
    const Vertex * pVert1 = &v1;
    const Vertex * pVert2 = &v2;
    const Vertex * pVert3 = &v3;
    vector<const Vertex *> vector = {pVert1 , pVert2 , pVert3};
    // 根据纵坐标排序
    sort(vector.begin(), vector.end() , [](const Vertex * p1 , const Vertex * p2)->bool {
        return p1->pos.y >= p2->pos.y;
    });

    pVert1 = vector.at(0);
    pVert2 = vector.at(1);
    pVert3 = vector.at(2);
    
    if (MathUtil::equal(pVert1->pos.y , pVert2->pos.y)) {
        // 平顶三角形
        _triangleBottomRasterize(*pVert1 , *pVert2 , *pVert3);
    } else if (MathUtil::equal(pVert2->pos.y , pVert3->pos.y)) {
        // 平底三角形
        _triangleTopRasterize(*pVert1 , *pVert2 , *pVert3);
    } else {
        Ldouble ty = pVert2->pos.y;
        Ldouble factor = (ty - pVert1->pos.y) / (pVert3->pos.y - pVert1->pos.y);
        Vertex tVert = pVert1->interpolate(*pVert3 , factor);
        _triangleTopRasterize(*pVert1, tVert , *pVert2);
        _triangleBottomRasterize(*pVert2, tVert , *pVert3);
    }
    
    return;
}

void Canvas::_triangleTopRasterize(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    const Vertex * pVert1 = &v1;
    const Vertex * pVert2 = &v2;
    const Vertex * pVert3 = &v3;
    vector<const Vertex *> vector = {pVert1 , pVert2 , pVert3};
    // 根据纵坐标排序
    sort(vector.begin(), vector.end() , [](const Vertex * p1 , const Vertex * p2)->bool {
        return p1->pos.y >= p2->pos.y;
    });
    // 上面的顶点
    pVert1 = vector.at(0);
    pVert2 = vector.at(1);
    pVert3 = vector.at(2);
    
    int startPY = _getPY(pVert1->pos.y);
    int endPY = _getPY(pVert3->pos.y);
    
    int sign = endPY > startPY ? 1 : -1;
    
    for (int py = startPY ; py * sign <= sign * endPY ; py = py + sign) {
        Ldouble ld = 1.0f;
        Ldouble factor = (py - startPY) * ld / (endPY - startPY);
        Vertex vertStart = pVert1->interpolate(*pVert2, factor);
        Vertex vertEnd = pVert1->interpolate(*pVert3, factor);

        drawLineRasterize(vertStart, vertEnd);
    }
}

void Canvas::_triangleBottomRasterize(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    const Vertex * pVert1 = &v1;
    const Vertex * pVert2 = &v2;
    const Vertex * pVert3 = &v3;
    vector<const Vertex *> vector = {pVert1 , pVert2 , pVert3};
    // 根据纵坐标排序
    sort(vector.begin(), vector.end() , [](const Vertex * p1 , const Vertex * p2)->bool {
        return p1->pos.y >= p2->pos.y;
    });
    // 上面的顶点
    pVert1 = vector.at(0);
    pVert2 = vector.at(1);
    pVert3 = vector.at(2);
    
    int startPY = _getPY(pVert3->pos.y);
    int endPY = _getPY(pVert1->pos.y);
    
    int sign = endPY > startPY ? 1 : -1;
    
    for (int py = startPY ; py * sign < sign * endPY ; py = py + sign) {
        Ldouble ld = 1.0f;
        Ldouble factor = (py - startPY) * ld / (endPY - startPY);
        Vertex vertStart = pVert3->interpolate(*pVert2, factor);
        Vertex vertEnd = pVert3->interpolate(*pVert1, factor);
        drawLineRasterize(vertStart, vertEnd);
    }
}

void Canvas::putPixel(int px , int py , const Color &color) {
    bool outX = px < 0 || px > _width;
    bool outY = py < 0 || py > _height;
    if (outX || outY) {
        return;
    }
    unsigned index = getIndex(px, py);
    auto pixels = getPixels();
    pixels[index] = color.uint32();
}

void Canvas::drawLineRasterize(const Vertex &vert1, const Vertex &vert2) {
    
    const Vertex * pVert1 = &vert1;
    const Vertex * pVert2 = &vert2;
    
    Vec4 pos1 = pVert1->pos;
    Vec4 pos2 = pVert2->pos;
    
    int px1 = _getPX(pos1.x);
    int py1 = _getPY(pos1.y);
    
    int px2 = _getPX(pos2.x);
    int py2 = _getPY(pos2.y);
 
    int dx = abs(px2 - px1);
    int dy = abs(py2 - py1);
    if (dx >= dy) {
        //以dx=1作为步长，否则会出现断点
        if (px1 > px2) {
            swap(pVert1, pVert2);
        }
        Vec4 pos1 = pVert1->pos;
        Vec4 pos2 = pVert2->pos;
        
        int px1 = _getPX(pos1.x);
        int py1 = _getPY(pos1.y);
        Ldouble z1 = pos1.z;
        Color color1 = pVert1->color;
        
        int px2 = _getPX(pos2.x);
        int py2 = _getPY(pos2.y);
        Ldouble z2 = pos2.z;
        Color color2 = pVert2->color;
        
        int sign = py2 >= py1 ? 1 : -1;  //斜率[-1,1]
        int k = sign * dy * 2;
        int e = -dx * sign;
        
        if (px2 == px1) {
            drawPixel(px1, py1, z1, color1);
        }
        
        for (int x = px1 , y = py1;x <= px2; ++x) {
            Ldouble factor = static_cast<Ldouble>((x - px1) * 1.0 / (px2 - px1));
            Ldouble z = MathUtil::interpolate(z1 , z2, factor);
            Color color = color1.interpolate(color2, factor);
            drawPixel(x , y , z, color);
            e += k;
            if (sign * e > 0) {
                y += sign;
                e -= 2 * dx * sign;
            }
        }
    } else {
        //以dy = 1 作为步长
        if (py1 > py2) {
            swap(pVert1, pVert2);
        }
        
        Vec4 pos1 = pVert1->pos;
        Vec4 pos2 = pVert2->pos;
        
        int px1 = _getPX(pos1.x);
        int py1 = _getPY(pos1.y);
        Ldouble z1 = pos1.z;
        Color color1 = pVert1->color;
        
        int px2 = _getPX(pos2.x);
        int py2 = _getPY(pos2.y);
        Ldouble z2 = pos2.z;
        Color color2 = pVert2->color;
        
        int sign = px2 > px1 ? 1 : -1;
        int k = sign * dx * 2;
        int e = -dy * sign;
        if (px2 == px1) {
            drawPixel(px1, py1, z1, color1);
        }
        for (int x = px1 , y = py1; y <= py2 ; ++y) {
            Ldouble factor = static_cast<Ldouble>((x - px1) * 1.0 / (px2 - px1));
            Ldouble z = MathUtil::interpolate(z1 , z2, factor);
            Color color = color1.interpolate(color2, factor);
            drawPixel(x , y , z, color);
            e += k;
            if (sign * e > 0) {
                x += sign;
                e -= 2 * dy * sign;
            }
        }
    }
}

void Canvas::drawPointRasterize(const Vertex &vert) {
    drawPointRasterize(vert.pos.x, vert.pos.y, vert.pos.z, vert.color);
}

void Canvas::drawPointRasterize(Ldouble x , Ldouble y , Ldouble z , const Color &color) {
    bool outX = x > 1 || x < -1;
    bool outY = y > 1 || y < -1;
    bool outZ = z > 1 || z < -1;
    
    if (outX || outY || outZ) {
        return;
    }
    
    Ldouble px = _getPX(x);
    Ldouble py = _getPY(y);
    
    drawPixel(px, py, z, color);
}












