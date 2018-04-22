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

#define Min 0.0000000001

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
    
};

#endif /* MathUtil_hpp */
