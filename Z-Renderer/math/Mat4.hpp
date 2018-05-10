//
//  Mat4.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/5.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Mat4_hpp
#define Mat4_hpp

#include "MathUtil.hpp"
#include "Vec.hpp"

class Mat4 {
    
public:
    union {
        Ldouble m[4][4];
        Ldouble a[16];
        struct
        {
            Ldouble _11; Ldouble _12; Ldouble _13; Ldouble _14;
            Ldouble _21; Ldouble _22; Ldouble _23; Ldouble _24;
            Ldouble _31; Ldouble _32; Ldouble _33; Ldouble _34;
            Ldouble _41; Ldouble _42; Ldouble _43; Ldouble _44;
        };
    };
    
    Mat4() {
        for (int i = 0 ;i < 16 ; ++ i) {
            a[i] = 0;
        }
    }
    
    Mat4(Ldouble p[4][4]) {
        for (int i = 0 ; i < 4; ++ i) {
            for (int j = 0 ; j < 4; ++ j) {
                m[i][j] = p[i][j];
            }
        }
    }
    
    Mat4(Ldouble * value) {
        for (int i = 0 ;i< 16 ; ++ i) {
            a[i] = value[i];
        }
    }
    
    inline void setZero() {
        for (int i = 0 ; i < 16; ++ i) {
            a[i] = 0;
        }
    }
    
    // 伴随矩阵除以行列式
    Mat4 getInverseMat() const;
    
    Mat4 getTransposeMat() const;
    
    Mat4 getAdjointMat() const;
    
    Ldouble getAdjointElement(Ldouble a1, Ldouble a2, Ldouble a3,
                              Ldouble b1, Ldouble b2, Ldouble b3,
                              Ldouble c1, Ldouble c2, Ldouble c3)const;
    
    Ldouble getDet() const;
    
    inline void print() const {
        cout << this << endl;
        for (int i = 0 ; i < 4 ; ++ i) {
            for (int j = 0 ; j < 4; ++ j) {
                char * str = new char[50]();
                sprintf(str , "m[%d][%d] = %f  " , i , j , m[i][j]);
                cout << str ;
                delete [] str;
            }
            cout << endl;
        }
    }
    
    Vec4 transform(const Vec4 &vec) const;
    
    static Mat4 perspective(Ldouble fov , Ldouble aspect , Ldouble zNear , Ldouble zFar);

    static Mat4 scale(Ldouble scale);
    
    static Mat4 scale(Ldouble x , Ldouble y , Ldouble z);
    
    static Mat4 scale(const Vec3 &scale);
    
    static Mat4 translate(const Vec3 &vec);
    
    static Mat4 translate(Ldouble x , Ldouble y , Ldouble z);
    
    static Mat4 rotateX(Ldouble radian);
    
    static Mat4 rotateY(Ldouble radian);
    
    static Mat4 rotateZ(Ldouble radian);
    
    bool operator == (const Mat4 &other) const;
    
    Mat4 operator + (const Mat4 &other) const;
    
    Mat4 operator * (const Mat4 &other) const;
    
    Mat4 operator - (const Mat4 &other) const;
    
    Mat4 operator * (Ldouble num) const;
    
    Mat4 operator / (Ldouble num) const;
    
    static Mat4 identity();
    
};


#endif /* Mat4_hpp */
