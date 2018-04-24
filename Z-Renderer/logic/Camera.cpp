//
//  Camera.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Camera.hpp"


Camera::Camera():
_horizontalAngle(0),
_verticalAngle(0),
_maxFov(130),
_minFov(20),
_farPlane(100),
_nearPlane(1),
_fieldOfView(50),
_maxPitch(80),
_viewportAspectRatio(4 / 3.0f),
_moveVelo(0.07),
_lookAt(0 , 0 , -1),
_headVec(0 , 1 , 0){
    
}


Camera::~Camera() {
    
}

void Camera::init() {
    
}

