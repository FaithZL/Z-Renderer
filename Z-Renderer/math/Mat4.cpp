//
//  Mat4.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/5.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "Mat4.hpp"


Vec4 Mat4::transform(const Vec4 &vec) {
    Ldouble x = vec.x * _11 + vec.y * _21 + vec.z * _31 + vec.w * _41;
    Ldouble y = vec.x * _12 + vec.y * _22 + vec.z * _32 + vec.w * _42;
    Ldouble z = vec.x * _13 + vec.y * _23 + vec.z * _33 + vec.w * _43;
    Ldouble w = vec.x * _14 + vec.y * _24 + vec.z * _34 + vec.w * _44;
    return Vec4(x , y , z , w);
}

Mat4 Mat4::identity() {
    Ldouble ret[16] = {
        1 , 0 , 0 , 0,
        0 , 1 , 0 , 0,
        0 , 0 , 1 , 0,
        0 , 0 , 0 , 1
    };
    return Mat4(ret);
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

Mat4 Mat4::scale(Ldouble x, Ldouble y, Ldouble z) {
    Ldouble a[16] = {
        x , 0 , 0 , 0,
        0 , y , 0 , 0,
        0 , 0 , z , 0,
        0 , 0 , 0 , 1
    };
    return Mat4(a);
}

Mat4 Mat4::perspective(Ldouble fovy, Ldouble aspect, Ldouble zNear, Ldouble zFar) {
    auto tanHalfFovy = tan(fovy / static_cast<Ldouble>(2));
    Ldouble value[16] = {
        static_cast<Ldouble>(1) / (aspect * tanHalfFovy) , 0 , 0 , 0,
        0 , static_cast<Ldouble>(1) / (tanHalfFovy) , 0 , 0,
        0 , 0 , - (zFar + zNear) / (zFar - zNear) , -1 ,
        0 , 0 , - (static_cast<Ldouble>(2) * zFar * zNear) / (zFar - zNear) , 0
    };
    return Mat4(value);
}

Mat4 Mat4::scale(Ldouble scale) {
    return translate(scale , scale , scale);
}

Mat4 Mat4::scale(const Vec3 &scale) {
    return translate(scale.x , scale.y , scale.z);
}

Mat4 Mat4::translate(Ldouble x , Ldouble y , Ldouble z) {
    Ldouble a[16] = {
        1 , 0 , 0 , 0,
        0 , 1 , 0 , 0,
        0 , 0 , 1 , 0,
        x , y , z , 1
    };
    return Mat4(a);
}

Mat4 Mat4::translate(const Vec3 &vec) {
    return translate(vec.x , vec.y , vec.z);
}

Mat4 Mat4::operator * (const Mat4 &other) {
    Ldouble ret[4][4];
    for (int i = 0 ; i < 4 ; ++ i) {
        for (int j = 0 ; j < 4 ; ++ j) {
            ret[i][j] = m[i][0] * other.m[0][j]
                    + m[i][1] * other.m[1][j]
                    + m[i][2] * other.m[2][j]
                    + m[i][3] * other.m[3][j];
        }
    }
    return Mat4(ret);
}

Mat4 Mat4::operator - (const Mat4 &other) {
    Ldouble ret[16];
    for (int i = 0 ; i < 16; ++ i) {
        ret[i] = a[i] - other.a[i];
    }
    return Mat4(ret);
}

Mat4 Mat4::operator + (const Mat4 &other) {
    Ldouble ret[16];
    for (int i = 0 ; i < 16; ++ i) {
        ret[i] = a[i] + other.a[i];
    }
    return Mat4(ret);
}

bool Mat4::operator == (const Mat4 &other) {
    for (int i = 0 ; i < 16 ; ++ i) {
        if (! MathUtil::equal(a[i], other.a[i])) {
            return false;
        }
    }
    return true;
}

