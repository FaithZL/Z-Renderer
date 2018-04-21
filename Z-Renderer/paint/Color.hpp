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

class Color {
    
public:
    double r;
    double g;
    double b;
    double a;
    
    Color(double r = 1.0f , double g = 1.0f , double b = 1.0f , double a = 1.0f):
    r(r),
    g(g),
    b(b),
    a(a){
        
    }
    
    Color(uint32_t rgba){
        r = ((rgba & 0x00ff0000) >> 16) / 255.0f;
        g = ((rgba & 0x0000ff00) >> 8) / 255.0f;
        b = ((rgba & 0x000000ff)) / 255.0f;
        a = ((rgba & 0xff000000) >> 24) / 255.0f;
    }
    
    static Color randomColor() {
        float r = (rand() % 255) / 255.0;
        float g = (rand() % 255) / 255.0;
        float b = (rand() % 255) / 255.0;
        return Color(r, g, b, 1);
    };
    
    uint32_t uint32() const {
        uint32_t R = (uint32_t)(r * 255.0f);
        uint32_t G = (uint32_t)(g * 255.0f);
        uint32_t B = (uint32_t)(b * 255.0f);
        uint32_t A = (uint32_t)(a * 255.0f);
        uint32_t value = (R << 16) | (G << 8) | B | (A << 24);
        return value;
    }
    
    Color operator + (const Color &color) const {
        return Color(r + color.r, g + color.g, b + color.b, a + color.a);
    };
    
    Color operator - (const Color &color) const {
        return Color(r - color.r, g - color.g, b - color.b, a - color.a);
    };
    
    Color operator * (float factor) const {
        return Color(r * factor, g * factor, b * factor, a * factor);
    };
    
    Color interpolate(const Color &c, float factor) const {
        return *this + (c - *this) * factor;
    };
};

#endif /* Color_hpp */












