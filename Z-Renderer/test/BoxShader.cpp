//
//  BoxShader.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/19.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "BoxShader.hpp"
#include "Canvas.hpp"
#include <algorithm>

void BoxShader::setLight(const Light &light) {
    _light = light;
}

void BoxShader::setMaterial(const Material &material) {
    _material = material;
}

VertexOut BoxShader::vs(const Vertex &vertex) const {
    return Shader::vs(vertex);
}

Color BoxShader::fs(const VertexOut &frag) const {
    auto texture = Canvas::getInstance()->getTexture();
    auto fragColor = texture->sample(frag.tex.u, frag.tex.v);
    Color ambient = _material.ambient;
    
    Vec3 fragPos = frag.posWorld;
    Vec3 normal = frag.normal.getNormalize();
    
    Vec3 ray = (_light.pos - fragPos).getNormalize();
    double cosTheta = ray.dot(normal);
    double diff = max(cosTheta , (double)0.0f);
    Color diffuse = _light.color * diff;
    
    //处理高光
    Vec3 cameraPos = Camera::getInstance()->getPosition();
    Vec3 viewDir = (cameraPos - fragPos).getNormalize();
    Vec3 reflectDir = (-ray).reflect(normal);
    
    auto spec = pow(max(viewDir.dot(reflectDir), 0.0), 64);
    Color specular = _light.color * spec;

    return fragColor * (ambient + specular);
}







