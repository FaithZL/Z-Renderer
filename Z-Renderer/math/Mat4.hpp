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
    
    Mat4 operator * (const Mat4 &other) const {
        
        double values[16];
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










