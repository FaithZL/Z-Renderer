//
//  BoxShader.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/19.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef BoxShader_hpp
#define BoxShader_hpp

#include "Shader.hpp"

struct Light {
    Vec3 pos;
    Color color;
};

struct Mertial {
    // 环境光
    Vec3 ambient;
    // 漫反射
    Vec3 diffuse;
    // 高光反射
    Vec3 specular;
    // 
    Vec3 shininess;
};

class BoxShader : public Shader {
    
public:
    
};

#endif /* BoxShader_hpp */
