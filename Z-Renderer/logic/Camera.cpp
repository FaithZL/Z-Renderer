//
//  Camera.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Camera.hpp"
#include "assert.h"
#include "Canvas.hpp"


Camera::Camera():
_yaw(0),
_pitch(0),
_maxFov(130),
_minFov(20),
_farPlane(10),
_nearPlane(1),
_fovy(70),
_maxPitch(80),
_moveVelo(0.07),
_lookAt(0 , 0 , -1),
_headVec(0 , 0 , 0){
    _position = Vec3(0 ,0 , 3);
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
    Ldouble width = Canvas::getInstance()->getWidth();
    Ldouble height = Canvas::getInstance()->getHeight();
    Mat4 ret = Mat4::perspective(MathUtil::angle2radian(_fovy), width / height, _nearPlane , _farPlane);
    return ret;
}

Mat4 Camera::getViewProjectionMat() const {
    // todo
    Mat4 ret;
    ret = getViewMat() * getProjectionMat();
    return ret;
}

Mat4 Camera::getCurDirectionMat() const {
    Mat4 vertical = Mat4::rotateX(MathUtil::angle2radian(-_pitch));
    Mat4 horizontal = Mat4::rotateY(MathUtil::angle2radian(_yaw));
    Mat4 ret = horizontal * vertical ;
    return ret;
}

void Camera::initLookAt(Vec3 lookAt){
    assert(!(lookAt == _position));
    Vec3 dir = (lookAt - _position).getNormalize();
    _pitch = MathUtil::radian2angle(atan(dir.y / dir.z));
    _yaw = MathUtil::radian2angle(atan2(dir.x , dir.z));
    _normalizeAngle();
}

Vec3 Camera::forward() {
    Vec3 ret;
    Vec4 temp = getCurDirectionMat().getInverseMat().transform(Vec4(0 , 0 , -1 , 0));
    return temp.getVec3();
}

Vec3 Camera::up() {
    Vec3 ret;
    Vec4 temp = getCurDirectionMat().getInverseMat().transform(Vec4(0 , 1 , 0 , 0));
    return temp.getVec3();
}

Vec3 Camera::right() {
    Vec3 ret;
    Vec4 temp = getCurDirectionMat().getInverseMat().transform(Vec4(1 , 0 , 0 , 0));
    return temp.getVec3();
}

Camera::~Camera() {
    
}

void Camera::init() {
//    initLookAt(_lookAt);
}














