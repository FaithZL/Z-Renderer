//
//  Vec.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Vec_hpp
#define Vec_hpp

#include "Macro.h"
#include <cmath>
#include "MathUtil.hpp"

class Vec3 {
    
public:
    Ldouble x;
    Ldouble y;
    Ldouble z;
    
    Vec3(Ldouble x = 0.0f , Ldouble y = 0.0f , Ldouble z = 0.0f);
    
    Ldouble length() const;
    
    inline Vec3 getNormalize() const {
        Ldouble length = getLength();
        Vec3 ret = Vec3(x / length , y / length , z / length);
        return ret;
    }
    
    inline Ldouble getLength() const {
        auto ret = sqrt((x * x + y * y + z * z));
        return ret;
    }
    
    Ldouble dot(const Vec3 &other) const;
    
    Vec3 cross(const Vec3 &other) const;
    
    Vec3 interpolate(const Vec3 &other , Ldouble factor) const ;
    
    Vec3 operator + (const Vec3 &other) const {
        return Vec3(x + other.x , y + other.y , z + other.z);
    }
    
    Vec3 operator - (const Vec3 &other) const {
        auto ret = Vec3(x - other.x , y - other.y , z - other.z);
        return ret;
    }
    
    Vec3 operator * (const Vec3 &other) const {
        auto ret = Vec3(x * other.x , y * other.y , z * other.z);
        return ret;
    }
    
    Vec3 operator * (Ldouble factor) const {
        auto ret = Vec3(x * factor , y * factor , z * factor);
        return ret;
    }
    
    Vec3 operator - () const {
        return Vec3(-x , -y , -z);
    }
    
    bool operator == (const Vec3 &other) const {
        return MathUtil::equal(x, other.x)
            && MathUtil::equal(y, other.y)
            && MathUtil::equal(z , other.z);
    }
};

class Vec2 {
    
public:
    Ldouble u;
    Ldouble v;
    
    Vec2(Ldouble u , Ldouble v):
    u(u),
    v(v) {
        
    }
    
    Vec2 interpolate(const Vec2 &other , Ldouble factor) const {
        auto ret = *this + (other - *this) * factor;
        return ret;
    }
    
    Vec2 operator * (Ldouble factor) const {
        return Vec2(u * factor , v * factor);
    }
    
    Vec2 operator + (const Vec2 &other) const {
        return Vec2(u + other.u , v + other.v);
    }
    
    Vec2 operator - (const Vec2 &other) const {
        return Vec2(u - other.u , v - other.v);
    }
    
    Vec2 operator - () const {
        return Vec2(-u , -v);
    }
    
    bool operator == (const Vec2 &other) const {
        return MathUtil::equal(u, other.u)
            && MathUtil::equal(v, other.v);
    }
};

#endif /* Vec_hpp */

















