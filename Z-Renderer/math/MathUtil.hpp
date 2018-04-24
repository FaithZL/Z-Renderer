//
//  MathUtil.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/22.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef MathUtil_hpp
#define MathUtil_hpp

#include <stdio.h>
#include <cmath>

#define Min 0.0000001
#define PI 3.141592653
typedef float Ldouble;

struct Line {
    Ldouble k = 1.0f;
    Ldouble b = 0.0f;
};

class MathUtil {
    
public:
    static inline bool equal(Ldouble v1 , Ldouble v2) {
        return fabs(v1 - v2) < Min;
    }
    
    static inline int round(Ldouble num) {
        return static_cast<int>(num + 0.5);
    }
    
    static inline Ldouble interpolate(Ldouble v1 , Ldouble v2 , Ldouble factor) {
        return v1 + (v2 - v1) * (factor);
    }
    
    static Ldouble inline angle2radian(Ldouble angle) {
        Ldouble radian = angle / (180 / PI);
        return radian;
    }
    
    static Ldouble inline radian2angle(Ldouble radian) {
        Ldouble angle = (180 / PI) * radian;
        return angle;
    }
    
    static inline Line getLineParam(Ldouble x1 , Ldouble y1 , Ldouble x2 , Ldouble y2){
        Line ret;
        Ldouble k = (y2 - y1) / (x2 - x1);
        Ldouble b = y1 - k * x1;
        ret.k = k;
        ret.b = b;
        return ret;
    }
};

#endif /* MathUtil_hpp */






