//
//  ZMath.h
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef ZMath_h
#define ZMath_h

#include <cmath>

const double min = 0.00000001;

bool equal(double v1 , double v2) {
    return fabs(v1 - v2) < min;
}

#endif /* ZMath_h */
