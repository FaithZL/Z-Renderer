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
public : inline void set##funcName(const Vec3 &val) { \
    this->varName = val; \
} \
public : inline Vec3 get##funcName() const { \
    return this->varName; \
} \
protected : Vec3 varName;


#endif /* ZMath_h */
