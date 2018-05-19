//
//  Color.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <cstdlib>
#include <cstdint>
#include "MathUtil.hpp"

class Color {
    
public:
    union {
        struct {
            Ldouble r;
            Ldouble g;
            Ldouble b;
            Ldouble a;
        };
        Ldouble e[4];
    };
    
    Color(Ldouble r = 1.0f , Ldouble g = 1.0f , Ldouble b = 1.0f , Ldouble a = 1.0f):
    r(r),
    g(g),
    b(b),
    a(a){
        format();
    }
    
    inline void format() {
        r = fmin(r, (Ldouble)1.0f);
        g = fmin(g, (Ldouble)1.0f);
        b = fmin(b, (Ldouble)1.0f);
        a = fmin(a, (Ldouble)1.0f);
    }
    
    Color(uint32_t rgba){
        r = ((rgba & 0xff000000) >> 24) / 255.0f;
        g = ((rgba & 0x00ff0000) >> 16) / 255.0f;
        b = ((rgba & 0x0000ff00) >> 8) / 255.0f;
        a = (rgba & 0x000000ff) / 255.0f;
    }
    
    static Color randomColor() {
        Ldouble r = (rand() % 255) / 255.0;
        Ldouble g = (rand() % 255) / 255.0;
        Ldouble b = (rand() % 255) / 255.0;
        return Color(r, g, b, 1);
    };
    
    uint32_t uint32() const {
        
        double fr = fmin(r, (Ldouble)1.0f);
        double fg = fmin(g, (Ldouble)1.0f);
        double fb = fmin(b, (Ldouble)1.0f);
        double fa = fmin(a, (Ldouble)1.0f);
        
        uint32_t R = (uint32_t)(fr * 255.0f);
        uint32_t G = (uint32_t)(fg * 255.0f);
        uint32_t B = (uint32_t)(fb * 255.0f);
        uint32_t A = (uint32_t)(fa * 255.0f);
        uint32_t value =B | (G << 8) | (R << 16) | (A << 24);
        return value;
    }
    
    Color operator + (const Color &color) const {
        auto ret = Color(r + color.r, g + color.g, b + color.b, a + color.a);
        return ret;
    };
    
    Color operator - (const Color &color) const {
        auto ret = Color(r - color.r, g - color.g, b - color.b, a - color.a);
        return ret;
    };
    
    Color operator * (Ldouble factor) const {
        auto ret = Color(r * factor, g * factor, b * factor, a * factor);
        return ret;
    };
    
    Color operator * (const Color &color) const {
        return Color(r * color.r , g * color.g , b * color.b , a * color.a);
    }
    
    Color interpolate(const Color &c, Ldouble factor) const {
        auto ret = *this + (c - *this) * factor;
        return ret;
    };
};

#endif /* Color_hpp */












