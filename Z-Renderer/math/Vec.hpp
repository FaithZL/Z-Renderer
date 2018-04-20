//
//  Vec.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/20.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Vec_hpp
#define Vec_hpp

#include <stdio.h>

class Vec {
    
public:
    double R(){
        return x;
    }
    double G();
    double B();
    double A();
    
    double X();
    double Y();
    double Z();
    double W();
    
protected:
    
    double x;
    double y;
    double z;
    double w;
};

#endif /* Vec_hpp */
