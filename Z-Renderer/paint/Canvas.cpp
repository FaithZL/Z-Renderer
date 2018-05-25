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
#include "Box.hpp"
#include <iostream>
#include "Bitmap.hpp"
#include "Sprite3D.hpp"
#include "Ground.hpp"

using namespace std;

const int SCREEN_WIDTH     = 800;
const int SCREEN_HEIGHT    = 600;

Canvas * Canvas::s_pCanvas = nullptr;

Canvas::Canvas(int width , int height):
_surface(nullptr),
_width(width),
_height(height),
_drawMode(DrawMode::Frame),
_cullingMode(CullingMode::None),
_bufferSize(height * width),
_texture(nullptr),
_PC(true),
_normalFix(true),
_shader(nullptr) {
    _depthBuffer = new Ldouble[_bufferSize]();
    _shader = new Shader();
    
    auto ground = Ground::create();
    
//    auto sp = Sprite3D::create("nanosuit.obj");
//    auto sp = Sprite3D::create("planet.obj");
//    auto sp = Sprite3D::create("WusonOBJ.obj");
//    sp->setPositionZ(-1);
//    sp->setPositionY(-5);
//    _node.push_back(sp);
    
    _node.push_back(ground);
//    _node.push_back(Box::create());
}

Canvas * Canvas::getInstance() {
    if (s_pCanvas == nullptr) {
        s_pCanvas = new Canvas(SCREEN_WIDTH , SCREEN_HEIGHT);
    }
    return s_pCanvas;
}

void Canvas::clear() {
    memset(getPixels(), 0, sizeof(uint32_t) * _width * _height);
    std::fill(_depthBuffer, _depthBuffer + _bufferSize, MAXFLOAT);
}

void Canvas::update(double dt) {
    
    lock();
    
    clear();
    
    render(dt);
    
    unlock();
    
}

void Canvas::render(double dt) {
    for (int i = 0 ; i < _node.size() ; ++ i) {
        auto node = _node.at(i);
        node->draw(dt);
    }
}

void Canvas::lock() {
    SDL_LockSurface(_surface);
}

void Canvas::unlock() {
    SDL_UnlockSurface(_surface);
}

void Canvas::drawArray(const vector<Vertex> &verts) {
    for (int i = 0 ; i < verts.size() ; i = i + 3) {
        const Vertex &v1 = verts.at(i);
        const Vertex &v2 = verts.at(i + 1);
        const Vertex &v3 = verts.at(i + 2);
        processTriangle(v1 , v2, v3);
    }
}

void Canvas::drawElement(const vector<Vertex> &verts, const vector<int> &indice) {
    for (int i = 0 ; i < indice.size() ; i = i + 3) {
        const Vertex &v1 = verts.at(indice.at(i));
        const Vertex &v2 = verts.at(indice.at(i + 1));
        const Vertex &v3 = verts.at(indice.at(i + 2));
        processTriangle(v1 , v2 , v3);
    }
}

void Canvas::fixNormal(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3) const {
    const Vec3 &pos1 = v1.posTrans.getVec3();
    const Vec3 &pos2 = v2.posTrans.getVec3();
    const Vec3 &pos3 = v3.posTrans.getVec3();
    
    Vec3 v12 = pos2 - pos1;
    Vec3 v23 = pos3 - pos2;
    
    Vec3 normal = v12.cross(v23);
    
    v1.normal = normal;
    v2.normal = normal;
    v3.normal = normal;
}

bool Canvas::isCulling(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3) const {
    if (_cullingMode == None) {
        return false;
    }
    
    const Vec3 &pos1 = v1.posTrans.getVec3();
    const Vec3 &pos2 = v2.posTrans.getVec3();
    const Vec3 &pos3 = v3.posTrans.getVec3();
    
    Vec3 v12 = pos2 - pos1;
    Vec3 v23 = pos3 - pos2;
    
    Vec3 crs = v12.cross(v23);
    
    Vec3 pos = Camera::getInstance()->getPosition();
    Vec3 dir = pos1 - pos;
    
    if (_cullingMode == CCW) {
        return dir.dot(crs) < 0;
    } else {
        return dir.dot(crs) > 0;
    }

}

void Canvas::processTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    VertexOut vOut1 = handleVertex(v1);
    VertexOut vOut2 = handleVertex(v2);
    VertexOut vOut3 = handleVertex(v3);
    
    Triangle triangle(vOut1 , vOut2 , vOut3);
    vector<Triangle> triangleList = {triangle};

    doClippingInCvv(triangleList);
    
    for (int i = 0 ; i < triangleList.size(); ++i) {
        Triangle &tri = triangleList.at(i);
        _drawTriangle(tri.v1, tri.v2, tri.v3);
    }
}

void Canvas::_drawTriangle(VertexOut &vOut1, VertexOut &vOut2, VertexOut &vOut3) {
    transformToScrn(vOut1);
    transformToScrn(vOut2);
    transformToScrn(vOut3);
    
    if (_drawMode == Fill) {
        _triangleRasterize(vOut1, vOut2, vOut3);
    } else if (_drawMode == Frame) {
        lineBresenham(vOut1, vOut2);
        lineBresenham(vOut1, vOut3);
        lineBresenham(vOut3, vOut2);
    }
}

void Canvas::doClippingInCvv(vector<Triangle> &triList) const {
    _doClppingInCvvAgainstNearPlane(triList);
    _doClppingInCvvAgainstFarPlane(triList);
    _doClppingInCvvAgainstLeftPlane(triList);
    _doClppingInCvvAgainstRightPlane(triList);
    _doClppingInCvvAgainstTopPlane(triList);
    _doClppingInCvvAgainstBottomPlane(triList);
}

void Canvas::_doClppingInCvvAgainstLeftPlane(vector<Triangle> &triList) const {
    for (auto iter = triList.begin() ; iter != triList.end() ; /*do nothing*/ ) {
        Triangle &tri = *iter;
        Vec4 p1 = tri.v1.pos;
        Vec4 p2 = tri.v2.pos;
        Vec4 p3 = tri.v3.pos;
        bool bOut1 = p1.x < -p1.w;
        bool bOut2 = p2.x < -p2.w;
        bool bOut3 = p3.x < -p3.w;
        vector<VertexOut> vertice = {tri.v1 , tri.v2 , tri.v3};
        vector<bool> bList = {bOut1 , bOut2 , bOut3};
        int outNum = 0;
        for (int i = 0; i < bList.size() ; ++ i) {
            bool out = bList.at(i);
            outNum = outNum + (out ? 1 : 0);
        }
        if (outNum == 0) {
            // 如果没有点在外部，不处理
            ++ iter;
            continue;
        } else if (outNum == 2) {
            // 如果有两个顶点在外部，构造一个新三角形（修改旧三角形）
            // 储存外侧顶点的索引
            vector<int> indiceOut;
            // 内侧顶点的索引
            int inIdx = 0;
            // 找到在外侧的点的索引
            for (int i = 0; i < bList.size(); ++ i) {
                if (bList.at(i)) {
                    indiceOut.push_back(i);
                } else {
                    inIdx = i;
                }
            }
            VertexOut &vertIn = vertice.at(inIdx);
            // 遍历外侧顶点，插值生成新的顶点
            for (int i = 0; i < indiceOut.size() ; ++ i) {
                int index = indiceOut.at(i);
                VertexOut &vertOut = vertice.at(index);
                // ax + (cx - ax) * factor = newX
                // aw + (cw - aw) * factor = newW
                // newX = - newW
                Ldouble factor = (vertIn.pos.x + vertIn.pos.w) / (vertIn.pos.x - vertOut.pos.x + vertIn.pos.w - vertOut.pos.w);
                VertexOut vertNew = vertIn.interpolate(vertOut, factor);
                vertice[index] = vertNew;
            }
            tri.v1 = vertice[0];
            tri.v2 = vertice[1];
            tri.v3 = vertice[2];
            ++iter;
        } else if (outNum == 1) {
            // 如果有一个顶点在外部 ,构造一个梯形（修改旧三角形+添加一个新三角形）
            // 储存内侧顶点的索引
            vector<int> indiceIn;
            // 外侧顶点的索引
            int outIdx = 0;
            // 找到内侧的点的索引
            for (int i = 0; i < bList.size(); ++ i) {
                if (!bList.at(i)) {
                    indiceIn.push_back(i);
                } else {
                    outIdx = i;
                }
            }
            VertexOut &vertOut = vertice.at(outIdx);
            // 遍历内侧顶点，插值生成新的顶点，并添加三角形
            vector<VertexOut> vertNewList;
            for (int i = 0 ; i < indiceIn.size() ; ++ i) {
                // 生成对应新顶点
                int index = indiceIn.at(i);
                VertexOut vertIn = vertice.at(index);
                // ax + (cx - ax) * factor = newX
                // aw + (cw - aw) * factor = newW
                // newX = - newW
                Ldouble factor = (vertIn.pos.x + vertIn.pos.w) / (vertIn.pos.x - vertOut.pos.x + vertIn.pos.w - vertOut.pos.w);
                VertexOut vertNew = vertIn.interpolateEarly(vertOut, factor);
                vertNewList.push_back(vertIn);
                vertNewList.push_back(vertNew);
            }
            tri.v1 = vertNewList[0];
            tri.v2 = vertNewList[1];
            tri.v3 = vertNewList[2];
            
            Triangle triNew(vertNewList[1] , vertNewList[2] , vertNewList[3]);
            iter = triList.insert(iter + 1, triNew);
            ++iter;
        } else if (outNum == 3) {
            // 如果有三个顶点在外部，整体剔除
            iter = triList.erase(iter);
        }
    }
    return;
}

void Canvas::_doClppingInCvvAgainstRightPlane(vector<Triangle> &triList) const {
    
}

void Canvas::_doClppingInCvvAgainstTopPlane(vector<Triangle> &triList) const {
    
}

void Canvas::_doClppingInCvvAgainstBottomPlane(vector<Triangle> &triList) const {
    
}

void Canvas::_doClppingInCvvAgainstFarPlane(vector<Triangle> &triList) const {
    
}

void Canvas::_doClppingInCvvAgainstNearPlane(vector<Triangle> &triList) const {
    
    for (auto iter = triList.begin() ; iter != triList.end() ; /*do nothing*/ ) {
        Triangle &tri = *iter;
        Vec4 p1 = tri.v1.pos;
        Vec4 p2 = tri.v2.pos;
        Vec4 p3 = tri.v3.pos;
        bool bOut1 = p1.z < 0;
        bool bOut2 = p2.z < 0;
        bool bOut3 = p3.z < 0;
        vector<VertexOut> vertice = {tri.v1 , tri.v2 , tri.v3};
        vector<bool> bList = {bOut1 , bOut2 , bOut3};
        int outNum = 0;
        for (int i = 0; i < bList.size() ; ++ i) {
            bool out = bList.at(i);
            outNum = outNum + (out ? 1 : 0);
        }
        if (outNum == 0) {
            // 如果没有点在外部，不处理
            ++ iter;
            continue;
        } else if (outNum == 2) {
            // 如果有两个顶点在外部，构造一个新三角形（修改旧三角形）
            // 储存外侧顶点的索引
            vector<int> indiceOut;
            // 内侧顶点的索引
            int inIdx = 0;
            // 找到在外侧的点的索引
            for (int i = 0; i < bList.size(); ++ i) {
                if (bList.at(i)) {
                    indiceOut.push_back(i);
                } else {
                    inIdx = i;
                }
            }
            VertexOut &vertIn = vertice.at(inIdx);
            // 遍历外侧顶点，插值生成新的顶点
            for (int i = 0; i < indiceOut.size() ; ++ i) {
                int index = indiceOut.at(i);
                VertexOut &vertOut = vertice.at(index);
                Ldouble factor = (vertIn.pos.z - 0) / (vertIn.pos.z - vertOut.pos.z);
                VertexOut vertNew = vertIn.interpolate(vertOut, factor);
                vertice[index] = vertNew;
            }
            tri.v1 = vertice[0];
            tri.v2 = vertice[1];
            tri.v3 = vertice[2];
            ++iter;
        } else if (outNum == 1) {
            // 如果有一个顶点在外部 ,构造一个梯形（修改旧三角形+添加一个新三角形）
            // 储存内侧顶点的索引
            vector<int> indiceIn;
            // 外侧顶点的索引
            int outIdx = 0;
            // 找到内侧的点的索引
            for (int i = 0; i < bList.size(); ++ i) {
                if (!bList.at(i)) {
                    indiceIn.push_back(i);
                } else {
                    outIdx = i;
                }
            }
            VertexOut &vertOut = vertice.at(outIdx);
            // 遍历内侧顶点，插值生成新的顶点，并添加三角形
            vector<VertexOut> vertNewList;
            for (int i = 0 ; i < indiceIn.size() ; ++ i) {
                // 生成对应新顶点
                int index = indiceIn.at(i);
                VertexOut vertIn = vertice.at(index);
                Ldouble factor = (vertIn.pos.z - 0) / (vertIn.pos.z - vertOut.pos.z);
                VertexOut vertNew = vertIn.interpolateEarly(vertOut, factor);
                vertNewList.push_back(vertIn);
                vertNewList.push_back(vertNew);
            }
            tri.v1 = vertNewList[0];
            tri.v2 = vertNewList[1];
            tri.v3 = vertNewList[2];
            
            Triangle triNew(vertNewList[1] , vertNewList[2] , vertNewList[3]);
            iter = triList.insert(iter + 1, triNew);
            ++iter;
        } else if (outNum == 3) {
            // 如果有三个顶点在外部，整体剔除
            iter = triList.erase(iter);
        }
    }
}

void Canvas::_triangleRasterize(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3) {
    
    if (isCulling(v1, v2, v3)) {
        return;
    }
    
    VertexOut const * pVert1 = &v1;
    VertexOut const * pVert2 = &v2;
    VertexOut const * pVert3 = &v3;
    
    if (_normalFix) {
        fixNormal(v1, v2, v3);
    }
    
    vector<VertexOut const *> vector = {pVert1 , pVert2 , pVert3};
    
    sort(vector.begin(), vector.end() , [](const VertexOut * p1 , const VertexOut * p2)->bool {
        return p1->pos.y >= p2->pos.y;
    });
    
    pVert1 = vector.at(0);
    pVert2 = vector.at(1);
    pVert3 = vector.at(2);
    
    if (MathUtil::equal(pVert1->pos.y , pVert2->pos.y)) {
        // 平顶三角形
        _triangleBottomRasterize(*pVert1, *pVert2, *pVert3);
    } else if (MathUtil::equal(pVert2->pos.y , pVert3->pos.y)) {
        // 平底三角形
        _triangleTopRasterize(*pVert1, *pVert2, *pVert3);
    } else {
        Ldouble ty = pVert2->pos.y;
        Ldouble factor = (ty - pVert1->pos.y) / (pVert3->pos.y - pVert1->pos.y);
        VertexOut tVert = pVert1->interpolate(*pVert3 , factor);
        _triangleTopRasterize(*pVert1, tVert , *pVert2);
        _triangleBottomRasterize(*pVert2, tVert , *pVert3);
    }
}

void Canvas::_triangleTopRasterize(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3) {
    const VertexOut * pVert1 = &v1;
    const VertexOut * pVert2 = &v2;
    const VertexOut * pVert3 = &v3;
    vector<const VertexOut *> vector = {pVert1 , pVert2 , pVert3};
    // 根据纵坐标排序
    sort(vector.begin(), vector.end() , [](const VertexOut * p1 , const VertexOut * p2)->bool {
        return p1->pos.y >= p2->pos.y;
    });
    // 上面的顶点
    pVert1 = vector.at(0);
    pVert2 = vector.at(1);
    pVert3 = vector.at(2);
    
    int startPY = pVert1->pos.y;
    int endPY = pVert3->pos.y;
    
    int sign = endPY > startPY ? 1 : -1;
    
    for (int py = startPY ; py * sign <= sign * endPY ; py = py + sign) {
        Ldouble ld = 1.0f;
        Ldouble factor = (py - startPY) * ld / (endPY - startPY);
        VertexOut vertStart = pVert1->interpolate(*pVert2, factor);
        VertexOut vertEnd = pVert1->interpolate(*pVert3, factor);
        scanLineFill(vertStart , vertEnd , py);
    }
}

void Canvas::_triangleBottomRasterize(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3) {
    const VertexOut * pVert1 = &v1;
    const VertexOut * pVert2 = &v2;
    const VertexOut * pVert3 = &v3;
    vector<const VertexOut *> vector = {pVert1 , pVert2 , pVert3};
    // 根据纵坐标排序
    sort(vector.begin(), vector.end() , [](const VertexOut * p1 , const VertexOut * p2)->bool {
        return p1->pos.y >= p2->pos.y;
    });
    // 上面的顶点
    pVert1 = vector.at(0);
    pVert2 = vector.at(1);
    pVert3 = vector.at(2);
    
    int startPY = pVert3->pos.y;
    int endPY = pVert1->pos.y;
    
    int sign = endPY > startPY ? 1 : -1;
    
    for (int py = startPY ; py * sign < sign * endPY ; py = py + sign) {
        Ldouble ld = 1.0f;
        Ldouble factor = (py - startPY) * ld / (endPY - startPY);
        VertexOut vertStart = pVert3->interpolate(*pVert2, factor);
        VertexOut vertEnd = pVert3->interpolate(*pVert1, factor);
        scanLineFill(vertStart, vertEnd , py);
    };
}

void Canvas::scanLineFill(const VertexOut &v1, const VertexOut &v2 , int yIndex) {
    
    const VertexOut * pVert1 = &v1;
    const VertexOut * pVert2 = &v2;
    
    pVert1 = v1.pos.x > v2.pos.x ? &v2 : &v1;
    pVert2 = v1.pos.x < v2.pos.x ? &v2 : &v1;
    
    int startX = pVert1->pos.x;
    int endX = pVert2->pos.x;
    
    if (startX == endX) {
        Ldouble z = pVert1->getZ();
        if (isPassDepth(startX , yIndex , z)) {
            drawPixel(startX , yIndex , z , _shader->fs(*pVert1));
            return;
        }
    }
    for (int x = startX ; x <= endX ; ++ x) {
        Ldouble factor = (x - startX) * 1.0f / (endX - startX);
        Ldouble z = pVert1->interpolateZ(*pVert2 , factor);
        if (isPassDepth(x , yIndex, z)) {
            VertexOut fragment = pVert1->interpolate(*pVert2, factor);
            drawPixel(x , yIndex , z , _shader->fs(fragment));
        }
    }
}

VertexOut Canvas::handleVertex(const Vertex &vert) const {
    VertexOut vertOut = _shader->vs(vert);
    return vertOut;
}

void Canvas::transformToScrn(VertexOut &vert) const {
    // 透视除法将cvv坐标转化成Ndc坐标
    vert.toNdc();
    // 转换到屏幕坐标
    vert.pos.x = _getPX(vert.pos.x);
    vert.pos.y = _getPY(vert.pos.y);
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

void Canvas::lineBresenham(const VertexOut &vert1, const VertexOut &vert2) {
    const VertexOut * pVert1 = &vert1;
    const VertexOut * pVert2 = &vert2;
    
    int px1 = pVert1->pos.x;
    int py1 = pVert1->pos.y;
    
    int px2 = pVert2->pos.x;
    int py2 = pVert2->pos.y;
    
    int dx = abs(px2 - px1);
    int dy = abs(py2 - py1);
    
    if (dx >= dy) {
        if (px1 > px2) {
            swap(pVert1, pVert2);
        }
        int px1 = pVert1->pos.x;
        int py1 = pVert1->pos.y;
        
        int px2 = pVert2->pos.x;
        int py2 = pVert2->pos.y;
        
        int sign = py2 >= py1 ? 1 : -1;  //斜率[-1,1]
        int k = sign * dy * 2;
        int e = -dx * sign;
        
        for (int x = px1 , y = py1;x <= px2; ++x) {
            Ldouble factor = static_cast<Ldouble>((x - px1) * 1.0 / (px2 - px1));
            Ldouble z = pVert1->interpolateZ(*pVert2, factor);
            if (isPassDepth(x , y , z)) {
                VertexOut fragment = pVert1->interpolate(*pVert2, factor);
                drawPixel(x , y , z, _shader->fs(fragment));
            }
            e += k;
            if (sign * e > 0) {
                y += sign;
                e -= 2 * dx * sign;
            }
        }
    } else {
        if (py1 > py2) {
            swap(pVert1, pVert2);
        }
        int px1 = pVert1->pos.x;
        int py1 = pVert1->pos.y;
        
        int px2 = pVert2->pos.x;
        int py2 = pVert2->pos.y;
        
        int sign = px2 > px1 ? 1 : -1;  //斜率[-1,1]
        int k = sign * dx * 2;
        int e = -dy * sign;
        
        for (int x = px1 , y = py1; y <= py2 ; ++y) {
            Ldouble factor = static_cast<Ldouble>((y - py1) * 1.0 / (py2 - py1));
            Ldouble z = pVert1->interpolateZ(*pVert2, factor);
            if (isPassDepth(x , y , z)) {
                VertexOut fragment = pVert1->interpolate(*pVert2, factor);
                drawPixel(x , y , z, _shader->fs(fragment));
            }
            e += k;
            if (sign * e > 0) {
                x += sign;
                e -= 2 * dy * sign;
            }
        }
    }
}














