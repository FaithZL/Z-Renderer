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
#include <iostream>
#include "MathUtil.hpp"

using namespace std;

class Vec3 {

public:
    union {
        Ldouble u;
        Ldouble x;
    };
    
    union {
        Ldouble v;
        Ldouble y;
    };
    
    union {
        Ldouble w;
        Ldouble z;
    };
    
    Ldouble dot(const Vec3 &other) const;
    
    Vec3 cross(const Vec3 &other) const;
    
    inline void print() const {
        cout << this << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
    }
    
    Vec3(Ldouble x = 0 , Ldouble y = 0 , Ldouble z = 0);
    
    inline Vec3 getNormalize() const {
        Ldouble length = getLength();
        Vec3 ret = Vec3(x / length , y / length , z / length);
        return ret;
    }
    
    inline Ldouble getLength() const {
        auto ret = sqrt((x * x + y * y + z * z));
        return ret;
    }
    
    Vec3 interpolate(const Vec3 &other , Ldouble factor) const {
        auto ret = *this + (other - *this) * factor;
        return ret;
    }
    
    Vec3 operator * (Ldouble factor) const {
        return Vec3(x * factor , y * factor , z * factor);
    }
    
    Vec3 operator + (const Vec3 &other) const {
        return Vec3(x + other.x , y + other.y , z + other.z);
    }
    
    Vec3 operator - (const Vec3 &other) const {
        return Vec3(x - other.x , y - other.y , z - other.z);
    }
    
    Vec3 operator - () const {
        return Vec3(-x , -y , -z);
    }
    
    bool operator == (const Vec3 &other) const {
        return MathUtil::equal(x, other.x)
            && MathUtil::equal(y, other.y)
            && MathUtil::equal(z, other.z);
    }
};

class Vec4 {
    
public:
    union {
        Ldouble r;
        Ldouble x;
    };
    
    union {
        Ldouble g;
        Ldouble y;
    };
    
    union {
        Ldouble b;
        Ldouble z;
    };
    
    union {
        Ldouble a;
        Ldouble w;
    };
    
    Vec4(const Vec3 &vec , Ldouble w = 1.0f){
        init(vec.x , vec.y , vec.z , w);
    }
    
    inline void print() const {
        cout << this << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
        cout << "w = " << w << endl;
    }
    
    Vec4(Ldouble x = 0.0f , Ldouble y = 0.0f , Ldouble z = 0.0f , Ldouble w = 1.0f);
    
    void init(Ldouble x = 0.0f , Ldouble y = 0.0f , Ldouble z = 0.0f , Ldouble w = 1.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    
    Ldouble dot(const Vec4 &other) const;
    
    Vec4 cross(const Vec4 &other) const;
    
    Vec4 interpolate(const Vec4 &other , Ldouble factor) const {
        auto ret = *this + (other - *this) * factor;
        return ret;
    }
    
    Vec3 getVec3() const {
        Vec3 ret(x , y , z);
        return ret;
    }
    
    Vec3 get3DNormal() const {
        Vec3 ret(x / w , y / w , z / w);
        return ret;
    }
    
    Vec4 operator + (const Vec4 &other) const {
        return Vec4(x + other.x , y + other.y , z + other.z , w + other.w);
    }
    
    Vec4 operator - (const Vec4 &other) const {
        auto ret = Vec4(x - other.x , y - other.y , z - other.z , w - other.w);
        return ret;
    }
    
    Vec4 operator * (const Vec4 &other) const {
        auto ret = Vec4(x * other.x , y * other.y , z * other.z , w * other.w);
        return ret;
    }
    
    Vec4 operator * (Ldouble factor) const {
        auto ret = Vec4(x * factor , y * factor , z * factor , w * factor);
        return ret;
    }
    
    Vec4 operator - () const {
        return Vec4(-x , -y , -z , -w);
    }
    
    bool operator == (const Vec4 &other) const {
        return MathUtil::equal(x, other.x)
        && MathUtil::equal(y, other.y)
        && MathUtil::equal(z , other.z)
        && MathUtil::equal(w , other.w);
    }
};


class Vec2 {
    
public:
    union {
        Ldouble u;
        Ldouble x;
    };
    
    union {
        Ldouble v;
        Ldouble y;
    };
    
    Vec2(Ldouble u = 0 , Ldouble v = 0):
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

















