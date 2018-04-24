//
//  ZMath.h
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef ZMath_h
#define ZMath_h

#define Setter_and_getter_vec3(varName , funcName) \
public : inline void set##FuncName(const Vec3 &val) { \
    this->varName = val; \
}



#endif /* ZMath_h */
