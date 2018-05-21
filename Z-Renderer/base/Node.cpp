//
//  Node.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Node.hpp"
#include "Camera.hpp"

void Node::updateTransform(double dt) {
    Mat4 r = Mat4::rotateY(MathUtil::angle2radian(_rotate.y));
    Mat4 model = r * Mat4::scale(_scale) * Mat4::translate(_position);
    auto camera = Camera::getInstance();
    auto v = camera->getViewMat();
    auto p = camera->getProjectionMat();
    _shader->setMvp(model , v, p);
}
