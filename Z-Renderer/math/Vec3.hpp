//
//  Vec.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Vec_hpp
#define Vec_hpp

#include "ZMath.h"


class Vec3 {
    
public:
    double x;
    double y;
    double z;
    
    Vec3(double x = 0.0f , double y = 0.0f , double z = 0.0f);
    
    double length() const;
    
    double normalize() const;
    
    double dot(Vec3 &other) const;
    
    Vec3 cross(Vec3 &other) const;
    
    Vec3 interpolate(Vec3 &other , double factor) const ;
    
    Vec3 operator + (Vec3 &other) const {
        return Vec3(x + other.x , y + other.y , z + other.z);
    }
    
    Vec3 operator - (Vec3 &other) const {
        return Vec3(x - other.x , y - other.y , z - other.z);
    }
    
    Vec3 operator * (Vec3 &other) const {
        return Vec3(x * other.x , y * other.y , z * other.z);
    }
    
    bool operator == (Vec3 &other) const {
        return equal(x, other.x)
            && equal(y, other.y)
            && equal(z , other.z);
    }
};

#endif /* Vec_hpp */











