//
//  Vec.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Vec.hpp"

Vec3::Vec3(Ldouble x , Ldouble y ,Ldouble z):
x(x),
y(y),
z(z){
    
}

Vec3 Vec3::reflect(const Vec3 &normal) const {
    Vec3 I = getNormalize();
    float tmp = 2.f * I.dot(normal);
    return I - (normal * tmp);
}

Ldouble Vec3::dot(const Vec3 &other) const {
    return x * other.x + y * other.y + z *other.z;
}

Vec3 Vec3::cross(const Vec3 &other) const {
    Ldouble X = y * other.z - z * other.y;
    Ldouble Y = z * other.x - x * other.z;
    Ldouble Z = x * other.y - y * other.x;
    return Vec3(X , Y , Z);
}

Vec4::Vec4(Ldouble x , Ldouble y ,Ldouble z , Ldouble w):
x(x),
y(y),
z(z),
w(w){
    
}

Ldouble Vec4::dot(const Vec4 &other) const {
    return x * other.x + y * other.y + z *other.z;
}

Vec4 Vec4::cross(const Vec4 &other) const {
    Ldouble X = y * other.z - z * other.y;
    Ldouble Y = z * other.x - x * other.z;
    Ldouble Z = x * other.y - y * other.x;
    return Vec4(X , Y , Z , 0);
}











