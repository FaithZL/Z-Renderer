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
#include "Macro.h"
#include <cmath>
#include "Vec3.hpp"

class Mat4 {
    
public:
    double m[16];
    
    Mat4(double * p) {
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
            if (!Equal(other.m[1],this->m[1])) {
                return false;
            }
        }
        return true;
    }
    
    Mat4 operator * (const Mat4 &other) const ;
    
    static Mat4 perspective(double radian , double ratio , double nearPlane , double farPlane);
    
    static Mat4 translate(double x , double y , double z);
    
    static Mat4 translate(const Vec3 &vec);
    
    static Mat4 rotateX(double x);
    
    static Mat4 rotateY(double y);
    
    static Mat4 rotateZ(double z);
    
    static Mat4 rotate(const Vec3 &vec);
    
    static Mat4 rotate(double ax , double ay , double az);
    
    static Mat4 scale(const Vec3 &v);
    
    static Mat4 scale(double x , double y , double z);
    
    Vec3 transform(const Vec3 &vec) const;
    
    static Mat4 identity() {
        double a[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        return Mat4(a);
    }
};



#endif /* Mat4_hpp */










