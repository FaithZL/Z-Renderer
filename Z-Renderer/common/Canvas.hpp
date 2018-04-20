//
//  Canvas.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>

class Cancas {
public:
    void putPixel(int x , int y , int z , u_int32_t color);
    
    void drawLine();
};

#endif /* Canvas_hpp */
