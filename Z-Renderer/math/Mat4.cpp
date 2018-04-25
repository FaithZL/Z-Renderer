//
//  Mat4.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Mat4.hpp"


Mat4 Mat4::operator*(const Mat4 &other) const {
    
    Ldouble values[16];
    for(int index = 0; index < 16; index++) {
        int i = index / 4;
        int j = index % 4;
        values[index] = m[i*4] * other.m[j]
        + m[i*4 + 1] * other.m[1*4 + j]
        + m[i*4 + 2] * other.m[2*4 + j]
        + m[i*4 + 3] * other.m[3*4 + j];
    }
    return Mat4(values);
    
}

Mat4 Mat4::perspective(Ldouble radian, Ldouble ratio, Ldouble znear, Ldouble zfar) {
    float height = 1 / tan(radian / 2);
    float width = height / ratio;
    float values[16] = {
        width,  0,      0,                                  0,
        0,      height, 0,                                  0,
        0,      0,      zfar / (zfar - znear),              1,
        0,      0,      (znear * zfar) / (znear - zfar),    0,
    };
    Mat4 ret(values);
    return ret;
}

Vec3 Mat4::transform(const Vec3 &vec) const {
    Ldouble x = vec.x * m[0*4 + 0] + vec.y * m[1*4 + 0] + vec.z * m[2*4 + 0] + m[3*4 + 0];
    Ldouble y = vec.x * m[0*4 + 1] + vec.y * m[1*4 + 1] + vec.z * m[2*4 + 1] + m[3*4 + 1];
    Ldouble z = vec.x * m[0*4 + 2] + vec.y * m[1*4 + 2] + vec.z * m[2*4 + 2] + m[3*4 + 2];
    Ldouble w = vec.x * m[0*4 + 3] + vec.y * m[1*4 + 3] + vec.z * m[2*4 + 3] + m[3*4 + 3];
    return Vec3(x/w, y/w, z/w);
}

Mat4 Mat4::scale(const Vec3 &v) {
    return scale(v.x, v.y, v.z);
}

Mat4 Mat4::scale(Ldouble x, Ldouble y, Ldouble z) {
    Ldouble values[16] = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1,
    };
    return Mat4(values);
}

Mat4 Mat4::rotateX(Ldouble radian) {
    Ldouble s = sinf(radian);
    Ldouble c = cosf(radian);
    Ldouble values[16] = {
        1, 0,  0, 0,
        0, c,  s, 0,
        0, -s, c, 0,
        0, 0,  0, 1,
    };
    return Mat4(values);
}

Mat4 Mat4::rotateY(Ldouble radian) {
    Ldouble s = sinf(radian);
    Ldouble c = cosf(radian);
    Ldouble values[16] = {
        c, 0, -s, 0,
        0, 1, 0,  0,
        s, 0, c,  0,
        0, 0, 0,  1,
    };
    return Mat4(values);
}

Mat4 Mat4::rotateZ(Ldouble radian) {
    Ldouble s = sinf(radian);
    Ldouble c = cosf(radian);
    Ldouble values[16] = {
        c,  s, 0, 0,
        -s, c, 0, 0,
        0,  0, 1, 0,
        0,  0, 0, 1,
    };
    return Mat4(values);
}

Mat4 Mat4::rotate(const Vec3 &vec) {
    return rotate(vec.x , vec.y , vec.z);
}

Mat4 Mat4::rotate(Ldouble radianX, Ldouble radianY, Ldouble radianZ) {
    Mat4 xm = Mat4::rotateX(radianX);
    Mat4 ym = Mat4::rotateY(radianY);
    Mat4 zm = Mat4::rotateZ(radianZ);
    return xm * ym * zm;
}

Mat4 Mat4::translate(const Vec3 &vec) {
    return translate(vec.x , vec.y , vec.z);
}

Mat4 Mat4::translate(Ldouble x, Ldouble y, Ldouble z){
    Ldouble values[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1,
    };
    return Mat4(values);
}






