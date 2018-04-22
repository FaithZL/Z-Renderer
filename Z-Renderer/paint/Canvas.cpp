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

using namespace std;

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
    Vertex v1(Vec3(-1 , -1 ,-1) , Color(1 , 0 , 0 , 0));
    Vertex v2(Vec3(0 , 1 , 1) , Color(0 , 1 , 0 , 0));
    Vertex v3(Vec3(1 , -0.5 , 1) , Color(0 , 0 , 1 , 0));

    drawLineRasterize(v2, v1);
    drawLineRasterize(v2, v3);
    drawLineRasterize(v3, v1);
    
    drawTriangleRasterize(v1 , v2 , v3);
}

void Canvas::lock() {
    SDL_LockSurface(_surface);
}

void Canvas::unlock() {
    SDL_UnlockSurface(_surface);
}

void Canvas::drawTriangleRasterize(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    
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
        _drawTriangleTopRasterize(*pVert1 , *pVert2 , *pVert3);
    } else if (MathUtil::equal(pVert2->pos.y , pVert3->pos.y)) {
        // 平底三角形
        _drawTriangleBottomRasterize(*pVert1 , *pVert2 , *pVert3);
    } else {
        double my = pVert2->pos.y;
        // 求直线方程
        double startX = pVert3->pos.x;
        double startY = pVert3->pos.y;
    }
    
    return;
}

void Canvas::_drawTriangleTopRasterize(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    
}

void Canvas::_drawTriangleBottomRasterize(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    
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
    
    Vec3 pos1 = pVert1->pos;
    Vec3 pos2 = pVert2->pos;
    
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
        Vec3 pos1 = pVert1->pos;
        Vec3 pos2 = pVert2->pos;
        
        int px1 = _getPX(pos1.x);
        int py1 = _getPY(pos1.y);
        double z1 = pos1.z;
        Color color1 = pVert1->color;
        
        int px2 = _getPX(pos2.x);
        int py2 = _getPY(pos2.y);
        double z2 = pos2.z;
        Color color2 = pVert2->color;
        
        int sign = py2 >= py1 ? 1 : -1;  //斜率[-1,1]
        int k = sign * dy * 2;
        int e = -dx * sign;
        for (int x = px1 , y = py1;x <= px2; ++x) {
            double factor = static_cast<double>((x - px1) * 1.0 / (px2 - px1));
            double z = MathUtil::interpolate(z1 , z2, factor);
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
        
        Vec3 pos1 = pVert1->pos;
        Vec3 pos2 = pVert2->pos;
        
        int px1 = _getPX(pos1.x);
        int py1 = _getPY(pos1.y);
        double z1 = pos1.z;
        Color color1 = pVert1->color;
        
        int px2 = _getPX(pos2.x);
        int py2 = _getPY(pos2.y);
        double z2 = pos2.z;
        Color color2 = pVert2->color;
        
        int sign = px2 > px1 ? 1 : -1;
        int k = sign * dx * 2;
        int e = -dy * sign;
        for (int x = px1 , y = py1; y <= py2 ; ++y) {
            double factor = static_cast<double>((x - px1) * 1.0 / (px2 - px1));
            double z = MathUtil::interpolate(z1 , z2, factor);
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

void Canvas::drawPointRasterize(double x , double y , double z , const Color &color) {
    bool outX = x > 1 || x < -1;
    bool outY = y > 1 || y < -1;
    bool outZ = z > 1 || z < -1;
    
    if (outX || outY || outZ) {
        return;
    }
    
    double px = _getPX(x);
    double py = _getPY(y);
    
    drawPixel(px, py, z, color);
}












