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

struct Line {
    double k = 1.0f;
    double b = 0.0f;
};

class MathUtil {
    
public:
    static inline bool equal(double v1 , double v2) {
        return fabs(v1 - v2) < Min;
    }
    
    static inline int round(double num) {
        return static_cast<int>(num + 0.5);
    }
    
    static inline double interpolate(double v1 , double v2 , double factor) {
        return v1 + (v2 - v1) * (factor);
    }
    
    static inline Line getLineParam(double x1 , double y1 , double x2 , double y2){
        Line ret;
        double k = (y2 - y1) / (x2 - x1);
        double b = y1 - k * x1;
        ret.k = k;
        ret.b = b;
        return ret;
    }
};

#endif /* MathUtil_hpp */






