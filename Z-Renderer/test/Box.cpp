//
//  Box.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/3.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Box.hpp"
#include "Camera.hpp"
#include "Canvas.hpp"

Box::Box():
_shader(nullptr) {
    
}

Box::~Box() {
    
}

void Box::updateTransform() {
    _rotate.y += 1;
    if (_rotate.y > 360) {
        _rotate.y -= 360;
    }
    Mat4 r = Mat4::rotateY(MathUtil::angle2radian(_rotate.y));
    Mat4 model = r * Mat4::scale(_scale) * Mat4::translate(_position);
    auto camera = Camera::getInstance();
    auto v = camera->getViewMat();
    auto p = camera->getProjectionMat();
    _shader->setMvp(model , v, p);
}

void Box::init() {
    
//    _vertice.resize(36);
    
    _shader = Shader::create();
    
    Vertex v1 = Vertex(Vec3(1 , 1, 1), Color(1 , 0 , 0 , 0));
    Vertex v2 = Vertex(Vec3(-1 , 1, 1), Color(0 , 1 , 0 , 0));
    Vertex v3 = Vertex(Vec3(-1 , -1, 1), Color(0 , 0 , 1 , 0));
    Vertex v4 = Vertex(Vec3(1 , -1, 1), Color(1 , 0 , 0 , 0));
    Vertex v1_ = Vertex(Vec3(1 , 1, -1), Color(0 , 1 , 0 , 0));
    Vertex v2_ = Vertex(Vec3(-1 , 1, -1), Color(0 , 0 , 1 , 0));
    Vertex v3_ = Vertex(Vec3(-1 , -1, -1), Color(1 , 0 , 0 , 0));
    Vertex v4_ = Vertex(Vec3(1 , -1, -1), Color(1 , 0 , 1 , 0));
    
    _position = Vec3(0 , 0 , -3);
//    _scale = Vec3(0.1 , 0.2);
    
    _vertice.resize(36);
    
    
    // 前面
    _vertice[0] = v1;
    _vertice[1] = v2;
    _vertice[2] = v3;
    
    _vertice[3] = v1;
    _vertice[4] = v3;
    _vertice[5] = v4;
    
    //后面
    _vertice[6] = v1_;
    _vertice[7] = v2_;
    _vertice[8] = v3_;
    
    _vertice[9] = v1_;
    _vertice[10] = v3_;
    _vertice[11] = v4_;
    
    //左面
    _vertice[12] = v2;
    _vertice[13] = v3;
    _vertice[14] = v3_;
    
    _vertice[15] = v3_;
    _vertice[16] = v2_;
    _vertice[17] = v2;
    
    //右面
    _vertice[18] = v1;
    _vertice[19] = v4;
    _vertice[20] = v4_;

    _vertice[21] = v1_;
    _vertice[22] = v4_;
    _vertice[23] = v1; 

    //上面
    _vertice[24] = v1;   
    _vertice[25] = v2;   
    _vertice[26] = v1_;

    _vertice[27] = v1_;   
    _vertice[28] = v2_;   
    _vertice[29] = v2;

    //下面   
    _vertice[30] = v3;   
    _vertice[31] = v4;   
    _vertice[32] = v3_;   

    _vertice[33] = v3_;   
    _vertice[34] = v4_;   
    _vertice[35] = v4;   

}

void Box::draw(Ldouble dt) {
    updateTransform();
    auto canvas = Canvas::getInstance();
    canvas->setShader(_shader);
    for (int i = 0; i < 36; i += 3) {
//        i = 18;
        canvas->drawTriangle(_vertice[i], _vertice[i+1], _vertice[i+2]);
//        if (i > 1) {
//            break;
//        }
//        break;
    }
}









