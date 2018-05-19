//
//  ZMath.h
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/21.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef ZMath_h
#define ZMath_h

#define create_func(type) static type * create() { \
auto ret = new type(); \
return ret; \
}

#define Setter_and_getter_vec3(varName , funcName) \
public : inline void set##funcName(const Vec3 &val) { \
    this->varName = val; \
} \
public : inline Vec3 get##funcName() const { \
    return this->varName; \
} \
public : inline void set##funcName##X(Ldouble val){\
    this->varName.x = val; \
}\
public : inline Ldouble get##funcName##X() { \
    return this->varName.x; \
} \
public : inline void set##funcName##Y(Ldouble val){\
    this->varName.y = val; \
}\
public : inline Ldouble get##funcName##Y() { \
    return this->varName.y; \
} \
public : inline void set##funcName##Z(Ldouble val){\
    this->varName.z = val; \
}\
public : inline Ldouble get##funcName##Z() { \
    return this->varName.z; \
} \
protected : Vec3 varName;


#endif /* ZMath_h */
