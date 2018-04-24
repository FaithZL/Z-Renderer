//
//  Mat4.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Mat4_hpp
#define Mat4_hpp

#include <stdio.h>
#include "MathUtil.hpp"
#include "Vec.hpp"

class Mat4 {
    
public:
    Ldouble m[16];
    
    Mat4(Ldouble * p) {
        for (int i = 0 ; i < 16 ; ++ i) {
            m[i] = p[i];
        }
    }
    
    Mat4() {
        for (int i = 0 ; i < 16 ; ++ i) {
            m[i] = 0;
        }
    }
    
    bool operator == (const Mat4 &other) const {
        for (int i = 0; i < 16 ; ++ i) {
            if (!MathUtil::equal(other.m[1],this->m[1])) {
                return false;
            }
        }
        return true;
    }
    
    Mat4 operator * (const Mat4 &other) const ;
    
    static Mat4 perspective(Ldouble radian , Ldouble ratio , Ldouble nearPlane , Ldouble farPlane);
    
    static Mat4 translate(Ldouble x , Ldouble y , Ldouble z);
    
    static Mat4 translate(const Vec3 &vec);
    
    static Mat4 rotateX(Ldouble radianX);
    
    static Mat4 rotateY(Ldouble radianY);
    
    static Mat4 rotateZ(Ldouble radianZ);
    
    static Mat4 rotate(const Vec3 &vec);
    
    static Mat4 rotate(Ldouble radianX , Ldouble radianY , Ldouble radianZ);
    
    static Mat4 scale(const Vec3 &v);
    
    static Mat4 scale(Ldouble x , Ldouble y , Ldouble z);
    
    Vec3 transform(const Vec3 &vec) const;
    
    static Mat4 identity() {
        Ldouble a[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        return Mat4(a);
    }
};



#endif /* Mat4_hpp */










