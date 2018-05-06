//
//  Camera.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Camera.hpp"
#include "assert.h"


Camera::Camera():
_horizontalAngle(0),
_verticalAngle(0),
_maxFov(130),
_minFov(20),
_farPlane(60),
_nearPlane(1),
_fieldOfView(60),
_maxPitch(80),
_viewportAspectRatio(4 / 3.0f),
_moveVelo(0.07),
_lookAt(0 , 0 , -1),
_headVec(0 , 1 , 0){
//    _position = Vec4(0 ,0 , 0);
}

Camera * Camera::s_pCamera = nullptr;

Camera * Camera::getInstance() {
    if (s_pCamera == nullptr) {
        s_pCamera = new Camera();
        s_pCamera->init();
    }
    return s_pCamera;
}

Mat4 Camera::getViewMat() const {
    Mat4 ret;
    ret = Mat4::translate(-_position) * getCurDirectionMat();
    return ret;
}

Mat4 Camera::getProjectionMat() const {
    Mat4 ret = Mat4::perspective(MathUtil::angle2radian(_fieldOfView), _viewportAspectRatio, _nearPlane , _farPlane);
    return ret;
}

Mat4 Camera::getViewProjectionMat() const {
    // todo
    Mat4 ret;
    ret = getProjectionMat() * getViewMat();
    return ret;
}

Mat4 Camera::getCurDirectionMat() const {
    Mat4 vertical = Mat4::rotateX(MathUtil::angle2radian(_verticalAngle));
    Mat4 horizontal = Mat4::rotateY(MathUtil::angle2radian(_horizontalAngle));
    Mat4 ret = vertical * horizontal;
    return ret;
}

void Camera::initLookAt(Vec4 lookAt){
    assert(!(lookAt == _position));
    Vec3 dir = (lookAt - _position).getVec3().getNormalize();
    _verticalAngle = MathUtil::radian2angle(atan(dir.y / dir.z));
    _horizontalAngle = MathUtil::radian2angle(atan2(dir.x , dir.z));
    _normalizeAngle();
}

Vec4 Camera::forward() {
    Vec4 ret;
    return ret;
}

Vec4 Camera::up() {
    Vec4 ret;
    return ret;
}

Vec4 Camera::right() {
    Vec4 ret;
    return ret;
}

Camera::~Camera() {
    
}

void Camera::init() {
    
}














