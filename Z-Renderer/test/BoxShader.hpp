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
#include "Macro.h"

struct Light {
    Vec3 pos;
    Color color;
};

struct Material {
    // 环境光
    Color ambient;
    // 漫反射
    Color diffuse;
    // 高光反射
    Color specular;
    //
    double shininess;
};

class BoxShader : public Shader {
    
public:
    
    create_func(BoxShader)
    
    void setMaterial(const Material &material);
    
    void setLight(const Light &light);
    
    virtual VertexOut vs(const Vertex &vertex) const;
    
    virtual Color fs(const VertexOut &vOut) const;
    
protected:
    Material _material;
    
    Light _light;
};

#endif /* BoxShader_hpp */










