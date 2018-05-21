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
    Ldouble factor;
};

struct Ambient {
    Color color;
    Ldouble factor;
};

struct Material {
    Ldouble diffuseFactor;
    Ldouble specularFactor;
    //
    Ldouble shininess;
};

class PhongShader : public Shader {
    
public:
    
    create_func(PhongShader)
    
    void setMaterial(const Material &material);
    
    void setLight(const Light &light);
    
    void setAmbient(const Ambient &ambient);
    
    virtual VertexOut vs(const Vertex &vertex) const;
    
    virtual Color fs(const VertexOut &frag) const;
    
    Color getDiffuse(const VertexOut &frag) const;
    
    Color getAmbient(const VertexOut &frag) const;
    
    Color getSpecular(const VertexOut &frag) const;
    
protected:
    Material _material;
    
    Ambient _ambient;
    
    Light _light;
};

#endif /* BoxShader_hpp */










