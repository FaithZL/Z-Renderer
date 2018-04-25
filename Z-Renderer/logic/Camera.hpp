//
//  Camera.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Mat4.hpp"

class Camera : public Node {
    
public:
    
    virtual ~Camera();
    
    void init();
    
    static Camera * getInstance();
    
    Mat4 getViewMat() const;
    
    Mat4 getProjectionMat() const;
    
    /**
     The combined camera transformation matrix, including perspective projection.
     
     This is the complete matrix to use in the vertex shader.
     */
    Mat4 getViewProjectionMat() const;
    
    inline void setAspectRatio(Ldouble r){
        _viewportAspectRatio = r;
    }
    
    inline void setNearAndFarPlane(Ldouble n , Ldouble f){
        setNearPlane(n);
        setFarPlane(f);
    }
    
    void initLookAt(Vec3 lookAt);
    
    
    Mat4 getCurDirectionMat() const;
    
    inline void offsetDirection(Ldouble verticalAngle , Ldouble horizontalAngle){
        _verticalAngle += verticalAngle;
        _horizontalAngle += horizontalAngle;
        _normalizeAngle();
    }
    
    inline Ldouble getNearPlane(){
        return _nearPlane;
    }
    
    inline void setNearPlane(Ldouble val){
        _nearPlane = val;
    }
    
    inline Ldouble getFarPlane(){
        return _farPlane;
    }
    
    inline void setFarPlane(Ldouble val){
        _farPlane = val;
    }
    
    inline void setMoveVelo(Ldouble val){
        _moveVelo = val;
    }
    
    inline Ldouble getMoveVelo(){
        return _moveVelo;
    }
    
    
    /**
     A unit vector representing the direction the camera is facing in world coordinate system
     */
    Vec3 forward();
    
    /**
     A unit vector representing the direction out of the top of the camera in world coordinate system
     */
    Vec3 up();
    
    /**
     A unit vector representing the direction to the right of the camera in world coordinate system
     */
    Vec3 right();
    
    inline void offsetPosition(Vec3 moveVec){
        _position = _position + moveVec;
    }
    
    /**
     The vertical viewing angle of the camera, in degrees.
     
     Determines how "wide" the view of the camera is. Large angles appear to be zoomed out,
     as the camera has a wide view. Small values appear to be zoomed in, as the camera has a
     very narrow view.
     
     The value must be between 0 and 180.
     */
    inline Ldouble getFieldOfView(){
        return _fieldOfView;
    }
    
    inline void setFieldOfView(Ldouble fov){
        if (fov > _maxFov) {
            _fieldOfView = _maxFov;
        }else if(fov < _minFov){
            _fieldOfView = _minFov;
        }
    }
    
protected:
    
    Camera();
    
    static Camera * s_pCamera;
    
    inline void _normalizeAngle(){
        _horizontalAngle = fmodf(_horizontalAngle, 360.0f);
        //fmodf can return negative values, but this will make them all positive
        if(_horizontalAngle < 0.0f){
            _horizontalAngle += 360.0f;
        }
        
        if(_verticalAngle > _maxPitch){
            _verticalAngle = _maxPitch;
        }
        else if(_verticalAngle < -_maxPitch){
            _verticalAngle = -_maxPitch;
        }
    }
    
    Vec3 _lookAt;
    
    Vec3 _headVec;
    
    Ldouble _verticalAngle = 0;
    
    Ldouble _horizontalAngle = 0;
    
    Ldouble _maxPitch = 150;
    
    Ldouble _nearPlane;
    
    Ldouble _farPlane;
    
    Ldouble _moveVelo = 10;
    
    Ldouble _minFov;
    
    Ldouble _viewportAspectRatio;
    
    // base of angle (horizontal)
    Ldouble _fieldOfView;
    
    Ldouble _maxFov;
};

#endif /* Camera_hpp */













