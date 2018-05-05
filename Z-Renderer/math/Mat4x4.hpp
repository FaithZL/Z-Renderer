//
//  Mat4x4.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/5.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Mat4x4_hpp
#define Mat4x4_hpp

#include "MathUtil.hpp"
#include "Vec.hpp"

class Mat4x4 {
    
public:
    union {
        Ldouble m[4][4];
        Ldouble a[16];
        struct
        {
            Ldouble _11; Ldouble _12; Ldouble _13; Ldouble _14;
            Ldouble _21; Ldouble _22; Ldouble _23; Ldouble _24;
            Ldouble _31; Ldouble _32; Ldouble _33; Ldouble _34;
            Ldouble _41; Ldouble _42; Ldouble _43; Ldouble _44;
        };
    };
    
    Mat4x4() {
        for (int i = 0 ;i< 16 ; ++ i) {
            a[i] = 0;
        }
    }
    
    Mat4x4(Ldouble p[4][4]) {
        for (int i = 0 ; i < 4; ++ i) {
            for (int j = 0 ; j < 4; ++ j) {
                m[i][j] = p[i][j];
            }
        }
    }
    
    Mat4x4(Ldouble * value) {
        for (int i = 0 ;i< 16 ; ++ i) {
            a[i] = value[i];
        }
    }
    
    Vec4 transform(const Vec4 &vec);
    
    static Mat4x4 perspective(Ldouble fov , Ldouble aspect , Ldouble zNear , Ldouble zFar);

    static Mat4x4 scale(Ldouble scale);
    
    static Mat4x4 scale(Ldouble x , Ldouble y , Ldouble z);
    
    static Mat4x4 scale(const Vec3 &scale);
    
    static Mat4x4 translate(const Vec3 &vec);
    
    static Mat4x4 translate(Ldouble x , Ldouble y , Ldouble z);
    
    static Mat4x4 rotateX(Ldouble radian);
    
    static Mat4x4 rotateY(Ldouble radian);
    
    static Mat4x4 rotateZ(Ldouble radian);
    
//    static Mat4x4 rotate(const Vec3 &vec);
    
    bool operator == (const Mat4x4 &other);
    
    Mat4x4 operator + (const Mat4x4 &other);
    
    Mat4x4 operator * (const Mat4x4 &other);
    
    Mat4x4 operator - (const Mat4x4 &other);
    
    static Mat4x4 identity();
    
};


#endif /* Mat4x4_hpp */
